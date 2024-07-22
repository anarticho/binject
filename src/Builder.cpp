#include <Builder.h>

Builder::Builder():
    outputs(),
    args(),
    out_obj()
{
    func_map["-s"] = std::bind(&Builder::get_s, this);
    func_map["-ns"] = std::bind(&Builder::get_ns, this);
    func_map["-x"] = std::bind(&Builder::get_x, this);
    func_map["-nx"] = std::bind(&Builder::get_nx, this);
    func_map["-a"] = std::bind(&Builder::get_a, this);
    func_map["-na"] = std::bind(&Builder::get_na, this);
    func_map["-if"] = std::bind(&Builder::get_if, this);
}

bool Builder::step()
{
    const bool ret = !args.empty()                      // still argument to process
                && (func_map.count(args.front()) != 0)  // verify flag within map
                && func_map.at(args.front())();         // execute function (and increment pointer)
    if(ret)
    {
        outputs.push(out_obj);
        out_obj.nb = 1;
    }
    else
    {
        while(!args.empty() && !outputs.empty())
        {
            args.pop();
            outputs.pop();
        };
    }
    return ret;
}

bool Builder::get_n()
{
    bool ret = true;
    try
    {
        const int tmp = std::stoi(args.front());
        ret = (tmp <= UINT16_MAX);
        out_obj.nb = tmp;
    }
    catch(const std::exception& e)
    {
        ret = false;
    }
    return ret;
}

bool Builder::get_x()
{
    args.pop();
    const bool ret = Getter::get_x0(args.front(), out_obj);
    args.pop();
    return ret;
}

bool Builder::get_s()
{
    args.pop();                 // get next argument (from flag to data)
    out_obj.str = args.front(); // just get string within out_obj
    args.pop();                 // point to next argument (next flag or \0)
    return true;
}

bool Builder::get_a()
{
    args.pop();
    const bool ret = Getter::get_a0(args.front(), out_obj);
    args.pop();
    return ret;     
}

bool Builder::get_if()
{
    args.pop();                                                         // get next argument (from flag to data)
    const bool ret = Getter::get_if0(args.front(), out_obj);    // parse -if within out_obj
    args.pop();                                                         // point to next argument (next flag or \0)
    return ret;
}
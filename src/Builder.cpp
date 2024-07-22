#include <Builder.h>

Builder::Builder(Args& args0):
    outputs(),
    args(args0),
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
    const bool ret = !args.current().empty()                // is not empty
                && (func_map.count(args.current()) != 0)    // verify flag within map
                && func_map.at(args.cunext())();            // execute function (and increment pointer)
    if(ret)
    {
        outputs.push(out_obj);
        out_obj.nb = 1;
    }
    else
    {
        while(args.isn() && !outputs.empty())
        {
            args.next();
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
        const int tmp = std::stoi(args.cunext());
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
    const bool ret = Getter::get_x0(args.cunext(), out_obj);
    return ret;
}

bool Builder::get_s()
{
    out_obj.str = args.cunext();
    return true;
}

bool Builder::get_a()
{
    const bool ret = Getter::get_a0(args.cunext(), out_obj);
    return ret;     
}

bool Builder::get_if()
{
    const bool ret = Getter::get_if0(args.cunext(), out_obj);
    return ret;
}
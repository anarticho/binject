#include "Builder.h"

Builder::Builder():
    outputs(),
    out_obj(),
    ptr_arg(0)
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
    const bool ret = ptr_arg                        // verify both init function called and overflowing argv array.
                && (func_map.count(**ptr_arg) != 0) // verify flag within map
                && func_map.at(**ptr_arg)();        // execute function (and increment pointer)
    if(ret)
    {
        outputs.push(out_obj);
        out_obj.nb = 1;
    }
    else
    {
        ptr_arg = 0;
        while(!outputs.empty())
        {
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
        const int tmp = std::stoi(**ptr_arg);
        ret = (tmp <= UINT16_MAX);
        out_obj.nb = tmp;
    }
    catch(const std::exception& e)
    {
        ret = false;
    }
    char* next_arg = *((*ptr_arg)+1);
    const bool next_ok = (next_arg!=0) && (next_arg[0]!='-');
    return ret && next_ok;
}

bool Builder::get_x()
{
    (*ptr_arg)++;
    const bool ret = Getter::get_x0(**ptr_arg, out_obj);
    (*ptr_arg)++;
    return ret;
}

bool Builder::get_s()
{
    (*ptr_arg)++;               // get next argument (from flag to data)
    out_obj.str = **ptr_arg;    // just get string within out_obj
    (*ptr_arg)++;               // point to next argument (next flag or \0)
    return true;
}

bool Builder::get_a()
{
    (*ptr_arg)++;
    const bool ret = Getter::get_a0(**ptr_arg, out_obj);
    (*ptr_arg)++;
    return ret;     
}

bool Builder::get_if()
{
    (*ptr_arg)++;                                           // get next argument (from flag to data)
    const bool ret = Getter::get_if0(**ptr_arg, out_obj);   // parse -if within out_obj
    (*ptr_arg)++;                                           // point to next argument (next flag or \0)
    return ret;
}
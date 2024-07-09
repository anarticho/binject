#include "Builder.h"

Builder::Builder(Outputs& outputs):
    out_obj(),
    out_q(outputs),
    ptr_arg(0)
{
    func_map["-s"] = std::bind(&Builder::get_s, this);
    func_map["-ns"] = std::bind(&Builder::get_ns, this);
    func_map["-x"] = std::bind(&Builder::get_x, this);
    func_map["-nx"] = std::bind(&Builder::get_nx, this);
}

bool Builder::step()
{
    const bool ret = ptr_arg                        // verify both init function called and overflowing argv array.
                && (func_map.count(**ptr_arg) != 0) // verify flag within map
                && func_map.at(**ptr_arg)();  // execute function (and increment pointer)
    if(ret)
    {
        out_q.push(out_obj);
        out_obj.nb = 1;
    }
    else
    {
        ptr_arg = 0;
        while(!out_q.empty())
        {
            out_q.pop();
        };
    }
    return ret;
}

bool Builder::get_n()
{
    bool ret = true;
    try
    {
        out_obj.nb = std::stoi(**ptr_arg);
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
    static std::string patrn = "[A-F0-9]+"; // only digits and uppercase A to F
    static const size_t hex_sz = 2;

    std::string str(**ptr_arg);             // increment pointer
    const size_t str_sz = str.length();
    
    bool ret = ((str_sz%hex_sz) == 0)       // even size
            && (std::regex_match(str, std::regex(patrn)));
    if(ret)
    {
        out_obj.str.clear();                // clear str before using += operator.
        for(size_t pos=0; ret && (pos<str_sz); pos+=2)
        {
            try
            {
                static const int base_hex = 16;
                out_obj.str += static_cast<char>(std::stoi(str.substr(pos, hex_sz), 0, base_hex));
            }
            catch (const std::exception& e)
            {
                ret = false;
            }
        }
    }
    ++(*ptr_arg);
    return ret;
}

bool Builder::get_s()
{
    (*ptr_arg)++;
    out_obj.str = **ptr_arg;
    (*ptr_arg)++;
    return true;
}
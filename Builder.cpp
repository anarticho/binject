#include "Builder.h"

Builder::Builder(Outputs& outputs):
    out_obj(),
    out_q(outputs),
    ptr(0),
    end(0)
{
    func_map["-s"] = std::bind(&Builder::get_s, this);
    func_map["-ns"] = std::bind(&Builder::get_ns, this);
    func_map["-x"] = std::bind(&Builder::get_x, this);
    func_map["-nx"] = std::bind(&Builder::get_nx, this);
}

bool Builder::step()
{
    const bool ret = ptr                        // verify init call
                && (*ptr < end)                 // verify pending element
                && (func_map.count(*ptr) != 0)  // verify flag within map
                && func_map.at(*ptr++)();       // execute function (and increment pointer)
    if(ret)
    {
        out_q.push(out_obj);
    }
    return ret;
}

bool Builder::get_n()
{
    bool ret = true;
    try
    {
        out_obj.nb = std::stoi(*ptr);
    }
    catch(const std::exception& e)
    {
        ret = false;
    }
    ptr++;
    return ret;
}

bool Builder::get_x()
{
    static std::string patrn = "[A-F0-9]+"; // only digits and uppercase A to F
    static const size_t hex_sz = 2;

    std::string str(*ptr);                // increment pointer
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
    ptr++;
    return ret;
}

bool Builder::get_s()
{
    out_obj.nb = 1;
    out_obj.str = *ptr;
    ptr++;
    return true;
}
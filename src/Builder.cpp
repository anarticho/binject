#include "Builder.h"

bool Builder::check_fext(const char* str)
{
    const std::string bin_str = ".bin";

    const size_t ext_sz = bin_str.length();
    const size_t arg_sz = std::strlen(str);

    return (arg_sz >= ext_sz) && (bin_str.compare(str+arg_sz-ext_sz) == 0);
}

Builder::Builder(Outputs& outputs):
    out_obj(),
    out_q(outputs),
    ptr_arg(0)
{
    func_map["-s"] = std::bind(&Builder::get_s, this);
    func_map["-ns"] = std::bind(&Builder::get_ns, this);
    func_map["-x"] = std::bind(&Builder::get_x, this);
    func_map["-nx"] = std::bind(&Builder::get_nx, this);
    func_map["-x64"] = std::bind(&Builder::get_x64, this);
    func_map["-nx64"] = std::bind(&Builder::get_nx64, this);
    func_map["-if"] = std::bind(&Builder::get_if, this);
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
    static std::string patrn = "[a-fA-F0-9]+"; // only digits and uppercase A to F
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

bool Builder::get_x64()
{
    static const uint8_t u64_sz8 = 8;           // 64-bits unsigned integer length in bytes.  
    const bool ret = Builder::get_x()           // increment ptr_arg
                     && (out_obj.str.length() <= u64_sz8);
    if(ret)
    {
        std::reverse(out_obj.str.begin(), out_obj.str.end());
        while(out_obj.str.length() != u64_sz8)
        {
            out_obj.str += '\0';
        }
    }
    return ret;     
}

bool Builder::get_if()
{
    (*ptr_arg)++;
    std::ifstream ifstr;
    const bool ret = check_fext(**ptr_arg)
                 && (ifstr.open(**ptr_arg, std::ifstream::binary), true) 
                 && ifstr.is_open();
    if(ret)
    {
        std::ostringstream tmp;
        tmp << ifstr.rdbuf();
        out_obj.str = tmp.str();
    }
    ifstr.close();
    (*ptr_arg)++;
    return ret;
}
#include "Getter.h"

bool Getter::check_fext(const char* str)
{
    const std::string bin_str = ".bin";

    const size_t ext_sz = bin_str.length();
    const size_t arg_sz = std::strlen(str);

    return (arg_sz >= ext_sz) && (bin_str.compare(str+arg_sz-ext_sz) == 0);
}

bool Getter::get_if0(const char* str, Output& out)
{
    std::ifstream ifstr;
    const bool ret = check_fext(str)
                 && (ifstr.open(str, std::ifstream::binary), true) 
                 && ifstr.is_open();
    if(ret)
    {
        std::ostringstream tmp;
        tmp << ifstr.rdbuf();
        out.str = tmp.str();
    }
    ifstr.close();
    return ret;
}
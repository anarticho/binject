#include <Getter.h>

#include <Badject.h>
#include <File.h>

namespace
{
    static const size_t base_hex = 16;
}

bool Getter::check_fext(const std::string& str)
{
    const std::string bin_str = ".bin";

    const size_t ext_sz = bin_str.length();
    const size_t arg_sz = str.size();

    return (arg_sz >= ext_sz) && (bin_str.compare(str.c_str()+arg_sz-ext_sz) == 0);
}

bool Getter::get_if0(const std::string& str, Output& out)
{
    const bool ret = check_fext(str) && File::read(str.c_str(), out.str);
    return ret;
}

bool Getter::get_x0(const std::string& str, Output& out)
{
    bool ret = true;

    static const size_t hex_sz = 2;
    const size_t str_sz = str.length();
    for(size_t pos=0; ret && (pos<str_sz); pos+=hex_sz)
    {
        try                                 // std::stoi call can throw an exception
        {
            const char tmp = std::stoi(str.substr(pos, hex_sz), 0, base_hex);
            out.str += tmp;
        }
        catch (const std::exception& e)
        {
            ret = false;
        }
    }
    return ret;
}

bool Getter::get_a0(const std::string& str, Output& out)
{
    bool ret = true;
    try
    {
        out.str.resize(u64_sz8, '\0');
        const uint64_t tmp = std::stoull(str, 0, base_hex);
        std::memcpy(out.str.data(), &tmp, u64_sz8);
    }
    catch (const std::exception& e)
    {
        ret = false;
    }

    return ret;
}

bool Getter::get_of0(const std::string& str, Output& out)
{
    const bool ret = Getter::check_fext(str);   // file name OK
    out.str = str;                              // store file name
    return ret;
}

bool Getter::get_bd0(const std::string& bad, const std::string& str, const std::string& loc)
{
    Output bad_bin, str_bin;
    const bool ret = get_if0(bad, bad_bin)                          // load file containing bad characters
                  && get_if0(str, str_bin)                          // load file containing value to XOR
                  && Badject::build(bad_bin.str, str_bin.str, loc); // process badchars
    return ret;
}
#include <Getter.h>

#include <Badject.h>
#include <File.h>

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
    static const size_t hex_sz = 2;             // expected size is even (because of hex format)
    static std::string patrn = "[a-fA-F0-9]+";  // only digits and lower and uppercases from A to f

    std::string hex_str(str);
    const size_t str_sz = hex_str.length();     // check provided size is even and matching pattern.
    bool ret = ((str_sz%hex_sz) == 0) && (std::regex_match(str, std::regex(patrn)));
    if(ret)
    {
        for(size_t pos=0; ret && (pos<str_sz); pos+=2)
        {
            try                                 // std::stoi call can throw an exception
            {
                static const size_t base_hex = 16;
                out.str += static_cast<char>(std::stoi(hex_str.substr(pos, hex_sz), 0, base_hex));
            }
            catch (const std::exception& e)
            {
                ret = false;
            }
        }
    }
    return ret;
}

bool Getter::get_a0(const std::string& str, Output& out)
{
    const bool ret = Getter::get_x0(str, out)                   // ::get_x increment ptr_arg
                     && (out.str.length() <= u64_sz8);          // check if fit within x64 address
    if(ret)
    {
        std::reverse(out.str.begin(), out.str.end());   // set little-endian
        while(out.str.length() != u64_sz8)              // fill out_obj with 0 for padding
        {
            out.str += '\0';
        }
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
#include <Binject.h>

#include <File.h>
#include <Flags.h>
#include <Logger.h>
#include <Outject.h>

namespace
{
    static const uint16_t nb_param_min = 2; // first check for minimum size (flag+data)
}

Binject::Binject(int argc, char* argv[]):
    Args(argc, argv),
    Builder(reinterpret_cast<Args&>(*this)),
    out_file(),
    bad_flg()
{
}

bool Binject::init()
{
    const size_t nb_args = Args::length();  
    const bool ret = (nb_args>=nb_param_min) && check();  // then for enhanced flags, and process it if needed
    while(ret && Builder::step());                  // check and parse format flags, 
                                                    // break at first error OR if no more element to build
    return ret && Builder::build_ok;
}

bool Binject::check()
{
    std::map<std::string, std::function<bool ()> > func_map;    // local map
    func_map.insert(std::make_pair(*Flags::get(enh_outf),       // append out file flag
                    std::bind(&Binject::get_of, this)));
    func_map.insert(std::make_pair(*Flags::get(enh_gnbd),       // append bad characters parser
                    std::bind(&Binject::get_bd, this)));
    func_map.insert(std::make_pair(*Flags::get(enh_ckbd),
                    std::bind(&Binject::get_cb, this)));

    const bool is_flag = (func_map.count(args.current()) != 0); // detect enhanced flag
    const bool ret = is_flag && func_map.at(args.cunext())();   // process if needed, and store result
    return (!is_flag) || ret;   // return true if no flag was detected, else return ret.
}

bool Binject::get_cb()
{
    const std::string bad_str = args.cunext();
    // out_file is filled, then shall return false to not being processed as -of file.
    if(Getter::get_if0(bad_str, out_file))
    {
        bool has_finish = false;
        uint16_t nb_flag = 0;
        do
        {
            has_finish = !Builder::step();
            if(!has_finish && Builder::build_ok)
            {
                bool has_badchar = false;
                const size_t nb_badchars = out_file.str.length();
                for(size_t i=0; !has_badchar && (i<nb_badchars); i++)
                {
                    has_badchar = (outputs.front().str.find(out_file.str[i]) != std::string::npos);
                }
                outputs.pop();
                std::string log_char("Bad character found at flag #");
                log_char += std::to_string(nb_flag++);
                Logger::err(log_char.c_str(), !has_badchar);
            }
        } while(!has_finish);
    }
    return false;   // return false to avoid ::step call
}

bool Binject::get_bd()
{
    static const uint16_t d_args = 3U;      // 3 parameters
    bool ret = (args.length() >= d_args);   // pending number greater or equals
    if(ret)
    {
        // using const reference on std::string avoid calling copy constructor
        // furthermore, ensure calling order, that passing per lvalue from call would depends on compiler 
        std::string bad_str = args.cunext();
        std::string arg_str = args.cunext();
        std::string loc_str = args.cunext();
        ret = Getter::get_bd0(bad_str, arg_str, loc_str);
    }
    return ret;
}


bool Binject::get_of()
{
    const bool ret = Getter::get_of0(args.cunext(), out_file);
    return ret;
}

void Binject::step()
{
    Outject out(out_file.str);  // create file and redirect flux if necessary.
    while(!out.has_fail() && !outputs.empty())
    {
        outputs.front().process();
        outputs.pop();
    };
    // ~Outject, DTOR is called here, to close file and restablish original std::cout if necessary.
}
#include <Binject.h>

#include <Outject.h>

Binject::Binject(int argc, char* argv[]):
    Args(argc, argv),
    Builder(reinterpret_cast<Args&>(*this)),
    out_file()
{
}

bool Binject::init()
{
    static const int min_nb = 2;                    // first check for minimum size (path+flag+data)
    const size_t nb_args = Args::length();  
    const bool ret = (nb_args>=min_nb) && check();  // then for enhanced flags, and process it if needed
    while(ret && Builder::step());                  // check and parse format flags, 
                                                    // break at first error OR if no more element to build
    return ret && Builder::build_ok;
}

bool Binject::check()
{
    /// Map of functions to process enhanced flags.
    std::map<std::string, std::function<bool ()> > func_map;
    func_map.insert(std::make_pair("-of", std::bind(&Binject::get_of, this)));
    func_map.insert(std::make_pair("-bd", std::bind(&Binject::get_bd, this)));

    /// Check for enhanced functions.
    const bool is_flag = (func_map.count(args.current()) != 0); // detect enhanced flag
    const bool ret = is_flag && func_map.at(args.cunext())();   // process if needed, and store result
    return (!is_flag) || ret;
}

bool Binject::get_bd()
{
    static const uint16_t d_args = 3U;      // 3 parameters
    bool ret = (args.length() >= d_args);   // pending number greater or equals
    if(ret)
    {
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
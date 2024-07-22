#include <Binject.h>

#include <Outject.h>

Binject::Binject(int argc, char* argv[]):
    Args(argc, argv),
    Builder(reinterpret_cast<Args&>(*this)),
    out_file()
{
    // first check for enhanced flags, and process it if needed
    const bool ret = check();
    
    // then check and parse format flags
    while(ret && Builder::step());
}

bool Binject::check()
{
    /// Map of functions to process the first flag.
    std::map<std::string, std::function<bool ()> > func_map;
    func_map["-of"] = std::bind(&Binject::get_of, this);
    func_map["-bd"] = std::bind(&Binject::get_bd, this);
    const bool is_flag = args.isn() && (func_map.count(args.current()) != 0); // check if within map
    bool ret = is_flag && func_map.at(args.cunext())();   // change args state (by calling pop)
    return (!is_flag) || ret;
}

bool Binject::get_bd()
{
    Args::Arg bad_str = args.cunext();
    Args::Arg arg_str = args.cunext();
    const bool ret = Getter::get_bd0(bad_str, arg_str);
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
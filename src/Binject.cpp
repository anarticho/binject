#include <Binject.h>

#include <Badject.h>
#include <Outject.h>

Binject::Binject(int argc, char* argv[]):
    Builder(),
    out_file()
{
    for(int i=1; i<argc; i++)   // build queue for arguments
    {
        args.push(*(++argv));   // skip first argument (as for path)
    }

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

    const bool is_flag = (func_map.count(args.front()) != 0);   // check if within map
    const bool ret = is_flag && func_map.at(args.front())();    // change args state (by calling pop)
    return (!is_flag) || ret;
}

bool Binject::get_bd()
{
    args.pop();
    Output bad_bin, str_bin;
    const bool ret = Getter::get_if0(args.front().c_str(), bad_bin) // load file containing bad characters
                  && (args.pop(), true)                             // pop to get next data
                  && Getter::get_if0(args.front().c_str(), str_bin) // load file containing value to XOR
                  && Badject::build(bad_bin.str, str_bin.str);      // process badchars
    args.pop();
    return ret;
}


bool Binject::get_of()
{
    args.pop();
    const bool ret = Getter::get_of0(args.front().c_str(), out_file);
    args.pop();
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
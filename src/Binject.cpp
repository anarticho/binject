#include <Binject.h>

#include <Badject.h>
#include <Outject.h>

Binject::Binject(int argc, char* argv[]):
    Builder(),
    out_file()
{
    // build map for flags and related functions.
    func_map["-of"] = std::bind(&Binject::get_of, this, std::placeholders::_1);
    func_map["-bd"] = std::bind(&Binject::get_bd, this, std::placeholders::_1);

    char** ptr_arg = argv+1;            // instantiate pointer to skip parameters if needed
    if((argc>=3) && check(&ptr_arg))    // check first flag (-of and -bd)
    {
        build(ptr_arg); // build and parse flags
    }
}

bool Binject::check(char*** ptr_arg)
{
    const bool is_flag = (func_map.count(**ptr_arg) != 0);          // check for existing first parameter
    const bool ret = is_flag && func_map.at(**ptr_arg)(ptr_arg);    // increment ptr
    return (!is_flag) || ret;
}

bool Binject::build(char** start)
{
    bool ret = true;
    Builder::init(&start);       // provide pointer to the first argument pointer
    while(ret && *start)
    {
        ret = Builder::step();   // return false at error
    };
    return ret;
}

bool Binject::get_bd(char*** ptr_arg)
{
    (*ptr_arg)++;   // get next argument (from flag to data)
    Output bad_bin, str_bin;
    const bool ret = Getter::get_if0(*(*ptr_arg), bad_bin)      // load file containing bad characters
                  && Getter::get_if0(*((*ptr_arg)+1), str_bin)  // load file containing value to XOR
                  && Badject::build(bad_bin.str, str_bin.str);  // process badchars
    (*ptr_arg)++;   // point to next argument (next flag or \0)
    return ret;
}


bool Binject::get_of(char*** ptr_arg)
{
    (*ptr_arg)++;   // point to next argument (next flag or \0)
    const bool ret = Getter::get_of0(**ptr_arg, out_file);
    (*ptr_arg)++;               // point to next argument (next flag or \0)
    return ret;
}

void Binject::step()
{
    Outject out(out_file.str);  // create file and redirect flux if necessary.
    while(!out.has_fail() && !outputs.empty())
    {
        Output out = outputs.front();
        out.process();
        outputs.pop();
    };
    // ~Outject, DTOR is called here, to close file and restablish original std::cout if necessary.
}
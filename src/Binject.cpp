#include "Binject.h"

bool Binject::get_bd(char*** ptr_arg)
{

}


bool Binject::get_of(char*** ptr_arg)
{
    const bool ret = Builder::check_fext(*(++(*ptr_arg)));    // file name OK
    if(ret)
    {
        outfile = *((*ptr_arg)++);   // store file name
    }
    return ret;
}


bool Binject::check(char*** ptr_arg)
{
    const bool is_flag = (func_map.count(**ptr_arg) != 0);          // check for existing first parameter
    const bool ret = is_flag && func_map.at(**ptr_arg)(ptr_arg);    // increment ptr
    return (!is_flag) || ret;
}

Binject::Binject(int argc, char* argv[]):
    outputs(),
    builder(outputs),   // construct the builder with outputs queue
    outfile()
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

bool Binject::build(char** start)
{
    bool ret = true;
    builder.init(&start);       // provide pointer to the first argument pointer
    while(ret && *start)
    {
        ret = builder.step();   // return false at error
    };
    return ret;
}

bool Binject::get_ostr(std::ofstream& ofstr)
{
    const bool is_file = !outfile.empty();
    bool is_ok = false;
    if(is_file)
    { 
        ofstr.open(outfile, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
        is_ok = ofstr.is_open() && (std::cout.rdbuf(ofstr.rdbuf()), true);
        while(!is_file && !outputs.empty())
        {
            outputs.pop();
        };
    }
    return !is_file || is_ok;
}

void Binject::step()
{
    std::streambuf* shrbuf = std::cout.rdbuf();
    std::ofstream ofstr;
    const bool out_ok = get_ostr(ofstr);
    while(out_ok && !outputs.empty())
    {
        Output out = outputs.front();
        out.process();
        outputs.pop();
    };
    std::cout.rdbuf(shrbuf);
    ofstr.close();
}
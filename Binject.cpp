#include "Binject.h"

Binject::Binject(int argc, char* argv[]):
    outputs(),
    builder(outputs),   // construct the builder with outputs queue
    outfile()
{
    (argc>=3)           // at least 3 arguments (including argv[0] executable)
    && build(argv+1);
}

bool Binject::init(char*** start)
{
    const std::string of_str = "-of";
    const std::string bin_str = ".bin";
    const size_t ext_sz = bin_str.length();
    char** arg_ptr = *start;

    const bool is_of = (of_str.compare(*arg_ptr++) == 0);
    const size_t arg_sz = std::strlen(*arg_ptr);
    bool ret = is_of 
               && (std::strlen(*arg_ptr) >= ext_sz)
               && (bin_str.compare((*arg_ptr)+arg_sz-ext_sz) == 0);
    if(ret)
    {
        outfile = *arg_ptr++;
        *start = arg_ptr;
    }

    return (!is_of) || ret;
}

bool Binject::build(char** start)
{
    bool ret = true;
    char*** ptr_start = &start;
    if(init(ptr_start))
    {
        builder.init(ptr_start);    // provide pointer to the first argument pointer
        while(ret && **ptr_start)
        {
            ret = builder.step();   // return false at error
        };
    }
    return ret;
}

bool Binject::to_file(std::ofstream& ofstr)
{
    bool is_file = !outfile.empty();
    if(is_file)
    { 
        ofstr.open(outfile, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
        is_file = ofstr.is_open() && (std::cout.rdbuf(ofstr.rdbuf()), true);
        while(!is_file && !outputs.empty())
        {
            outputs.pop();
        };
    }
    return is_file;
}

void Binject::step()
{
    std::streambuf* shrbuf = std::cout.rdbuf();
    std::ofstream ofstr;
    const bool is_file = to_file(ofstr);
    while(!outputs.empty())
    {
        Output out = outputs.front();
        out.process();
        outputs.pop();
    };
    if(is_file)
    {
        std::cout.rdbuf(shrbuf);
        ofstr.close();
    }
}
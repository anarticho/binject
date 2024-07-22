#include <Outject.h>

Outject::Outject(std::string out_file):
    shrbuf(std::cout.rdbuf()),
    ofstr(),
    is_ok(true)
{
    const bool is_file = !out_file.empty();
    if(is_file)
    { 
        ofstr.open(out_file, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
        is_ok = ofstr.is_open() && (std::cout.rdbuf(ofstr.rdbuf()), true);
    }
}

Outject::~Outject()
{
    std::cout.rdbuf(shrbuf);
    ofstr.close();
}
#include "Badject.h"

void Badject::gen_out()
{

}

bool Badject::init_xor(std::string bad_bin)
{
    bool ret = false;
    while(!ret && (cpxor != UINT8_MAX))
    {
        ret = true;
        std::string::iterator itr = bad_bin.begin();
        const std::string::iterator end = bad_bin.end();
        for(; ret && (itr != end); itr++)
        {
            const uint8_t cptmp = cpxor^(*itr);
            ret = (bad_bin.find(cptmp) == std::string::npos);
        }
        cpxor += !ret;
    };
    if(!ret)
    {
        std::cout << "[*] XOR not computed from badchar binary." << std::endl;
    }
    return ret;
}

bool Badject::chck_str(std::string bad_bin, std::string str_bin)
{
    bool ret = false;
    std::string::iterator itr = bad_bin.begin();
    while(!ret && (itr!=bad_bin.end()))
    {
        ret = (str_bin.find(*itr) != std::string::npos);
    };
    if(!ret)
    {
        std::cout << "[*] Badchar not found within provided binary." << std::endl;
    }
    return ret;
}

bool Badject::build(std::string bad_bin, std::string str_bin)
{
    Badject bad_obj;
    const bool ret = bad_obj.chck_str(bad_bin, str_bin) 
                  && bad_obj.init_xor(bad_bin);
    if(ret)
    {
        bad_obj.gen_out();
    }
    return ret;
}
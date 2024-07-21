#include "Badject.h"

void Badject::gen_xvl()
{
    static const uint8_t u64_sz8 = UINT64_WIDTH / UINT8_WIDTH;  // 8 bytes length (64-bits)  
    std::string xvl_str;
    xvl_str += cpxor;
    while(xvl_str.length() != u64_sz8)                  // fill out_obj with 0 for padding
    {
        xvl_str += '\0';
    }

    std::ofstream xvl("xvl.bin", File::wr_mode);
    xvl.write(xvl_str.c_str(), xvl_str.size());
    xvl.close();
    std::cout << "[*] xvl.bin containing computed XOR value." << std::endl;
}

void Badject::gen_esc()
{
    std::cout << "[*] Offset for detected bad characters:" << std::endl;
    std::string str_bin;
    const size_t str_sz = parms.mods.size();
    for(size_t i=0; i<str_sz; i++)
    {
        uint8_t str_c = parms.mods[i];
        if(offqe.front() == i)
        {
            std::cout << "\t- " << offqe.front() << std::endl;
            str_c ^= cpxor;
            offqe.pop();
        }
        str_bin += str_c;
    }

    std::ofstream esc("esc.bin", File::wr_mode);
    esc.write(str_bin.c_str(), str_bin.size());
    esc.close();

    std::cout << "[*] esc.bin containing XORed argument." << std::endl;
}

void Badject::gen_output()
{
    gen_xvl();  // generate xvl.bin as for XOR value as x64 format.
    gen_esc();  // generate esc.bin as for escaped bad characters.
}

bool Badject::compute_xor()
{
    bool ret = false;
    while(!ret && (cpxor != UINT8_MAX))
    {
        ret = true;
        std::string::iterator itr = parms.bads.begin();
        const std::string::iterator end = parms.bads.end();
        for(; ret && (itr != end); itr++)
        {
            const uint8_t cptmp = cpxor^(*itr);
            ret = (parms.bads.find(cptmp) == std::string::npos);
        }
        cpxor += !ret;
    };
    if(!ret)
    {
        std::cout << "[*] XOR not computed from badchar binary." << std::endl;
    }
    else
    {
    }
    return ret;
}

bool Badject::compute_str()
{
    bool ret = false;
    std::string::iterator str_itr = parms.mods.begin();
    while(str_itr != parms.mods.end())
    {
        if(parms.bads.find(*str_itr) != std::string::npos)
        {
            const uint16_t idx = std::distance(parms.mods.begin(), str_itr);
            offqe.push(idx);
            ret = true;
        }
        str_itr++;
    };
    if(!ret)
    {
        std::cout << "[*] Badchar not found within provided binary." << std::endl;
    }
    return ret;
}

bool Badject::build(std::string bad_bin, std::string str_bin)
{
    Badject bad_obj({bad_bin, str_bin});
    const bool ret = bad_obj.compute_xor()  // fix ::cpxor
                  && bad_obj.compute_str(); // fix ::offqe
    if(ret)
    {
        bad_obj.gen_output();
    }
    return ret;
}
#include <Badject.h>

#include <File.h>
#include <Logs.h>

bool Badject::build(const std::string& bad_bin, const std::string& str_bin)
{
    Badject bad_obj;
    const bool ret = bad_obj.compute_xor(bad_bin)           // fix ::cpxor
                  && bad_obj.compute_str(bad_bin, str_bin); // fix ::offqe
    if(ret)
    {
        bad_obj.gen_xvl();                  // generate XOR value into binary
        bad_obj.gen_esc(bad_bin, str_bin);  // generate escaped binary
    }
    return ret;
}

bool Badject::compute_xor(const std::string& bad_bin)
{
    bool ret = false;
    while(!ret && (cpxor != UINT8_MAX)) // iterate on [1-255]
    {
        ret = true;
        std::string::const_iterator itr = bad_bin.begin();
        const std::string::const_iterator end = bad_bin.end();
        for(; ret && (itr != end); itr++)                       // for each badchar
        {
            const uint8_t cptmp = cpxor^(*itr);                 // compute XORed 
            ret = (bad_bin.find(cptmp) == std::string::npos);   // check if result is a badchar
        }
        cpxor += !ret;  // increment computed XOR only if current one is not consistent
    };
    Logs::error("Consistent value for XOR not found.", ret);
    return ret;
}

bool Badject::compute_str(const std::string& bad_bin, const std::string& str_bin)
{
    bool ret = false;
    std::string::const_iterator itr = str_bin.begin();
    const std::string::const_iterator end = str_bin.end();
    while(itr != end)   // for each character from provided content to be XORed
    {
        if(bad_bin.find(*itr) != std::string::npos) // check if there is a badchar
        {
            const uint16_t idx = std::distance(str_bin.begin(), itr);   // compute offset of badchar within content
            offqe.push(idx);                                            // push badchar offset within content to queue
            ret = true;                                                 // return value to true, only if badchar found
        }
        itr++;  // next character within content
    };
    Logs::error("Badchar not found within provided binary.", ret);
    return ret;
}

void Badject::gen_xvl()
{
    std::string xvl_str;
    xvl_str += cpxor;
    while(xvl_str.length() != u64_sz8)                  // fill out_obj with 0 for padding
    {
        xvl_str += '\0';
    }
    File::write("xvl.bin", xvl_str);
    Logs::error("[*] xvl.bin containing computed XOR value." );
}

void Badject::gen_esc(const std::string& bad_bin, const std::string& str_bin)
{
    // to change
    std::cout << "[*] Offset for detected bad characters:" << std::endl;
    std::string str_esc;
    const size_t str_sz = str_bin.size();
    for(size_t i=0; i<str_sz; i++)
    {
        uint8_t str_c = str_bin[i];
        if(offqe.front() == i)
        {
            std::cout << "\t- " << offqe.front() << std::endl;
            str_c ^= cpxor;
            offqe.pop();
        }
        str_esc += str_c;
    }
    File::write("esc.bin", str_esc);
    std::cout << "[*] esc.bin containing XORed argument." << std::endl;
}
#include <Badchck.h>

#include <File.h>
#include <Logger.h>

bool Badchck::check(const std::string& fname)
{
    std::string data;
    const bool is_open = File::read(fname.c_str(), data);
    const std::string log_str("Checking " + fname); 
    Logger::log(log_str.c_str());
    if(is_open)
    {
        const size_t data_sz = data.length();
        for(size_t i=0; i<data_sz; i++)
        {
            std::string fnd_str = "Badchar found at ";
            if(bad_str.find(data[i]))
            {
                fnd_str += std::to_string(i);
            } 
        }
    }
    Logger::err("Failed opening file.", is_open);
    return is_open;
}
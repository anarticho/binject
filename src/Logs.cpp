#include <Logs.h>

#include <stdfw.h>

void Logs::error(const char* log_str, bool is_ok)
{
    if(!is_ok)
    {
        std::cout << "[*] " << log_str << std::endl;
    }
}
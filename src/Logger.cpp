#include <Logger.h>

#include <iostream>

const char* Logger::pre = "[*] ";

void Logger::log(const char* log_str)
{
    std::cout << pre << log_str << std::endl;
}

void Logger::err(const char* log_str, bool is_ok)
{
    (!is_ok) && (log(log_str), true);
}
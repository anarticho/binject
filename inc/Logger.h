#ifndef LOGS_H_
#define LOGS_H_

/// @brief Support to print on std::cout.
struct Logger
{
    public:
        static void log(const char* log_str);
        static void err(const char* log_str, bool is_ok);
        
    private:
        static const char* pre;

        Logger(); ///< = delete
        Logger(const Logger& orig); ///< = delete
        Logger& operator=(const Logger& orig); ///< = delete
};

#endif
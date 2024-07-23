#ifndef LOGS_H_
#define LOGS_H_

struct Logs
{
    public:
        static void error(const char* log_str, bool is_ok = true);
        
    private:
        Logs(); ///< = delete
        Logs(const Logs& orig); ///< = delete
        Logs& operator=(const Logs& orig); ///< = delete
};

#endif
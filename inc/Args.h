#ifndef ARGS_H_
#define ARGS_H_

#include <stdfw.h>

/// @brief Structure to handle the queue of arguments.
struct Args
{
    public:
        /// @brief Default constructor.
        /// @param argc Total number of arguments (path included).
        /// @param argv Array of arguments.
        Args(int argc, char* argv[]);

        /// @brief Retrieve current argument.
        /// @return Current argument.
        std::string current() const;

        /// @brief Retrieve current argument and go to next one.
        /// @return Current argument.
        std::string cunext();

        /// @brief Retrieve next argument.
        /// @return Next argument.
        std::string next();

        /// @brief Retrieve the current number of pending arguments.
        /// @return Number of elements within the queue.
        uint32_t length() const;
        
    private:
        std::queue<std::string> q_args; ///< Queue of arguments as std::string objects.

        Args(const Args& orig); ///< = delete
        Args& operator=(const Args& orig); ///< = delete
};

inline Args::Args(int argc, char* argv[]):
    q_args()
{
    for(int i=1; i<argc; i++)   // build queue for arguments
    {
        q_args.push(*(++argv));   // skip first argument (as for path)
    }   
}

inline std::string Args::current() const
{
    return q_args.front();
};

inline std::string Args::cunext()
{
    std::string ret = current();
    next();
    return ret;
}

inline std::string Args::next()
{
    q_args.pop();
    return current();
}

inline uint32_t Args::length() const
{
    return q_args.size();
}

#endif
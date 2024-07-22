#ifndef ARGS_H_
#define ARGS_H_

#include <stdfw.h>

/// @brief Structure to handle the queue of arguments.
struct Args
{
    public:
        typedef const std::string& Arg; ///< Typedef for function's parameters.

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

        /// @brief Is next.
        /// @return True if there is pending arguement.
        bool isn() const;
        
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
    q_args.pop();
    return ret;
}

inline std::string Args::next()
{
    q_args.pop();
    return current();
}

inline bool Args::isn() const
{
    return !q_args.empty();
}

#endif
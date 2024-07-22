#ifndef OUTJECT_H_
#define OUTJECT_H_

#include <stdfw.h>

/// @brief Structure to handle redirected standart C output (std::cout) through binary file (std::ofstream). 
struct Outject
{
    public:
        /// @brief Default constructor, to open file if needed, and to redirect standart C output to it.
        /// @param out_file String of file name, NULL if not needed.
        explicit Outject(std::string out_file);

        /// @brief Retrieve the state of redirecting standart C output to binary file.
        /// @return True if not needed or if suceed, else return False.
        bool has_fail() const;

        /// @brief Destructor, to close file and restablish default standart C output.
        ~Outject();

    private:
        std::streambuf* shrbuf; ///< Stream buffer.
        std::ofstream ofstr;    ///< Output file stream.
        bool is_ok;             ///< Is ok flag, to True if not needed or if suceed, else return False.

        Outject(const Outject& orig); ///< = delete
        Outject& operator=(const Outject& orig); ///< = delete
};

inline bool Outject::has_fail() const
{
    return !is_ok;
}

#endif
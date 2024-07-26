#ifndef FILE_H_
#define FILE_H_

#include <stdfw.h>

struct File
{
    public:
        static void write(const char* fname, std::string fdata);
        static bool read(const char* fname, std::string& fdata);
        
        /// @brief Create a directory of provided name.
        /// @param dname Directory name.
        /// @return True if operation succeed, else return False.
        static bool cdir(const char* dname);

        /// @brief Retrieve NULL terminated ASCII string for binary extension (.bin).
        /// @return ".bin".
        static const std::string bin_extension();

    private:
        static const std::ios_base::openmode wr_mode;

        File(); ///< = delete
        File(const File& orig); ///< = delete
        File& operator=(const File& orig);  ///< = delete    
};

#endif
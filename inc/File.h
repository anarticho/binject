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

        /// @brief Retrieve list of files within provided queue for current directory.
        /// @param bin_files Reference to the queue to be filled with found binary files.
        /// @return True if at least one file was found, else return False.
        static bool binf(std::queue<std::string>& bin_files);

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
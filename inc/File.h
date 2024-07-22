#ifndef FILE_H_
#define FILE_H_

#include <stdfw.h>

struct File
{
    public:
        static void write(const char* fname, std::string fdata);
        static bool read(const char* fname, std::string& fdata);

    private:
        static const std::ios_base::openmode wr_mode;

        File(); ///< = delete
        File(const File& orig); ///< = delete
        File& operator=(const File& orig);  ///< = delete    
};

#endif
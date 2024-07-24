#include <File.h>

using namespace std;

/// @brief Open mode for write opration.
const ios_base::openmode File::wr_mode = ios_base::out | ios_base::binary | ios_base::trunc;

void File::write(const char* fname, string fdata)
{
    ofstream xvl(fname, wr_mode);
    xvl.write(fdata.c_str(), fdata.size());
    xvl.close();
}

bool File::read(const char* fname, string& fdata)
{
    std::ifstream ifstr(fname, ifstream::binary);
    const bool ret = ifstr.is_open();
    if(ret)
    {
        std::ostringstream tmp;
        tmp << ifstr.rdbuf();
        fdata = tmp.str();
        ifstr.close();
    }
    return ret;
}

bool File::cdir(const char* dname)
{
    std::filesystem::path path(dname);
    std::error_code ec;
    return std::filesystem::create_directory(path, ec);
}
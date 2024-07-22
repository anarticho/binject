#include <File.h>

using namespace std;

/// @brief Open mode for write opration.
const ios_base::openmode File::wr_mode = ios_base::out | ios_base::binary | ios_base::trunc;

void File::write(const char* fname, std::string fdata)
{
    ofstream xvl(fname, wr_mode);
    xvl.write(fdata.c_str(), fdata.size());
    xvl.close();
}
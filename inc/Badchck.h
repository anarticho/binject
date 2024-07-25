#ifndef BADCHCK_H_
#define BADCHCK_H_

#include <stdfw.h>

class Badchck
{
    public:
        explicit Badchck(const std::string& bad_str0);

        bool check(const std::string& fname);

    private:
        const std::string& bad_str; ///< String containing bad characters.

        Badchck(const Badchck& orig); ///< = delete
        Badchck& operator=(const Badchck& orig); ///< = delete
};

inline Badchck::Badchck(const std::string& bad_str0):
    bad_str(bad_str0)
{
}

#endif
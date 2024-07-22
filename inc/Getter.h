#ifndef GETTER_H_
#define GETTER_H_

#include "Output.h"

struct Getter
{
    public:
    protected:
        typedef std::queue<Output> Outputs; ///< Type definition for vecotr of Output objects.

        /// @brief Default constructor, do nothing.
        inline Getter() {};

        /// @brief Check extension for files.
        /// @param str  String to check.
        /// @return True if extension is ".bin", else return False.
        static bool check_fext(const char* str);

        /// @brief Check, parse and store -if argument within provided Output object.
        /// @param str  File name.
        /// @param out  Output object
        /// @return False if format is invalid (or if file do not exist), else return True.
        static bool get_if0(const char* str, Output& out);

        /// @brief Check, parse and store -a argument within provided Output object.
        /// @param str  String into hexadecimal format.
        /// @param out  Output object.
        /// @return False if format is invalid, else return True.
        static bool get_x0(const char* str, Output& out);

        /// @brief Check, parse and store -x argument within provided Output object.
        /// @param str  Address as string into hexadecimal format.
        /// @param out  Output object.
        /// @return False if format is invalid, else return True.
        static bool get_a0(const char* str, Output& out);

        /// @brief Check, parse and process -of flag from provided parameter.
        /// @param str  File name.
        /// @param out  Output object.
        /// @return False if process failed, else return True.
        static bool get_of0(const char* str, Output& out);

    private:
        Getter(const Getter& orig); ///< = delete
        Getter& operator=(const Getter& orig); ///< = delete
};

#endif
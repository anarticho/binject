#ifndef GETTER_H_
#define GETTER_H_

#include <Output.h>

struct Getter
{
    public:
        /// @brief Check extension for files.
        /// @param str  String to check.
        /// @return True if extension is ".bin", else return False.
        static bool check_fext(std::string& str);

        /// @brief Check, parse and store -if argument within provided Output object.
        /// @param str  File name.
        /// @param out  Output object
        /// @return False if format is invalid (or if file do not exist), else return True.
        static bool get_if0(std::string& str, Output& out);

        /// @brief Check, parse and store -a argument within provided Output object.
        /// @param str  String into hexadecimal format.
        /// @param out  Output object.
        /// @return False if format is invalid, else return True.
        static bool get_x0(std::string& str, Output& out);

        /// @brief Check, parse and store -x argument within provided Output object.
        /// @param str  Address as string into hexadecimal format.
        /// @param out  Output object.
        /// @return False if format is invalid, else return True.
        static bool get_a0(std::string& str, Output& out);

        /// @brief Check, parse and process -of flag from provided parameter.
        /// @param str  File name.
        /// @param out  Output object.
        /// @return False if process failed, else return True.
        static bool get_of0(std::string& str, Output& out);

        /// @brief Check, parse and process -bd flag from provided parameter.
        /// @param bad Name for the file wich contain bad characters.
        /// @param str Name for the file to be XORed.
        /// @return False if process failed, else return True.
        static bool get_bd0(std::string& bad, std::string& str);

    private:
        Getter(const Getter& orig); ///< = delete
        Getter& operator=(const Getter& orig); ///< = delete
};

#endif
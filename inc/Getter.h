#ifndef GETTER_H_
#define GETTER_H_

#include <Output.h>
#include <Args.h>

struct Getter
{
    public:
        /// @brief Check extension for files.
        /// @param arg  String to check.
        /// @return True if extension is ".bin", else return False.
        static bool check_fext(Args::Arg arg);

        /// @brief Check, parse and store -if argument within provided Output object.
        /// @param arg  File name.
        /// @param out  Output object
        /// @return False if format is invalid (or if file do not exist), else return True.
        static bool get_if0(Args::Arg arg, Output& out);

        /// @brief Check, parse and store -a argument within provided Output object.
        /// @param arg  String into hexadecimal format.
        /// @param out  Output object.
        /// @return False if format is invalid, else return True.
        static bool get_x0(Args::Arg arg, Output& out);

        /// @brief Check, parse and store -x argument within provided Output object.
        /// @param arg  Address as string into hexadecimal format.
        /// @param out  Output object.
        /// @return False if format is invalid, else return True.
        static bool get_a0(Args::Arg arg, Output& out);

        /// @brief Check, parse and process -of flag from provided parameter.
        /// @param arg  File name.
        /// @param out  Output object.
        /// @return False if process failed, else return True.
        static bool get_of0(Args::Arg arg, Output& out);

        /// @brief Check, parse and process -bd flag from provided parameter.
        /// @param bad Name for the file wich contain bad characters.
        /// @param str Name for the file to be XORed.
        /// @return False if process failed, else return True.
        static bool get_bd0(Args::Arg bad, Args::Arg arg);

    private:
        Getter(const Getter& orig); ///< = delete
        Getter& operator=(const Getter& orig); ///< = delete
};

#endif
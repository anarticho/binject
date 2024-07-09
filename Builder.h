#ifndef BUILDER_H_
#define BUILDER_H_

#include "Output.h"

/// @brief Builder of Output objects from provided inputs.
class Builder
{
    public:
        /// @brief  Type definition for vecotr of Output objects.
        typedef std::queue<Output> Outputs;

        /// @brief Default constructor.
        /// @param outputs  Queue of objects to store parsed arguments.
        explicit Builder(Outputs& outputs);

        /// @brief Initialize pointer for arguments both with pointer for last element.
        /// @param ptr0 Pointer for arguments.
        /// @param end0 Pointer to the last element.
        void init(char** ptr0, const char* const end0);

        /// @brief Iterate through internal FSM.
        /// @return False if an error occured, else return True.
        bool step();

    private:
        Output out_obj;     ///< Output object, as cache.
        Outputs& out_q;     ///< Queue of Output objects.

        char** ptr;         ///< Array arguments.
        const char* end;    ///< Pointer to the last argument.

        std::map<std::string, std::function<bool ()> > func_map; ///< Map of functions to process arguments.

        /// @brief Check, parse and store ASCII string for number of occurences (in case of -n flag).
        /// @return False if format is invalid, else return True.
        bool get_n();
        
        /// @brief Check, parse and store -nx arguments within Output object.
        /// @return False if format is invalid, else return True.
        bool get_nx();

        /// @brief Check, parse and store -ns arguments within Output object.
        /// @return False if format is invalid, else return True.
        bool get_ns();

        /// @brief Check, parse and store -x argument within Output object.
        /// @return False if format is invalid, else return True.
        bool get_x();

        /// @brief Check store -s argument within Output object.
        /// @return True.
        bool get_s();

        Builder(const Builder& orig); ///< = delete
        Builder& operator=(const Builder& orig); ///< = delete
};

inline void Builder::init(char** ptr0, const char* const end0)
{
    ptr = ptr0;
    end = end0;
}

inline bool Builder::get_nx()
{
    return get_n() && get_x();
}

inline bool Builder::get_ns()
{
    return get_n() && get_s();
}

#endif
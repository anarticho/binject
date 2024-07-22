#ifndef BUILDER_H_
#define BUILDER_H_

#include <Getter.h>

/// @brief Builder of Output objects from provided inputs.
class Builder
{
    public:
        /// @brief Iterate through internal FSM.
        /// @return False if an error occured, else return True.
        bool step();

    protected:
        typedef std::queue<Output> Outputs; ///< Type definition for vecotr of Output objects.
        Outputs outputs;                    ///< Queue to store Output objects to be processed on step.
        std::queue<std::string> args;       ///< Queue to store arguments as std::string.
        
        /// @brief Default constructor.
        Builder();

    private:
        Output out_obj;     ///< Output object, as cache.

        /// Map of functions to process arguments.
        std::map<std::string, std::function<bool ()> > func_map;

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

        /// @brief Check, parse and store -a argument within Output object.
        /// @return False if format is invalid, else return True.
        bool get_a();

        /// @brief Check, parse and store -na argument within Output object.
        /// @return False if format is invalid, else return True.
        bool get_na();

        /// @brief Check, parse and store -if argument within Output object.
        /// @return False if format is invalid (or if file do not exist), else return True.
        bool get_if();

        Builder(const Builder& orig); ///< = delete
        Builder& operator=(const Builder& orig); ///< = delete
};

inline bool Builder::get_nx()
{
    args.pop();
    return get_n() && get_x();
}

inline bool Builder::get_ns()
{
    args.pop();
    return get_n() && get_s();
}

inline bool Builder::get_na()
{
    args.pop();
    return get_n() && get_a();
}

#endif
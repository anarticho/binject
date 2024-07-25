#include <Flags.h>

const Flags::type* Flags::get(Flag_id id)
{
    // assume provided id exist within defined below.
    static const Flags::type flags[nb_flags] = { "-of", "-bd", 
                                                 "-s", "-x", "-a", 
                                                 "-ns", "-nx", "-na", 
                                                 "-if"};    
    return flags + id;
}
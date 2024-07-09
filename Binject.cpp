#include "Binject.h"

Binject::Binject(int argc, char* argv[]):
    outputs(),
    builder(outputs)    // construct the builder with outputs queue
{
    (argc>=3)           // at least 3 arguments (including argv[0] executable)
    && build(argv+1);
}

bool Binject::build(char** start)
{
    bool ret = true;
    builder.init(&start);       // provide pointer to the first argument pointer
    while(ret && *start)
    {
        ret = builder.step();   // return false at error
    };
    return ret;
}

bool Binject::step()
{
    if(!outputs.empty())
    {
        Output out = outputs.front();
        out.process();
        outputs.pop();
    }
    return !outputs.empty();
}
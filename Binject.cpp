#include "Binject.h"

Binject::Binject(int argc, char* argv[]):
    outputs(),
    builder(outputs)
{
    if(argc >= 3)
    {
        build(argv+1, argv[argc - 1]);
    }
}

bool Binject::build(char** start, const char* const end)
{
    bool ret = true;
    builder.init(start, end);
    while(ret && (*start<=end))
    {
        ret = builder.step();
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
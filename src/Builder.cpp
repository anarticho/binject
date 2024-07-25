#include <Builder.h>

#include <Flags.h>

Builder::Builder(Args& args0):
    outputs(),
    build_ok(true),
    args(args0),
    out_obj()
{
    const Flags::type* flag_it = Flags::get(fmt_str);
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_s, this)));
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_x, this)));
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_a, this)));
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_ns, this)));
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_nx, this)));
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_na, this)));
    func_map.insert(std::make_pair(*flag_it++,  std::bind(&Builder::get_if, this)));
}

bool Builder::step()
{
    const bool pend = !args.current().empty();  // element pending to build

    // check first flag, then call related function.
    const bool ret = pend && (func_map.count(args.current()) != 0) && func_map.at(args.cunext())();
    if(ret)
    {
        outputs.push(out_obj);  // push built element
        out_obj.nb = 1;         // release occurences to 1
        out_obj.str.clear();    // clear working Output object
    }
    else
    {
        build_ok = !pend;   // OK flag to false if error occured at building pending element
    }
    return ret;
}

bool Builder::get_n()
{
    bool ret = true;
    try
    {
        const int tmp = std::stoi(args.cunext());
        ret = (tmp <= UINT16_MAX);
        out_obj.nb = tmp;
    }
    catch(const std::exception& e)
    {
        ret = false;
    }
    return ret;
}

bool Builder::get_x()
{
    const bool ret = Getter::get_x0(args.cunext(), out_obj);
    return ret;
}

bool Builder::get_s()
{
    out_obj.str = args.cunext();
    return true;
}

bool Builder::get_a()
{
    const bool ret = Getter::get_a0(args.cunext(), out_obj);
    return ret;     
}

bool Builder::get_if()
{
    const bool ret = Getter::get_if0(args.cunext(), out_obj);
    return ret;
}
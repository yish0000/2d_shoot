#include "Processor.h"
#include <map>
#include <stdio.h>

namespace scnet
{

std::map<int, const Processor *> &ProcessorRegister::getMap()
{
    static std::map<int, const Processor *> map;
    return map;
}

ProcessorRegister::ProcessorRegister(int type, const Processor *p)
{
    getMap()[type] = p;
}
    
const Processor *Processor::getProcessor(int type)
{
    std::map<int, const Processor *> &m = ProcessorRegister::getMap();
    std::map<int, const Processor *>::const_iterator it = m.find(type);
    return it == m.end() ? NULL : it->second;
}

}

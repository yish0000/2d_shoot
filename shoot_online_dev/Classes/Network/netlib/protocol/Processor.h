#ifndef _SC_Processor_h
#define _SC_Processor_h

#include <map>

namespace scnet
{

class Processor
{
public:
    virtual ~Processor() {}
    virtual void process(const void *data) const = 0;
    
    static const Processor *getProcessor(int type);
};

class ProcessorRegister
{
public:
    ProcessorRegister(int, const Processor *);
    template <int N>
    ProcessorRegister(int (&type)[N], const Processor *p)
    {
        std::map<int, const Processor *> &m = getMap();
        for (int i = 0; i < N; ++i)
            m[type[i]] = p;
    }
    
private:
    friend class Processor;
    static std::map<int, const Processor *> &getMap();
};

#define REGISTER_PROCESSOR(TYPE, CLASS) \
	scnet::ProcessorRegister g_ProcessorRegister_##CLASS(TYPE, new CLASS())

#define REGISTER_PROCESSOR_N(TYPEARRAY, CLASS) \
	scnet::ProcessorRegister g_ProcessorRegister_##CLASS(TYPEARRAY, new CLASS())

#define DECLARE_REGISTER_PROCESSOR(CLASS) \
	extern scnet::ProcessorRegister g_ProcessorRegister_##CLASS;\
	void* tmp_##CLASS = &g_ProcessorRegister_##CLASS

}

#endif

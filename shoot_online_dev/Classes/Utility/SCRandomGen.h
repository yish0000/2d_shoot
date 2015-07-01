#ifndef __SC_RANDOMGEN_H__
#define __SC_RANDOMGEN_H__

#include <time.h>
#include <stdlib.h>

class SCRandomGen
{
public:
    SCRandomGen();
    ~SCRandomGen();

    static void Init()
    {
        srand((unsigned)time(NULL));
    }

    //产生0-1的随机浮点数
    static float RandomUniform()
    {
        return rand() / double(RAND_MAX);
    }

    static int RandomInt(int lower, int upper)
    {
        return (rand() % (upper - lower + 1)) + lower;
    }

};
#endif
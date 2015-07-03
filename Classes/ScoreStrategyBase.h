
#ifndef __MemoryCard__ScoreStrategyBase__
#define __MemoryCard__ScoreStrategyBase__

#include <stdio.h>

#include "ScoreData.h"
#include "CardData.h"

class ScoreStrategyBase
{
public:
    virtual void execute(ScoreData* score, CardData* cardA,CardData* cardB)=0;
    
};

#endif /* defined(__MemoryCard__ScoreStrategyBase__) */

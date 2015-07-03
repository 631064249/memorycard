
#ifndef __MemoryCard__ScoreStrategy__
#define __MemoryCard__ScoreStrategy__

#include <stdio.h>
#include "ScoreStrategyBase.h"

class ScoreStrategy :public ScoreStrategyBase
{
private:
	int _continuous;
public:
	ScoreStrategy();
	virtual void execute(ScoreData* score, CardData* cardA, CardData* cardB);
};

#endif /* defined(__MemoryCard__ScoreStrategy__) */

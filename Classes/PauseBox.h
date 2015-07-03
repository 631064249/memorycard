#ifndef __MemoryCard__PauseBox__
#define __MemoryCard__PauseBox__

#include <stdio.h>
#include "cocos2d.h"
#include <functional>

USING_NS_CC;


class PauseBox :public Layer
{
protected:
	std::function<void()> _continueCallback;
	std::function<void()> _endGameCallback;

public:
	PauseBox();
	virtual ~PauseBox();

	CREATE_FUNC(PauseBox);

	virtual bool init();

	virtual void registerCallback(std::function<void()> continueCallback, std::function<void()> endGameCallback);
};


#endif /* defined(__MemoryCard__PauseBox__) */

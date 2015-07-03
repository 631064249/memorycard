#pragma once
#include "stdio.h"
#include "cocos2d.h"

USING_NS_CC;
class Energy :public Node
{
protected:
	ProgressTimer* _progress;
	Sprite* _background;
	float _percentage;
public:
	Energy();
	virtual ~Energy();

	CREATE_FUNC(Energy);
	virtual bool init();

	void updateView(int value);
};
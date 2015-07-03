#pragma once
#include "stdio.h"
#include "cocos2d.h"

USING_NS_CC;
class BackGround :public Node
{
protected:
	Sprite* _background;
public:
	BackGround();
	virtual~BackGround();

	CREATE_FUNC(BackGround);
	virtual bool init();
	virtual void update(float t);
};
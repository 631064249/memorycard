#pragma once
#include "ICard.h"


class CardFactory
{
public:
	CardFactory();
	~CardFactory();
	virtual  ICard* creatcard(int backId,int number);
};


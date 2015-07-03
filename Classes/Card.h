#pragma once
#include "cocos2d.h"
#include "ICard.h"

USING_NS_CC;
class Card:public ICard,public Node
{
public:
	Card();
	~Card();
	CREATE_FUNC(Card);
	virtual void flipToBack(const std::function<void()> &callback = nullptr);
	virtual void flipToFront(const std::function<void()> &callback = nullptr);
	virtual CardState getCardState() const;
	virtual void setCardData(CardData data);
	virtual CardData* getCardData();
protected:
	CardState _state;
	CardData _cardDate;
	CC_PROPERTY(Node*, _backImage, BackImage);
	CC_PROPERTY(Node*, _frontImage, FrontImage);
	void flipFromTo(Node* a, Node* b, const std::function<void()> &callback = nullptr);
};


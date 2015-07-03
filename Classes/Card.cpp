#include "Card.h"

Card::Card() :_backImage(nullptr), _frontImage(nullptr), _state(CardState::BACK)
{
	this->setCascadeColorEnabled(true);
}

Card::~Card()
{
	this->removeAllChildren();
}

Node* Card::getFrontImage()
{
	return _frontImage;
}

Node* Card::getBackImage()
{
	return _backImage;
}

void Card::setFrontImage(cocos2d::Node* var)
{
	if (var == nullptr)
	{
		return;
	}
	if (_frontImage != nullptr)
	{
		_frontImage->removeFromParent();
	}
	_frontImage = var;
	_frontImage->setCascadeOpacityEnabled(true);
	_frontImage->setVisible(false);
	addChild(_frontImage);
}

void Card::setBackImage(cocos2d::Node* var)
{
	if (var == nullptr)
	{
		return;
	}
	if (_backImage != nullptr)
	{
		_backImage->removeFromParent();
	}
	_backImage = var;
	_backImage->setCascadeOpacityEnabled(true);
	//_backImage->setVisible(false);
	addChild(_backImage);
}

void Card::flipFromTo(cocos2d::Node *a, cocos2d::Node *b, const std::function<void()>&callback)
{
	if (a == nullptr || b == nullptr)
	{
		return;
	}
	//初始化属性
	a->stopAllActions();
	b->stopAllActions();

	a->setVisible(true);
	a->setScale(1);

	b->setVisible(false);
	b->setScale(0);
	//B放大
	auto flipB = [a, b, callback]()
	{
		a->setVisible(false);
		b->setVisible(true);
		CallFunc* func = nullptr;
		if (callback != nullptr)
		{
			func = CallFunc::create(callback);
		}
		b->runAction(Sequence::create(ScaleTo::create(0.125, 1.0,1.0), func, NULL));
	};

	//A翻入，完成回调B
	b->runAction(Sequence::create(ScaleTo::create(0.125, 0, 1.0), CallFunc::create(flipB), NULL));
}

void Card::flipToBack(const std::function<void()>&callback)
{
	if (_state == CardState::BACK)
	{
		return;
	}
	flipFromTo(_frontImage, _backImage, callback);
	_state = CardState::BACK;
}

void Card::flipToFront(const std::function<void()>&callback)
{
	if (_state == CardState::FRONT)
	{
		return;
	}
	flipFromTo(_backImage,_frontImage,callback);
	_state = CardState::FRONT;
}

CardState Card::getCardState()const
{
	return _state;
}

void Card::setCardData(CardData data)
{
	_cardDate = data;
}
CardData* Card::getCardData()
{
	return &_cardDate;
}
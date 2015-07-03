#include "CardFactory.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Card.h"
USING_NS_CC;
CardFactory::CardFactory()
{
}


CardFactory::~CardFactory()
{
}

ICard* CardFactory::creatcard(int backId, int number)
{
	const int CardSize = 256;
	//创建背景
	if (backId < 0 || backId>8)
	{
		backId = 0;
	}
	int x = (backId % 2)*CardSize;
	int y = (backId / 2)*CardSize;
	auto backImage = Sprite::create("card_back.png",Rect(x,y,CardSize,CardSize));

	//创建正面
	auto frontImage = Node::create();
	frontImage->setContentSize(Size(CardSize, CardSize));
	frontImage->addChild(Sprite::create("card_front.png"));
	auto numberText = ui::TextAtlas::create(StringUtils::format("%d", number), "card_number.png", 140, 140, "0");
	frontImage->addChild(numberText);

	//创建卡片数据
	CardData data = {};
	data.number = number;

	//创建卡片
	auto card = Card::create();
	card->setBackImage(backImage);
	card->setFrontImage(frontImage);
	card->setCardData(data);

	card->setContentSize(backImage->getContentSize());
	return card;
}
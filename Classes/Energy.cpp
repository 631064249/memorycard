#include "Energy.h"
Energy::Energy() :_percentage(0)
{

}
Energy::~Energy()
{

}
bool Energy::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	_progress = ProgressTimer::create(Sprite::create("energy_front.png"));
	_progress->setType(cocos2d::ProgressTimer::Type::BAR);
	_progress->setMidpoint(Vec2(0, 0));
	_progress->setBarChangeRate(Vec2(1, 0));

	_background = Sprite::create("energy_back.png");

	this->addChild(_background);//Ìí¼Ó×¢ÒâË³Ğò
	this->addChild(_progress);

	this->setContentSize(_background->getContentSize());

	updateView(1000.0f);

	return true;
}
void Energy::updateView(int value)
{
	auto percent = value / 1000.0f * 100.0f;
	if (abs(percent - _percentage) > 1.0f)
	{
		_progress->runAction(EaseBackOut::create(ProgressTo::create(0.25f, percent)));
	}
	else
	{
		_progress->setPercentage(percent);
	}
	_percentage = percent;
}
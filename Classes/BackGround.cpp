#include "BackGround.h"
BackGround::BackGround()
{

}
BackGround::~BackGround()
{
	this->unscheduleUpdate();
}

bool BackGround::init()
{
	if (Node::init() == false)
	{
		return false;
	}
	_background = Sprite::create("background.png");
	_background->setAnchorPoint(Vec2(0, 0));

	Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	_background->getTexture()->setTexParameters(tp);

	auto viewsize = Director::getInstance()->getVisibleSize();
	auto rect = Rect(0, 0, viewsize.width, viewsize.height);

	_background->setTextureRect(rect);
	this->addChild(_background);
	this->scheduleUpdate();
	return true;
}

void BackGround::update(float t)
{
	Node::update(t);

	auto rect = _background->getTextureRect();
	rect.origin.x += 100.0f*t;
	rect.origin.y += 100.0f*t;
	_background->setTextureRect(rect);

}
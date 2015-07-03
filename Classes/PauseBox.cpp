
#include "PauseBox.h"
#include "ui/CocosGUI.h"

PauseBox::PauseBox()
{

}

PauseBox::~PauseBox()
{
}

bool PauseBox::init()
{
	if (Layer::init() == false) {
		return false;
	}

	auto viewSize = Director::getInstance()->getVisibleSize();


	auto background = LayerColor::create(Color4B(0, 0, 0, 200));
	auto box = ui::Scale9Sprite::create("message_box.png");
	auto continueBut = ui::Button::create("continue.png");
	auto endGameBut = ui::Button::create("end_game.png");

	box->setContentSize(Size(450, 300));
	box->setPosition(viewSize.width / 2, viewSize.height / 2);

	continueBut->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 75));
	endGameBut->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 75));

	this->setContentSize(viewSize);

	this->addChild(background);
	this->addChild(box);
	this->addChild(continueBut);
	this->addChild(endGameBut);

	continueBut->addClickEventListener([this](Ref* ref){
		if (_continueCallback != nullptr)
		{
			_continueCallback();
		}
	});

	endGameBut->addClickEventListener([this](Ref* ref){
		if (_endGameCallback != nullptr)
		{
			_endGameCallback();
		}
	});

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){return true; };
	listener->setSwallowTouches(true);

	background->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, background);


	return true;
}

void PauseBox::registerCallback(std::function<void()> continueCallback, std::function<void()> endGameCallback)
{
	_continueCallback = continueCallback;
	_endGameCallback = endGameCallback;
}


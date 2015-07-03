
#include "ChartsScene.h"
#include "UserData.h"
#include "SceneMediator.h"

ChartsScene::ChartsScene():
_background(nullptr),
_backBut(nullptr),
_newScoreTitle(nullptr),
_newScore(nullptr),
_chartsScoreTitle(nullptr)
{
    
}

ChartsScene::~ChartsScene()
{
    
}

bool ChartsScene::init()
{
    if (Layer::init()==false) {
        return false;
    }
    
    auto viewSize=Director::getInstance()->getVisibleSize();
    
    _background=BackGround::create();
    addChild(_background);
    
    _backBut=ui::Button::create("back.png");
    _backBut->setAnchorPoint(Vec2(0,1));
    _backBut->setPosition(Vec2(10,viewSize.height-10));
	_backBut->setScale(0.5);
    addChild(_backBut);
    
    _newScoreTitle=Sprite::create("new_score.png");
    _newScoreTitle->setAnchorPoint(Vec2(0,0.5f));
    _newScoreTitle->setPosition(Vec2(10,viewSize.height/2+150));
	_newScoreTitle->setScale(0.5);
    addChild(_newScoreTitle);
    
    _newScore=ui::TextAtlas::create("0", "number.png", 63, 83, "0");
    _newScore->setPosition(Vec2(viewSize.width/2,viewSize.height/2+160));
    auto newScore=UserDefault::getInstance()->getIntegerForKey(NEW_SCORE, 0);
    _newScore->setString(StringUtils::format("%d",newScore));
    this->addChild(_newScore);
    
    _chartsScoreTitle=Sprite::create("charts_score.png");
    _chartsScoreTitle->setAnchorPoint(Vec2(0,0.5f));
    _chartsScoreTitle->setPosition(Vec2(10,viewSize.height/2+100));
	_chartsScoreTitle->setScale(0.5);
    addChild(_chartsScoreTitle);
    
    for (int i=0; i<5; i++) {
        int score=UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,i).c_str(), 0);
        
        auto row=createChart(i,score);
        row->setPosition(Vec2(viewSize.width/2,viewSize.height/2+100-64*i));
		row->setScale(0.7);
        addChild(row);
    }
    
    _backBut->addClickEventListener([](Ref* ref){
        SceneMediator::getInstance()->gotoStartScene();
    });
    
    return true;
}

Node* ChartsScene::createChart(int rank,int score)
{
    auto viewSzie=Director::getInstance()->getVisibleSize();
    
    auto row=Node::create();
    auto r=ui::TextAtlas::create(StringUtils::format("%d",rank+1), "number.png", 63, 83, "0");
    
    auto s=ui::TextAtlas::create(StringUtils::format("%d",score),"number.png", 63, 83, "0");
    
    r->setAnchorPoint(Vec2(0,0.5));
    s->setAnchorPoint(Vec2(1,0.5));
    r->setPosition(Vec2(30,0));
    s->setPosition(Vec2(viewSzie.width-30,0));
    row->addChild(r);
    row->addChild(s);
    
    row->setContentSize(Size(viewSzie.width,100));
    row->setAnchorPoint(Vec2(0.5,0.5));
    return row;
}

Scene* ChartsScene::createScene()
{
    auto layer=ChartsScene::create();
    
    auto scene=Scene::create();
    
    scene->addChild(layer);
    
    return scene;
}

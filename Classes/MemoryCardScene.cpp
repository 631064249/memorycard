#include "MemoryCardScene.h"
#include "PauseBox.h"
#include "SceneMediator.h"
#include "UserData.h"
#include "MemoryCardLevel.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"



MemoryCardScene::MemoryCardScene():_scoreData({}),_nowLevelLayer(nullptr)
{
    _scoreData.energy=1000;
}

MemoryCardScene::~MemoryCardScene()
{
    this->unscheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

Scene* MemoryCardScene::createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
    auto scene = Scene::create();
    
    auto layer = MemoryCardScene::create(scoreStrategy);
    
    scene->addChild(layer);
    
    return scene;
}


MemoryCardScene* MemoryCardScene::create(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
    MemoryCardScene *scene=new MemoryCardScene();
    
    if (scene && scene->initWithScoreStrategy(scoreStrategy)) {
        scene->autorelease();
        return scene;
    }
    
    CC_SAFE_DELETE(scene);
    
    return nullptr;
}

bool MemoryCardScene::initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
    if (Layer::init()==false)
        return false;
    
	_scoreStrategy = scoreStrategy;

	

	initLevelDataList();  
	
	//停止背景音乐，这是一个缺省参数函数，传参表示是否释放音乐文件
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    initUI();
    
    newGame();
    
    this->scheduleUpdate();
    
    return true;
}

void MemoryCardScene::initLevelDataList()
{
    auto str= FileUtils::getInstance()->getStringFromFile("leveldata.csv");
    
    std::vector<std::string> rowList;
    
    char *row = strtok((char*)str.c_str(),"\n");
    while(row)
    {
        rowList.push_back(row);
        row=strtok(nullptr,"\n");
    }
    
    for (auto row=rowList.begin(); row!=rowList.end(); ++row) {
        char* rows= strtok((char*)row->c_str(),",");
        char* columns= strtok(nullptr,",");
        char* loss= strtok(nullptr,",");

        if (rows==nullptr || columns==nullptr || loss==nullptr) {
            continue;
        }

        LevelData level;
        
        level.rows= atoi(rows);
        level.columns=atoi(columns);
        level.loss=atoi(loss);
		
        if (level.rows*level.columns<=0||(level.rows*level.columns)%2!=0||level.loss<0) {
            continue;
        }
        _levelDataList.push_back(level);
        
    }
    _allLevel=static_cast<int>(_levelDataList.size());
}

void MemoryCardScene::initUI()
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

	_background = BackGround::create();
	this->addChild(_background);

	_energyBar = Energy::create();
	_energyBar->setPosition(visiblesize.width / 2, visiblesize.height - 15.0f);
	_energyBar->setScale(0.6);
	this->addChild(_energyBar);

	_scoreText = ScoreText::create();
	_scoreText->setPosition(Vec2(visiblesize.width - 20, visiblesize.height - 30));
	_scoreText->setScale(0.5);
	this->addChild(_scoreText);
    
    
	_pauseButton = ui::Button::create("pause.png"); 
    _pauseButton->setAnchorPoint(Vec2(0,1));
    _pauseButton->setPosition(Vec2(0,visiblesize.height));
    this->addChild(_pauseButton);
    
    _pauseButton->addClickEventListener([this](Ref* ref){
		
		this->unscheduleUpdate();
       
		auto pauseBox= PauseBox::create();

        pauseBox->registerCallback([this,pauseBox](){
			//继续游戏
			//重大问题，下面两行无法交换位置否则出现中断BUG
			this->scheduleUpdate();
            pauseBox->removeFromParent();
        },[](){

			//关卡中退出
            SceneMediator::getInstance()->gotoStartScene();
			//Director::getInstance()->popScene();
        });
        
        this->addChild(pauseBox);
    });
}


void MemoryCardScene::newGame()
{
    
	_nowLevel = -1;
    nextLevel();
}

void MemoryCardScene::nextLevel()
{

	_nowLevel++;
	
	if (_nowLevel >= _allLevel)
	{
		_nowLevel = 0;
	}

	_nowLevelData = _levelDataList[_nowLevel];

	Size visiblesize = Director::getInstance()->getVisibleSize();

	auto level = _nowLevelLayer = MemoryCardLevel::create(_nowLevelData);
	auto levelsize = level->getContentSize();
	level->setAnchorPoint(Vec2(0.5, 0.5));
	level->ignoreAnchorPointForPosition(false);
	level->setPosition(Vec2(visiblesize.width / 2, visiblesize.height / 2));
	auto scalex = visiblesize.width / (levelsize.width + 40);
	auto scaley = visiblesize.height / (levelsize.height + 20);

	level->setScale(2);
	level->setOpacity(0);

	level->runAction(Spawn::create(FadeIn::create(0.25), ScaleTo::create(0.25, scaley - 45.0f/levelsize.height),NULL));
	addChild(level);

	level->registerCallFunc([this](CardData* cardA, CardData* cardB)
	{
		_scoreStrategy->execute(&_scoreData, cardA, cardB);

	}, [this](){

		//重大问题，使用下面这行代码将出现中断BUG
		//_nowLevelLayer->removeFromParent();
		nextLevel();
	});
}


void MemoryCardScene::update(float t)
{
    Layer::update(t);
    
	_scoreData.energy -= this->_nowLevelData.loss*t;
	CCLOG("%f", _scoreData.energy);
    
    if (_scoreData.energy>1000) {
        _scoreData.energy=1000;
    }else if(_scoreData.energy<0){
        _scoreData.energy=0;
    }
    
    _energyBar->updateView(_scoreData.energy);
    _scoreText->updateView(_scoreData.score);
    
    if (_scoreData.energy<=0) {
        //游戏结束,记录分数
        

		//播放GAME OVER音效
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ye.mp3");

        UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, _scoreData.score);
        
        //刷新排行榜
        std::vector<int> scoreList;
        scoreList.push_back(_scoreData.score);
        
        for (int i=0; i<5; i++) {
            int score =UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,i).c_str(), 0);
            scoreList.push_back(score);
        }
        
        //排序
        std::sort(scoreList.begin(), scoreList.end(), [](int &a,int &b){
            return a>b;
        });
        
        //写入
        int rank=0;
        for (auto i=scoreList.begin(); i!=scoreList.end(); i++) {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,rank).c_str(), *i);
            rank++;
        }

		if (_scoreData.score == scoreList.at(0))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("numberOne.mp3");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gameover.wav");
		}

        this->unscheduleUpdate();
        
        SceneMediator::getInstance()->gotoChartsScene();
    }
}

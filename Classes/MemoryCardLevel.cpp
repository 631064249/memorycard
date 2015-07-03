
#include "MemoryCardLevel.h"

#include "CardFactory.h"
#include "SimpleAudioEngine.h"

MemoryCardLevel::MemoryCardLevel():_selCardA(nullptr),_selCardB(nullptr),_unfinishedCard(0)
{
    this->setCascadeOpacityEnabled(true);
}

MemoryCardLevel::~MemoryCardLevel()
{
    this->removeAllChildren();
}

MemoryCardLevel* MemoryCardLevel::create(LevelData levelData)
{
    MemoryCardLevel *cl=new MemoryCardLevel();
    
    if (cl && cl->initWithLevelData(levelData)) {
        cl->autorelease();
        return cl;
    }
    
    CC_SAFE_DELETE(cl);
    
    return nullptr;
}

bool MemoryCardLevel::initWithLevelData(LevelData levelData)
{
    if (Layer::init()==false)
        return false;
    
    if ((levelData.rows*levelData.columns)%2!=0)
        return false;
    
    _levelData=levelData;

    
    initCardLayout();
    
    initTouchEvent();
    
    return true;
}

void MemoryCardLevel::registerCallFunc(std::function<void(CardData* cardA,CardData* cardB)> pairCallback,std::function<void()> completeCallback)
{
    _pairCallback=pairCallback;
    _completeCallback=completeCallback;
}

void MemoryCardLevel::initCardLayout()
{
    //产生随机的颜色
    int backId=random(0,7);
    
    
    //初始化卡片table
    for (int row=0; row<_levelData.rows; ++row) {
        std::vector<Card*> r(_levelData.columns);
        _cardTable.push_back(r);
    }
    
    //创建卡片，并放入table
    CardFactory factory;
    int number=0;
    Vector<Card*> cardList;
    for (number=0; number<_levelData.rows*_levelData.columns; ++number) {
       //创建卡片
       Card* card=dynamic_cast<Card*>(factory.creatcard(backId,number/2));
	 
        cardList.pushBack(card);
    }
    this->_unfinishedCard=number;
    
    for (int row=0; row<_levelData.rows; ++row) 
	{
        for (int column=0; column<_levelData.columns; ++column) 
		{
			int size = cardList.size();
			//random(0.0f, 1.0f)*size  随机
			//0 不随机
			auto card = cardList.at(random(0.0f, 1.0f)*size);

			card->getCardData()->row = row;
			card->getCardData()->column = column; 
            
            cardList.eraseObject(card);
            
            //设置坐标
            int space=20;//间距
            auto cardSize=card->getContentSize();
            card->setPosition(Vec2(
                                   (cardSize.width+space)*column+cardSize.width/2,
                                   (cardSize.height+space)*row+cardSize.height/2
                                   ));
            _cardTable[row][column]=card;
            
            
            
            //添加至显示列表
            this->addChild(card);
            
            //设置图层大小
            if (column==_levelData.columns-1&&row==_levelData.rows-1) 
			{
                this->setContentSize(Size(
                                          (cardSize.width+space)*column+cardSize.width,
                                          (cardSize.height+space)*row+cardSize.height
                                     ));
				
            }
            
            
        }
    }
    
}

void MemoryCardLevel::initTouchEvent()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [&](Touch *touch,Event *event){
        
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size s = this->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            return true;
        }else{
            return false;
        }
    };
    
    listener->onTouchEnded=[&](Touch *touch,Event *event){
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        
        Card* selCard=nullptr;
        
        for (auto row=0;row<_levelData.rows;row++) {
            auto cards=_cardTable[row];
            for (auto column=0;column<_levelData.columns;column++) {
                auto card= cards[column];
                
                if (card==nullptr) {
                    continue;
                }
                
                auto size= card->getContentSize();
                auto pos=card->getPosition();
                auto rect= Rect(pos.x-size.width/2,pos.y-size.height/2,size.width,size.height);
                
                if (rect.containsPoint(locationInNode)) {
                    selCard=card;
                    break;
                }
                
            }
        }
        
        if (selCard==nullptr || _selCardA==selCard) {
            return;
        }
        
        if (_selCardA==nullptr) {
            //第一次打开
            _selCardA=selCard;
            _selCardA->flipToFront();
            
        }else{
            //第二次打开
            _selCardB=selCard;
            
            auto dataA=_selCardA->getCardData();
            auto dataB=_selCardB->getCardData();
            
            //通知外部回调
            if (_pairCallback!=nullptr) {
                this->_pairCallback(dataA,dataB);
            }
            

            
            //刷新视图
            if (dataA->number==dataB->number) {
                //配对成功，消除
                
				//播放消除音效
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ye.mp3");
                
                auto cardA=_selCardA;
                auto cardB=_selCardB;
                
                _selCardB->flipToFront([&,cardA,cardB](){
                    
                    cardA->runAction(Sequence::create( Spawn::create(FadeOut::create(0.25),ScaleTo::create(0.25, 0.25), NULL),CallFunc::create([this,cardA](){
                        
                        auto p= ParticleExplosion::create();
						p->setPosition(cardA->getPosition());
                        p->setSpeed(1200);
                        p->setSpeedVar(600);
                        p->setStartColor(Color4F(1,0,0,0.25));
                        p->setStartColorVar(Color4F(0,0,0,0.25));
                        p->setEndColor(Color4F(1,1,1,0.5));
                        p->setEndColorVar(Color4F(0.1,0.1,0.1,0.25));
                        p->setAutoRemoveOnFinish(true);
                        this->addChild(p);
                        
                        cardA->removeFromParent();
                        
                        
                    }), NULL));
                    
                    cardB->runAction(Sequence::create( Spawn::create(FadeOut::create(0.25),ScaleTo::create(0.25, 0.25), NULL),CallFunc::create([this,cardB](){
                        
                        auto p= ParticleExplosion::create();
                        p->setSpeed(1200);
                        p->setSpeedVar(600);
                        p->setStartColor(Color4F(1,0,0,0.25));
                        p->setStartColorVar(Color4F(0,0,0,0.25));
                        p->setEndColor(Color4F(1,1,1,0.5));
                        p->setEndColorVar(Color4F(0,0,0,0.25));
                        p->setPosition(cardB->getPosition());
                        p->setAutoRemoveOnFinish(true);
                        this->addChild(p);

                        
                        cardB->removeFromParent();
                    }), NULL));

                });
                
                
                
                
                
                _cardTable[dataA->row][dataA->column]=nullptr;
                _cardTable[dataB->row][dataB->column]=nullptr;
                _selCardA=nullptr;
                _selCardB=nullptr;
                this->_unfinishedCard-=2;
                
                //全部完成
                if (_unfinishedCard==0 && _completeCallback!=nullptr) {
                    _completeCallback();
                }
                
            }else{
                //配对失败
                auto cardA=_selCardA;
                auto cardB=_selCardB;
                _selCardB->flipToFront([&,cardA,cardB](){
                    cardA->flipToBack();
                    cardB->flipToBack();
                });
                
                _selCardA=nullptr;
                _selCardB=nullptr;
            }
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}



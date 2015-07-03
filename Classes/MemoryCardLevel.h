
#ifndef __MemoryCard__MemoryCardLevel__
#define __MemoryCard__MemoryCardLevel__
#include <stdio.h>
#include <functional>
#include <vector>
#include "cocos2d.h"
#include "Card.h"
#include "LevelData.h"
#include "CardData.h"

USING_NS_CC;

class MemoryCardLevel:public Layer{
    
protected:
    //配对时回调
    std::function<void(CardData* cardA,CardData* cardB)> _pairCallback;

    //消除完成时回调
    std::function<void()> _completeCallback;
    
    //关卡数据
    LevelData _levelData;
    
    //当前关卡的卡片
    std::vector<std::vector<Card*>> _cardTable;
    
    //当前选择的卡片
    Card* _selCardA;
    Card* _selCardB;
    
    //剩余卡片
    int _unfinishedCard;
public:
    
    MemoryCardLevel();
    virtual ~MemoryCardLevel();
    
    static MemoryCardLevel* create(LevelData levelData);
    
    virtual bool initWithLevelData(LevelData levelData);
    
    void registerCallFunc(std::function<void(CardData* cardA,CardData* cardB)> pairCallback,std::function<void()> completeCallback);
    
protected:
    
    void initCardLayout();
    
    void initTouchEvent();
    
};

#endif /* defined(__MemoryCard__MemoryCardLevel__) */

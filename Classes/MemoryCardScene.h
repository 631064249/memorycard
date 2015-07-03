#ifndef __MemoryCard__MemoryCardScene__
#define __MemoryCard__MemoryCardScene__

#include <stdio.h>
#include "cocos2d.h"
#include "MemoryCardLevel.h"
#include <vector>
#include "ScoreStrategyBase.h"
#include <memory>
#include "Background.h"
#include "Energy.h"
#include "ScoreText.h"

USING_NS_CC;

class MemoryCardScene:public Layer
{
    
protected:
    int _nowLevel;
    int _allLevel;
    
    std::vector<LevelData> _levelDataList;
    
    
    LevelData _nowLevelData;
    
    MemoryCardLevel* _nowLevelLayer;

    std::shared_ptr<ScoreStrategyBase> _scoreStrategy;

    ScoreData _scoreData;
    
    BackGround* _background;
    
    Energy* _energyBar;
    
    ScoreText* _scoreText;
    
    ui::Button* _pauseButton;
    
public:

    MemoryCardScene();
    virtual ~MemoryCardScene();
    
    static Scene* createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
    
    static MemoryCardScene* create(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
    
    virtual void update(float t);
    
    virtual bool initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy);
    
    virtual void initLevelDataList();
    
    virtual void initUI();
    
    virtual void newGame();
    
    virtual void nextLevel();
};
#endif /* defined(__MemoryCard__MemoryCardScene__) */

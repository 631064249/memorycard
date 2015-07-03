
#ifndef __MemoryCard__ChartsScene__
#define __MemoryCard__ChartsScene__

#include <stdio.h>
#include "cocos2d.h"
#include "BackGround.h"
#include "ui/CocosGUI.h"
#include <vector>
USING_NS_CC;

class ChartsScene:public Layer
{
protected:
    BackGround* _background;
    ui::Button* _backBut;
    
    Sprite* _newScoreTitle;
    ui::TextAtlas* _newScore;
    
    Sprite* _chartsScoreTitle;
    std::vector<Node*> _chartList;
    
    Node* createChart(int rank,int score);
public:
    ChartsScene();
    ~ChartsScene();
    
    CREATE_FUNC(ChartsScene);
    virtual bool init();
    
    static Scene* createScene();

};


#endif /* defined(__MemoryCard__ChartsScene__) */

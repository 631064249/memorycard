
#ifndef __MemoryCard__StartScene__
#define __MemoryCard__StartScene__

#include <stdio.h>

#include "cocos2d.h"
#include "BackGround.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class StartScene:public Layer
{
protected:
	BackGround* _background;
    
    Sprite* _logo;
    
    ui::Button* _startBtn;
    ui::Button* _chartBtn;
    ui::Button* _exitBtn;
    
public:
    StartScene();
    ~StartScene();
    
    CREATE_FUNC(StartScene);
    virtual bool init();
    
    static Scene* createScene();

};

#endif /* defined(__MemoryCard__StartScene__) */

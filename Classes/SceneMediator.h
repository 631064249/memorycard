
#ifndef __MemoryCard__SceneMediator__
#define __MemoryCard__SceneMediator__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class SceneMediator
{
protected:
    static SceneMediator* _instance;
    
public:
    static SceneMediator* getInstance();
    
    virtual void gotoStartScene();
    
    virtual void gotoGameScene();
    
    virtual void gotoChartsScene();
    
};

#endif /* defined(__MemoryCard__SceneMediator__) */

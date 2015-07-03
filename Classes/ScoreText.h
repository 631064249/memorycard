
#ifndef __MemoryCard__ScoreText__
#define __MemoryCard__ScoreText__

#include <stdio.h>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ScoreText:public Node
{
protected:
    
    ui::TextAtlas* _text;
    
    int _score;
    
public:
    
    ScoreText();
    
    CREATE_FUNC(ScoreText);
    
    virtual bool init();
    
    virtual void updateView(int value);
    
};


#endif /* defined(__MemoryCard__ScoreText__) */

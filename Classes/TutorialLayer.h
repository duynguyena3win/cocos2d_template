//
//  TitleLayer.hpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#ifndef __TUTORIALLAYER_H__
#define __TUTORIALLAYER_H__

#include "InputLayer.h"
#include "cocos2d.h"
USING_NS_CC;

class GameScene;
class BackgroundLayer;
class PipeObject;
class BirdObject;

class TutorialLayer : public cocos2d::Sprite
{
    enum ChildTagTutorial
    {
        ChildTagTutorial_Text,
        ChildTagTutorial_MainTutorial,
    };
    
public:
    CREATE_FUNC(TutorialLayer);
    void startGame();
    void restartGame();
    
private:
    bool init();
    
};
#endif /* __TUTORIALLAYER_H__ */

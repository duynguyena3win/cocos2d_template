//
//  TitleLayer.hpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "InputLayer.h"
#include "cocos2d.h"
USING_NS_CC;

class GameScene;
class BackgroundLayer;
class PipeObject;
class BirdObject;

class GameLayer : public cocos2d::Layer, public TouchDelegate
{
    enum ChildTagGameLayer
    {
        ChildTagInputLayer,
        ChildTagGameLayer_Back,
        ChildTagGameLayer_Pipe,
        ChildTagGameLayer_Bird,
        ChildTagGameLayer_Ground
    };
    
private:
    BackgroundLayer* _background;
    cocos2d::Vector<Node*> _pipes;
    BirdObject* _bird;
    BackgroundLayer* _backBottom;
    GameScene* _gameScene;
    
    Vec2 _startPosBird;
    float _distance2Pipe;
    float _deltaHeight;
    float _velocity;
    float _totalTime;
    float _gravity;
    bool _isCheckScore;
    
    Size _winSize;
public:
    static GameLayer* create(GameScene* gameScene);
    void startGame();
    void restartGame();
    void pauseTouched(cocos2d::Ref *sender);
    
private:
    bool init();
    void update(float delta);
    
protected:
    virtual void changeTouchStatus(InputLayer::TouchStatus status);
    virtual void changeTouchMoved(cocos2d::Point position);
    virtual void touchBegan(cocos2d::Point position);
    virtual void touchMoved(cocos2d::Point position);
    virtual void touchEnded(cocos2d::Point position);
};
#endif /* __GAMELAYER_H__ */

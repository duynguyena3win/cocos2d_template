#ifndef __INPUTLAYER_H__
#define __INPUTLAYER_H__

#include "cocos2d.h"

class TouchDelegate;
class GameScene;

class InputLayer :
public cocos2d::Layer
{
public:
    enum TouchStatus{
        TouchStatus_None    = 1 << 0,

        TouchStatus_Left    = 1 << 1,
        TouchStatus_Right   = 1 << 2,

        TouchStatus_OnMask  = (TouchStatus_Left + TouchStatus_Right),
    };

    enum ChildTags{
        ChildTagNone = 0,
        ChildTagDebug,
    };


public:
    CREATE_FUNC(InputLayer);

private:
    bool init();

protected:
    InputLayer();
    virtual ~InputLayer();


private:
    bool _isTapStart;

private:
    GameScene *getGameScene();
    bool isInGame();

private:
    TouchStatus _touchStatus;
    cocos2d::Point _movePosition;
    void setTouchStatus(cocos2d::Point touchPoint, bool isTouch = true);
    void setTouchMoved(cocos2d::Point touchPoint);

public:
    TouchStatus getTouchStatus(){ return _touchStatus; }
    void resetTouchStatus(){ _touchStatus = TouchStatus_None; }

    CC_SYNTHESIZE(TouchDelegate *, _touchDelegate, TouchDelegate);

    inline void tapStart() {
        this->onTouchEnded(NULL, NULL);
    }

//CCLayer
protected:
    // default implements are used to call script callback if exist
    virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

    // default implements are used to call script callback if exist
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent);
};

class TouchDelegate
{
public:
    virtual void setTouchStatus(InputLayer::TouchStatus status) {};
    virtual void changeTouchStatus(InputLayer::TouchStatus status) {};
    virtual void changeTouchMoved(cocos2d::Point position) {};

    virtual void touchBegan(cocos2d::Point position){};
    virtual void touchMoved(cocos2d::Point position){};
    virtual void touchEnded(cocos2d::Point position){};

    virtual void touchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent) {};
    virtual void touchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent) {};
    virtual void touchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent) {};
    virtual void touchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *pEvent) {};
};

#endif /* defined(__INPUTLAYER_H__) */


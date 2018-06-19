//
//  PauseLayer.h
//
//  Created by Goodia.Inc on 2013/09/09.
//
//

#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"
#include "ModalLayer.h"


class PauseDelegate;


class PauseLayer : public ModalLayer
{
public:
    enum ActionTags{
        ActionTagNone,
    };

    enum ChildTagPause {
        ChildTagPause_Menu,
        ChildTagPause_Home,
        ChildTagPause_Resume
    };


protected:
    PauseLayer();
    virtual ~PauseLayer();

private:
    std::function<void()> _func;

public:
    static PauseLayer * create(const std::function<void()> &func, bool isPrepare);

protected:
    bool init(const std::function<void()> &func, bool isPrepare);

private:
    PauseDelegate * _delegate;
    PauseDelegate * getDelegate() { return _delegate; };

public:
    static PauseLayer * create(PauseDelegate * delegate, bool isPrepare);

protected:
    bool init(PauseDelegate * delegate, bool isPrepare);
    
private:
    void titleTouched(cocos2d::Ref * sender);
    void resumeTouched(cocos2d::Ref * sender);
};

class PauseDelegate
{
public:
    virtual void resumeTouched(){};
    virtual void titleTouched(){};
};

#endif

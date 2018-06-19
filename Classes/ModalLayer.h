
#ifndef __MODALLAYER_H__
#define __MODALLAYER_H__

#include "cocos2d.h"


class ModalLayer : public cocos2d::Layer
{

public:
    typedef enum _ActionTags
    {
        ActionTagNone,
    } ActionTags;

    typedef enum _ChildTags
    {
        ChildTagNone = 0,
    } ChildTags;

protected:
    ModalLayer();
    virtual ~ModalLayer();

public:
    CREATE_FUNC(ModalLayer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;

public:
    virtual void menuCloseCallBack(cocos2d::Ref * sender);
};

#endif

//
//  ModalLayer.cpp
//
//  Created by Goodia.Inc on 2013/09/09.
//
//

#include "ModalLayer.h"


USING_NS_CC;

ModalLayer::ModalLayer()
{
}

ModalLayer::~ModalLayer()
{
}

bool ModalLayer::init()
{
    bool result = false;

    do
    {
        if (!Layer::init())
        {
            break;
        }

        result = true;
    } while (0);

    return result;
}

void ModalLayer::onEnter()
{
    Layer::onEnter();

    if (auto listener = EventListenerTouchOneByOne::create())
    {
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [](Touch * pTouch, Event * pEvent) {
            return true;
        };

        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    }
}

void ModalLayer::onExit()
{
    this->getEventDispatcher()->removeEventListenersForTarget(this);

    Layer::onExit();
}

void ModalLayer::menuCloseCallBack(Ref *sender)
{
    this->removeFromParentAndCleanup(true);
}

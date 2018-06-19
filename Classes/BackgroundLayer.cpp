//
//  GameLayer.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "BackgroundLayer.h"
#include "Utils.h"

BackgroundLayer* BackgroundLayer::createWithType(const char* frameName, float speed)
{
    BackgroundLayer *pRet = new BackgroundLayer();
    if (pRet && pRet->initWithType(frameName, speed))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool BackgroundLayer::initWithType(const char* frameName, float speed)
{
    _frameName = frameName;
    _speed = speed;
    
    if (!Layer::init()){
        return false;
    }
    
    for(int i=0; i<3; i++) {
        Sprite* back = Sprite::createWithSpriteFrameName(_frameName);
        back->setAnchorPoint(Vec2(0.5f, 0));
        Vec2 pos = Utils::GetCenter();
        _sizeBack = back->getBoundingBox().size;
        back->setPosition(pos.x + _sizeBack.width * i, 0);
        _backs.pushBack(back);
        this->addChild(back);
    }
    
    this->scheduleUpdate();
    return true;
}

void BackgroundLayer::update(float delta)
{
    float deltaMove = _speed * delta * 60;
    Vec2 posCenter = Utils::GetCenter();
    
    for(int i=0; i< 3; i++) {
        Sprite* back = _backs.at(i);
        back->setPositionX(back->getPositionX() - deltaMove);
        if(back->getPositionX() < -_sizeBack.width * 0.5f)
            back->setPositionX(back->getPositionX() + _sizeBack.width * 2);
    }
}

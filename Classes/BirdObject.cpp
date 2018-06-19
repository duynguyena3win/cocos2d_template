//
//  GameLayer.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "BirdObject.h"
#include "AnimateCreator.h"
#include "Utils.h"

bool BirdObject::init()
{
    if(!Sprite::initWithSpriteFrameName("sprite_bird_0.png"))
        return false;
    
    auto animFly = RepeatForever::create(AnimateCreator::createAnimate("sprite_bird_%d.png", 0, 2, 0.15f));
    animFly->setTag(111);
    this->runAction(animFly);
    
    return true;
}

void BirdObject::setDead()
{
    this->stopActionByTag(111);
}

void BirdObject::setStart()
{
    auto animFly = RepeatForever::create(AnimateCreator::createAnimate("sprite_bird_%d.png", 0, 2, 0.15f));
    animFly->setTag(111);
    this->runAction(animFly);
}

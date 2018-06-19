//
//  GameLayer.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "PipeObject.h"
#include "Utils.h"

bool PipeObject::init()
{
    if(!Node::init())
        return false;
    
    Sprite* topPipe = Sprite::createWithSpriteFrameName("img_pipe_top.png");
    topPipe->setAnchorPoint(Vec2(0.5f, 0));
    topPipe->setPosition(Vec2(0, 100));
    this->addChild(topPipe, 0);
    
    Sprite* bottomPipe = Sprite::createWithSpriteFrameName("img_pipe_bottom.png");
    bottomPipe->setAnchorPoint(Vec2(0.5f, 1));
    bottomPipe->setPosition(Vec2(0, -100));
    this->addChild(bottomPipe, 0);
    
    SizeObject = topPipe->getBoundingBox().size;
    
    return true;
}

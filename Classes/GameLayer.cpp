//
//  GameLayer.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "GameLayer.h"
#include "GameScene.h"
#include "BackgroundLayer.h"
#include "PipeObject.h"
#include "BirdObject.h"
#include "Utils.h"

GameLayer* GameLayer::create(GameScene* gameScene)
{
    GameLayer *pRet = new GameLayer();
    pRet->_gameScene = gameScene;
    if (pRet && pRet->init())
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

bool GameLayer::init()
{
    if (!Layer::init()){
        return false;
    }
    
    {
        InputLayer * layer = InputLayer::create();
        
        int tagId = ChildTagInputLayer;
        this->addChild(layer, tagId, tagId);
        
        layer->setTouchEnabled(true);
        layer->setTouchDelegate(this);
    }
    
    _background = BackgroundLayer::createWithType("back.png", 1.5f);
    this->addChild(_background, ChildTagGameLayer_Back, ChildTagGameLayer_Back);

    _distance2Pipe = 400.0f;
    _deltaHeight = 40.0f;
    _winSize = Director::getInstance()->getWinSize();
    
    Vec2 startPos = Vec2(_distance2Pipe * 3, Utils::GetCenter().y);
    
    for(int i=0; i<3; i++) {
        PipeObject* object = PipeObject::create();
        object->setPosition(startPos + Vec2(_distance2Pipe * i, 0));
        object->IsChecked = false;
        this->addChild(object, ChildTagGameLayer_Pipe, ChildTagGameLayer_Pipe);
        _pipes.pushBack(object);
    }
    
    _backBottom = BackgroundLayer::createWithType("img_ground.png", 3.0f);
    this->addChild(_backBottom, ChildTagGameLayer_Ground, ChildTagGameLayer_Ground);
    
    _bird = BirdObject::create();
    Vec2 posBird = Vec2(_winSize.width * 0.3f, _winSize.height * 0.5f);
    _bird->setPosition(posBird);
    this->addChild(_bird, ChildTagGameLayer_Bird, ChildTagGameLayer_Bird);
    restartGame();
    
    this->scheduleUpdate();
    return true;
}

void GameLayer::startGame()
{
    _isCheckScore = false;
    _totalTime = 0.0f;
    _velocity = 50.0f;
    _gravity = 9.8f;
    _startPosBird = _bird->getPosition();
    _bird->stopActionByTag(112);
}

void GameLayer::restartGame()
{
    auto moveUp = MoveBy::create(0.5f, Vec2(0, 30));
    auto seq = RepeatForever::create(Sequence::create(moveUp, moveUp->reverse(), NULL));
    seq->setTag(112);
    _bird->runAction(seq);
}

void GameLayer::update(float delta)
{
    if(_gameScene->getIsGameStart()) {
        float deltaMove = 3.0f * delta * 60;
        
        for(int i=0; i<3; i++) {
            PipeObject* pipe = (PipeObject*) _pipes.at(i);
            pipe->setPositionX(pipe->getPositionX() - deltaMove);
            Size sizePipe = pipe->SizeObject;
            float checkPoint = _winSize.width * 0.3f + pipe->SizeObject.width * 0.3f;
            if(pipe->getPositionX() < checkPoint && !pipe->IsChecked) {
                pipe->IsChecked = true;
                _gameScene->addScore();
            }
            
            if(pipe->getPositionX() < -sizePipe.width * 0.5f) {
                float posY = _winSize.height * 0.5f + random(0, 4) * _deltaHeight;
                pipe->setPosition(pipe->getPositionX() + _distance2Pipe * _pipes.size(), posY);
                pipe->IsChecked = false;
            }
        }
        
        {
            Vec2 posBird = Vec2::ZERO;
            posBird.x = _winSize.width * 0.3f;
            posBird.y = _startPosBird.y + _velocity * _totalTime - 0.5f * _gravity * _totalTime * _totalTime;
            _totalTime += 8 * delta;
            _bird->setPosition(posBird);
        }
    }
}

void GameLayer::changeTouchStatus(InputLayer::TouchStatus status)
{
    
}

void GameLayer::changeTouchMoved(cocos2d::Point position)
{
    
}

void GameLayer::touchBegan(cocos2d::Point position)
{
    _startPosBird = _bird->getPosition();
    _totalTime = 0;
}

void GameLayer::touchMoved(cocos2d::Point position)
{
}

void GameLayer::touchEnded(cocos2d::Point position)
{
}

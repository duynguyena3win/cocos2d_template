/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "GameLayer.h"
#include "TitleLayer.h"
#include "TutorialLayer.h"
#include "MenuItemSpriteFrame.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameSceneScene.cpp\n");
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    {
        _score = 0;
        _isGameStart = false;
        _isGameOver = false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    _gameLayer = GameLayer::create(this);
    this->addChild(_gameLayer, ChildTagGameScene_GameLayer, ChildTagGameScene_GameLayer);
    
    _tutorialLayer = TutorialLayer::create();
    this->addChild(_tutorialLayer, ChildTagGameScene_TutorialLayer, ChildTagGameScene_TutorialLayer);
    
    _scoreLabel = Label::createWithBMFont("font_score.fnt", "0");
    _scoreLabel->setScale(1.5f);
    Vec2 posLabel = Utils::GetCenter();
    _scoreLabel->setPosition(posLabel.x, Director::getInstance()->getWinSize().height * 0.8f);
    this->addChild(_scoreLabel, ChildTagGameScene_ScoreLabel, ChildTagGameScene_ScoreLabel);
    
    {
        MenuItem * itemPause = NULL;
        {
            const char * fileName = "btn_pause.png";
            auto btn = MenuItemSpriteFrame::create(fileName, fileName, CC_CALLBACK_1(GameScene::pauseTouched, this));
            btn->setSelectedColor(Color3B::GRAY);
            itemPause = btn;
        }
        
        {
            Menu * menu1 = NULL;
            menu1 = Menu::create(itemPause,
                                 nullptr);
            if (menu1)
            {
                Point position = Point(50.0f, winSize.height - 50.0f);
                menu1->setPosition(position);
                menu1->setEnabled(false);
                this->addChild(menu1, ChildTagGameScene_PauseMenu, ChildTagGameScene_PauseMenu);
            }
        }
    }
    return true;
}

void GameScene::addScore(int bonus)
{
    _score += bonus;
    std::string text = StringUtils::format("%d", _score);
    _scoreLabel->setString(text.c_str());
}

void GameScene::gameStart()
{
    _score = 0;
    _isGameStart = true;
    _isGameOver = false;
    
    if(_tutorialLayer)
        _tutorialLayer->startGame();
    
    if(_gameLayer)
        _gameLayer->startGame();
    
    if(this->getPauseMenu())
        this->getPauseMenu()->setEnabled(true);
}

void GameScene::gameEnd(bool clear)
{
    
}

Menu * GameScene::getPauseMenu()
{
    Node * node = this->getChildByTag(ChildTagGameScene_PauseMenu);
    return (Menu *)node;
}

void GameScene::pauseTouched(Ref* pSender)
{
    {
        int tagId = ChildTagGameScene_PauseLayer;
        PauseLayer * layer = nullptr;
        
        layer = (PauseLayer *)this->getChildByTag(tagId);
        if(!layer){
            layer = PauseLayer::create(this, false);
            this->addChild(layer, tagId, tagId);
        }
        layer->setVisible(true);
    }
    
    if(this->getPauseMenu())
        this->getPauseMenu()->setEnabled(false);
    
    if(_gameLayer)
        _gameLayer->setTouchEnabled(false);
    
    _isGameStart = false;
    Director::getInstance()->pause();
}

void GameScene::resumeTouched()
{
    this->removeChildByTag(ChildTagGameScene_PauseLayer);
    _isGameStart = true;
    
    if(this->getPauseMenu())
        this->getPauseMenu()->setEnabled(true);
    
    if(_gameLayer)
        _gameLayer->setTouchEnabled(true);
    
    Director::getInstance()->resume();
}

void GameScene::titleTouched()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleLayer::scene()));
}

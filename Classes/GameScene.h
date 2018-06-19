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

#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "PauseLayer.h"

USING_NS_CC;

class GameLayer;
class TutorialLayer;

class GameScene : public cocos2d::Scene, public PauseDelegate
{
    enum ChildTagGameScene
    {
        ChildTagGameScene_GameLayer,
        ChildTagGameScene_TutorialLayer,
        ChildTagGameScene_ScoreLabel,
        ChildTagGameScene_PauseMenu,
        ChildTagGameScene_PauseLayer,
    };
    
private:
    GameLayer* _gameLayer;
    TutorialLayer* _tutorialLayer;
    Label* _scoreLabel;
    
public:
    static cocos2d::Scene* createScene();

    bool init();
    void addScore(int bonus = 1);
    void gameStart();
    void gameEnd(bool clear);
    
    CC_SYNTHESIZE(int, _score, Score);
    CC_SYNTHESIZE(bool, _isGameStart, IsGameStart);
    CC_SYNTHESIZE(bool, _isGameOver, IsGameOver);

    Menu* getPauseMenu();
    
    void pauseTouched(cocos2d::Ref* pSender);
    void resumeTouched();
    void titleTouched();
    
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_H__

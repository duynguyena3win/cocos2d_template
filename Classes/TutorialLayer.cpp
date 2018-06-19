//
//  GameLayer.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "TutorialLayer.h"
#include "Utils.h"

bool TutorialLayer::init()
{
    if (!Sprite::init()){
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* readyText = Sprite::createWithSpriteFrameName("img_text_ready.png");
    readyText->setPosition(winSize.width * 0.5f, winSize.height * 0.7f);
    this->addChild(readyText, ChildTagTutorial_Text, ChildTagTutorial_Text);
    
    Sprite* imgTutorial = Sprite::createWithSpriteFrameName("img_tutorial.png");
    imgTutorial->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
    this->addChild(imgTutorial, ChildTagTutorial_MainTutorial, ChildTagTutorial_MainTutorial);
    
    return true;
}

void TutorialLayer::startGame()
{
    float animationTime = 0.5f;
    this->getChildByTag(ChildTagTutorial_Text)->runAction(FadeOut::create(animationTime));
    this->getChildByTag(ChildTagTutorial_MainTutorial)->runAction(FadeOut::create(animationTime));
}

void TutorialLayer::restartGame()
{
    float animationTime = 0.5f;
    this->getChildByTag(ChildTagTutorial_Text)->runAction(FadeIn::create(animationTime));
    this->getChildByTag(ChildTagTutorial_MainTutorial)->runAction(FadeIn::create(animationTime));
}

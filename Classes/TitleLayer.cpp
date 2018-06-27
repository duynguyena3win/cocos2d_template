//
//  TitleLayer.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "TitleLayer.h"
#include "GameScene.h"
#include "AnimateCreator.h"
#include "MenuItemSpriteFrame.h"
#include "Utils.h"
#include "DemoController.h"

Scene * TitleLayer::scene()
{
    return TitleLayer::create();
}

bool TitleLayer::init()
{
    if (!Scene::init()){
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size _winSize = Director::getInstance()->getWinSize();
    
    Sprite* backSprite = Sprite::createWithSpriteFrameName("back.png");
    backSprite->setPosition(visibleSize * 0.5f);
    this->addChild(backSprite, 0);
    
#ifdef  CODE_STEP_1
    Sprite* logo = Sprite::createWithSpriteFrameName("img_logo.png");
    logo->setPosition(Utils::GetCenter());
    this->addChild(logo);
#endif

#ifdef  CODE_STEP_2
    Size sizeLogo = logo->getContentSize();
    Sprite* birdIcon = Sprite::createWithSpriteFrameName("sprite_bird_0.png");
    birdIcon->setAnchorPoint(Vec2(0, 0.5f));
    birdIcon->setPosition(sizeLogo.width + 10.0f, sizeLogo.height * 0.5f);
    logo->addChild(birdIcon, 1);
#endif
    
#ifdef  CODE_STEP_3
    auto animFly = RepeatForever::create(AnimateCreator::createAnimate("sprite_bird_%d.png", 0, 2, 0.15f));
    birdIcon->runAction(RepeatForever::create(animFly));
    logo->runAction(RepeatForever::create(EaseIn::create(JumpTo::create(1.0f, logo->getPosition(), 30, 1), 1.5f)));
#endif
    
#ifdef  CODE_STEP_4
    {
        MenuItem * itemStart = NULL;
        {
            const char * fileName = "btn_start.png";
            auto btn = MenuItemSpriteFrame::create(fileName, fileName, CC_CALLBACK_1(TitleLayer::startTouched, this));
            btn->setSelectedColor(Color3B::GRAY);
            btn->setTag(ChildTagTitle_Start);
            itemStart = btn;
        }

        MenuItem * itemRanking = NULL;
        {
            const char * fileName = "btn_score.png";
            auto btn = MenuItemSpriteFrame::create(fileName, fileName, CC_CALLBACK_1(TitleLayer::rankingTouched, this));
            btn->setSelectedColor(Color3B::GRAY);
            btn->setTag(ChildTagTitle_Ranking);
            itemRanking = btn;
        }

        {
            Menu * menu1 = NULL;
            float ds = 100.0f;
            menu1 = Menu::create(itemStart,
                                 itemRanking,
                                 nullptr);
            if (menu1)
            {
                Point position = Point(_winSize.width * 0.5f, _winSize.height * 0.2f);
                menu1->alignItemsHorizontallyWithPadding(ds);
                menu1->setPosition(position);

                int tagId = ChildTagTitle_Menu;
                this->addChild(menu1, tagId, tagId);
            }
        }
    }
#endif
    
    return true;
}

void TitleLayer::startTouched(cocos2d::Ref *sender)
{
#ifdef  CODE_STEP_5
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::create()));
#endif
}

void TitleLayer::rankingTouched(cocos2d::Ref *sender)
{
}

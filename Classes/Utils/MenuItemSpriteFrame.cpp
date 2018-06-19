/****************************************************************************
 Copyright (c) 2014 QuanNguyen
 
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

#include "MenuItemSpriteFrame.h"

USING_NS_CC;

/** creates a menu item with a normal, selected and disabled image*/
MenuItemSpriteFrame * MenuItemSpriteFrame::create(const std::string& normalSprite, const std::string& selectedSprite, const std::string& disabledSprite)
{
    return MenuItemSpriteFrame::create(normalSprite, selectedSprite, disabledSprite, nullptr);
}
/** creates a menu item with a normal and selected image with target/selector
 * @lua NA
 */
MenuItemSpriteFrame * MenuItemSpriteFrame::create(const std::string& normalSprite, const std::string& selectedSprite, cocos2d::Ref* target, SEL_MenuHandler selector)
{
    return MenuItemSpriteFrame::create(normalSprite, selectedSprite, "", target, selector);
}
/** creates a menu item with a normal,selected  and disabled image with target/selector
 * @lua NA
 */
MenuItemSpriteFrame * MenuItemSpriteFrame::create(const std::string& normalSprite, const std::string& selectedSprite, const std::string& disabledSprite, Ref* target, cocos2d::SEL_MenuHandler selector)
{
    MenuItemSpriteFrame *pRet = new MenuItemSpriteFrame();
    cocos2d::SpriteFrameCache *sFC = SpriteFrameCache::getInstance();
    cocos2d::Sprite *n = nullptr;
    if(normalSprite.size() > 0){
        n = cocos2d::Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(normalSprite));
    }
    Sprite *s = nullptr;
    if(selectedSprite.size() > 0){
        s = Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(selectedSprite));
    }
    Sprite *d = nullptr;
    if(disabledSprite.size() > 0){
        d = Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(disabledSprite));
    }
    
    pRet->initWithNormalSprite(n, s, d, target, selector);
    pRet->autorelease();
    return pRet;
}

/** creates a menu item with a normal and selected image with a callable object */
MenuItemSpriteFrame * MenuItemSpriteFrame::create(const std::string& normalSprite, const std::string& selectedSprite, const cocos2d::ccMenuCallback& callback)
{
    MenuItemSpriteFrame *pRet = new MenuItemSpriteFrame();
    cocos2d::SpriteFrameCache *sFC = SpriteFrameCache::getInstance();
    Sprite *n = nullptr;
    if(normalSprite.size() > 0){
        n = cocos2d::Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(normalSprite));
    }
    Sprite *s = nullptr;
    if(selectedSprite.size() > 0){
        s = Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(selectedSprite));
    }
    
    pRet->initWithNormalSprite(n, s, nullptr, callback);
    pRet->autorelease();
    return pRet;
    
}
/** creates a menu item with a normal,selected  and disabled image with target/selector */
MenuItemSpriteFrame * MenuItemSpriteFrame::create(const std::string& normalSprite, const std::string& selectedSprite, const std::string& disabledSprite, const cocos2d::ccMenuCallback& callback)
{
    MenuItemSpriteFrame *pRet = new MenuItemSpriteFrame();
    cocos2d::SpriteFrameCache *sFC = SpriteFrameCache::getInstance();
    Sprite *n = nullptr;
    if(normalSprite.size() > 0){
        n = cocos2d::Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(normalSprite));
    }
    Sprite *s = nullptr;
    if(selectedSprite.size() > 0){
        s = Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(selectedSprite));
    }
    Sprite *d = nullptr;
    if(disabledSprite.size() > 0){
        d = Sprite::createWithSpriteFrame(sFC->getSpriteFrameByName(disabledSprite));
    }
    
    pRet->initWithNormalSprite(n, s, d, callback);
    pRet->autorelease();
    return pRet;
}


void MenuItemSpriteFrame::setSelectedScaleRatio(float scale)
{
    _selectedScaleRatio = scale;
}

void MenuItemSpriteFrame::setSelectedColor(const cocos2d::Color3B &color)
{
    _selectedColor = color;
}

const unsigned int    kZoomActionTag = 0xc0c05002;

void MenuItemSpriteFrame::selected()
{
    MenuItemSprite::selected();
    
    if(_enabled){
        Action *action = getActionByTag(kZoomActionTag);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            m_fOriginalScale.x = this->getScaleX();
            m_fOriginalScale.y = this->getScaleY();
            m_fOriginalColor = this->getColor();
        }
        
        
        Action *zoomAction = ScaleTo::create(0.1f, m_fOriginalScale.x * _selectedScaleRatio,m_fOriginalScale.y * _selectedScaleRatio);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
        
        this->setColor(_selectedColor);
    }
}

void MenuItemSpriteFrame::unselected()
{
    // subclass to change the default action
    MenuItemSprite::unselected();
    
    if(_enabled)
    {
        MenuItem::unselected();
        
        this->stopActionByTag(kZoomActionTag);
        Action *zoomAction = ScaleTo::create(0.1f, m_fOriginalScale.x, m_fOriginalScale.y);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
        
        this->setColor(m_fOriginalColor);
    }
}

void MenuItemSpriteFrame::activate()
{
    if(_enabled)
    {
        this->stopActionByTag(kZoomActionTag);
        this->setScale(m_fOriginalScale.x, m_fOriginalScale.y);
        
        this->setColor(m_fOriginalColor);
        
        MenuItem::activate();
    }
}

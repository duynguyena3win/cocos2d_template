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

#ifndef __MENUITEMSPRITEFRAME_H__
#define __MENUITEMSPRITEFRAME_H__

#include "cocos2d.h"

class MenuItemSpriteFrame : public cocos2d::MenuItemSprite {
    
public:
    /** creates a menu item with a normal, selected and disabled image*/
    static MenuItemSpriteFrame * create(const std::string& normalSprite, const std::string& selectedSprite = "", const std::string& disabledSprite = "");
    /** creates a menu item with a normal and selected image with target/selector
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSpriteFrame * create(const std::string& normalSprite, const std::string& selectedSprite, Ref* target, cocos2d::SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSpriteFrame * create(const std::string& normalSprite, const std::string& selectedSprite, const std::string& disabledSprite, Ref* target, cocos2d::SEL_MenuHandler selector);
    
    /**
     *  creates a menu item with a normal and selected image with a callable object
     */
    static MenuItemSpriteFrame * create(const std::string& normalSprite, const std::string& selectedSprite, const cocos2d::ccMenuCallback& callback);
    /**
     *  creates a menu item with a normal,selected  and disabled image with target/selector
     */
    static MenuItemSpriteFrame * create(const std::string& normalSprite, const std::string& selectedSprite, const std::string& disabledSprite, const cocos2d::ccMenuCallback& callback);
    
    
    void setSelectedScaleRatio(float scale);
    void setSelectedColor(const cocos2d::Color3B &color);
    
protected:
    MenuItemSpriteFrame(){
        _selectedScaleRatio = 1.0f;
        m_fOriginalScale = cocos2d::Vec2(1.0f, 1.0f);
        m_fOriginalColor = cocos2d::Color3B::WHITE;
        _selectedColor = cocos2d::Color3B::WHITE;
    }
    float _selectedScaleRatio;
    cocos2d::Vec2 m_fOriginalScale;
    cocos2d::Color3B m_fOriginalColor;
    cocos2d::Color3B _selectedColor;
    
    virtual void selected();
    virtual void unselected();
    virtual void activate();
    
};

#endif /* defined(__MENUITEMSPRITEFRAME_H__) */

//
//  TitleLayer.hpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#ifndef __BACKGROUNDLAYER_H__
#define __BACKGROUNDLAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer : public cocos2d::Layer
{
private:
    cocos2d::Vector<Sprite*> _backs;
    Size _sizeBack;
    const char* _frameName;
    float _speed;
    
public:
    static BackgroundLayer* createWithType(const char* frameName, float speed);
    Size getSize() { return _sizeBack; }
    
private:
    bool initWithType(const char* frameName, float speed);
    void update(float delta);
};
#endif /* __BACKGROUNDLAYER_H__ */

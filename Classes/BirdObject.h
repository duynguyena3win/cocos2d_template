//
//  TitleLayer.hpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#ifndef __BIRDOBJECT_H__
#define __BIRDOBJECT_H__

#include "cocos2d.h"
USING_NS_CC;

class BirdObject : public Sprite
{
public:
    CREATE_FUNC(BirdObject);
    Size SizeObject;
    
private:
    bool init();
    void setDead();
    void setStart();
};
#endif /* __BIRDOBJECT_H__ */

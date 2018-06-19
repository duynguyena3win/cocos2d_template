//
//  Utils.cpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#include "Utils.h"

Vec2 Utils::GetCenter()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize * 0.5f;
}

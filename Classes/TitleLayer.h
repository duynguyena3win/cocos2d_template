//
//  TitleLayer.hpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#ifndef TitleLayer_h
#define TitleLayer_h

#include "cocos2d.h"
USING_NS_CC;

class TitleLayer : public cocos2d::Scene
{
    enum ChildTagTitle {
        ChildTagTitle_Logo,
        ChildTagTitle_Menu,
        ChildTagTitle_Start,
        ChildTagTitle_Ranking,
    };
    
public:
    static Scene* scene();
    CREATE_FUNC(TitleLayer);
    
    void startTouched(cocos2d::Ref *sender);
    void rankingTouched(cocos2d::Ref *sender);
    
private:
    virtual bool init();
    
};
#endif /* TitleLayer_hpp */

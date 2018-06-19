#ifndef __AnimateCreator__
#define __AnimateCreator__

#include "cocos2d.h"

class AnimateCreator {
    
public:
    static cocos2d::Animation * createAnimation(const char * frameNameFormat,
                                                  int startIndex,
                                                  int endIndex,
                                                  float frameTime);
    
    static cocos2d::Animation * createAnimation(std::vector<std::string> frameNames,
                                                  float frameTime);
    
    
    static cocos2d::Animate * createAnimate(const char * frameNameFormat,
                                              int startIndex,
                                              int endIndex,
                                              float frameTime);
    
    static cocos2d::Animate * createAnimate(std::vector<std::string> frameNames,
                                              float frameTime);
};

#endif /* defined(__AnimateCreator__) */

#include "AnimateCreator.h"

USING_NS_CC;

Animation * AnimateCreator::createAnimation(const char * frameNameFormat,
                                              int startIndex,
                                              int endIndex,
                                              float frameTime)
{
    auto frameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame *> frames;
    
    for (int i = startIndex;
         (startIndex <= endIndex)?(i <= endIndex):(i >= endIndex);
         (startIndex <= endIndex)?(i++):(i--))
    {
        std::string frameName = StringUtils::format(frameNameFormat, i);
        
        frames.pushBack(frameCache->getSpriteFrameByName(frameName.c_str()));
    }
    
    auto animation = Animation::createWithSpriteFrames(frames, frameTime);
    animation->setRestoreOriginalFrame(false);
    
    return animation;
}

Animation * AnimateCreator::createAnimation(std::vector<std::string> frameNames,
                                              float frameTime)
{
    auto frameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame *> frames;
    
    ssize_t count = frameNames.size();
    for (int i = 0; i < count; i++)
    {
        std::string frameName = frameNames[i];
        
        frames.pushBack(frameCache->getSpriteFrameByName(frameName.c_str()));
    }
    
    auto animation = Animation::createWithSpriteFrames(frames, frameTime);
    animation->setRestoreOriginalFrame(false);
    
    return animation;
}

Animate * AnimateCreator::createAnimate(const char * frameNameFormat,
                                          int startIndex,
                                          int endIndex,
                                          float frameTime)
{
    auto animation = AnimateCreator::createAnimation(frameNameFormat,
                                                           startIndex,
                                                           endIndex,
                                                           frameTime);
    return Animate::create(animation);
}

Animate * AnimateCreator::createAnimate(std::vector<std::string> frameNames,
                                          float frameTime)
{
    auto animation = AnimateCreator::createAnimation(frameNames, frameTime);
    
    return Animate::create(animation);
}

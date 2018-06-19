//
//  TitleLayer.hpp
//  Template-mobile
//
//  Created by Apple on 6/15/18.
//

#ifndef __PIPEOBJECT_H__
#define __PIPEOBJECT_H__

#include "cocos2d.h"
USING_NS_CC;

class PipeObject : public Node
{
public:
    CREATE_FUNC(PipeObject);
    Size SizeObject;
    bool IsChecked;
    
private:
    bool init();
    
};
#endif /* __PIPEOBJECT_H__ */

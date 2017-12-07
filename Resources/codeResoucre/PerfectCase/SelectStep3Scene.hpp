//
//  SelectStep3Scene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#ifndef SelectStep3Scene_hpp
#define SelectStep3Scene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class SelectStep3Scene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectStep3Scene);
    
    cocos2d::Layer* createMessageLayer();
    
};
#endif /* SelectStep3Scene_hpp */

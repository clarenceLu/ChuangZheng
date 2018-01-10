//
//  DystoniaScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef DystoniaScene_hpp
#define DystoniaScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class DystoniaScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(DystoniaScene);
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
private:
};

#endif /* DystoniaScene_hpp */

//
//  SenseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef SenseScene_hpp
#define SenseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class SenseScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SenseScene);
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
private:
};

#endif /* SenseScene_hpp */

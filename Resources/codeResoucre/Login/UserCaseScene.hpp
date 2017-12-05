//
//  UserCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#ifndef UserCaseScene_hpp
#define UserCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class UserCaseScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(UserCaseScene);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    cocos2d::Layer* createCaseLayer();
    cocos2d::Layer* createInformLayer();
    cocos2d::Layer* createNotificationInformLayer();
};
#endif /* UserCaseScene_hpp */

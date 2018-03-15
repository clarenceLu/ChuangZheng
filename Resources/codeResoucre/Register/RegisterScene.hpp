//
//  RegisterScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/11/29.
//

#ifndef RegisterScene_hpp
#define RegisterScene_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
class RegisterScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(RegisterScene);
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    cocos2d::Layer* createCaseLayer();
    
private:
    cocos2d::ui::TextField* textFieldCase;
};


#endif /* RegisterScene_hpp */

//
//  RegisterMessageScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/11/29.
//

#ifndef RegisterMessageScene_hpp
#define RegisterMessageScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
class RegisterMessageScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(RegisterMessageScene);
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::Layer* createAlbumLayer();
    
    
};

#endif /* RegisterMessageScene_hpp */

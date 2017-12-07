//
//  SelectStep2Scene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#ifndef SelectStep2Scene_hpp
#define SelectStep2Scene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class SelectStep2Scene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectStep2Scene);
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
};

#endif /* SelectStep2Scene_hpp */

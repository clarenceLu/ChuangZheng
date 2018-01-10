//
//  ActionAbnormalScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/21.
//

#ifndef ActionAbnormalScene_hpp
#define ActionAbnormalScene_hpp
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class ActionAbnormalScene:public cocos2d::Scene{
    public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ActionAbnormalScene);
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
     float creatLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag);
};


#endif /* ActionAbnormalScene_hpp */

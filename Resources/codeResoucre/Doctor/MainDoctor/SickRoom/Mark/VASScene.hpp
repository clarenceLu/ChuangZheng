//
//  VASScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#ifndef VASScene_hpp
#define VASScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class VASScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(VASScene);
     void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
private:
    int count;
    cocos2d::ui::ListView* lv;
    
    cocos2d::ui::TextField* partField;
    cocos2d::ui::TextField* painField;
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
     cocos2d::ui::Layout * createPainView(cocos2d::Vec2 point,int i);
    
};

#endif /* VASScene_hpp */

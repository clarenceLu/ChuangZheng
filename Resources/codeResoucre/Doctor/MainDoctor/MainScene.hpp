//
//  MainScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class MainScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MainScene);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void menuLoginCallback(cocos2d::Ref* pSender);

    cocos2d::Layer* createSickRoomLayer();
    cocos2d::Layer* createOutPatientLayer();
    cocos2d::Layer* createSickInfoLayer();
     cocos2d::Layer* createCalendarLayer();
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Button* createMessageBtn(int i, cocos2d::Size  innerSize);
    
    cocos2d::LayerMultiplex *multLayer;
    
    std::shared_ptr<cocos2d::Vector<cocos2d::ui::CheckBox*>>  boxVec;
    
    cocos2d::Menu*   createRectButton(cocos2d::Vec2 point,int i);
    cocos2d::ui::ScrollView* createScrollV();
    
};
#endif /* MainScene_hpp */
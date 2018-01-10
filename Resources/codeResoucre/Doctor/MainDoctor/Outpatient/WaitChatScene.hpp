//
//  WaitChatScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#ifndef WaitChatScene_hpp
#define WaitChatScene_hpp
#include <stdio.h>
#include "ui/CocosGUI.h"
class WaitChatScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(WaitChatScene);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Layout * createMessageLayout(int i);
    
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
private:
//当isReceive为2时，选中的是接待列表，当isReceive为3时，选中的是拒绝列表
    int isReceive;
    
};

#endif /* WaitChatScene_hpp */

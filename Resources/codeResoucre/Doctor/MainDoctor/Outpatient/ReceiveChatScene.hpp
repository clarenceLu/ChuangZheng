//
//  ReceiveChatScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#ifndef ReceiveChatScene_hpp
#define ReceiveChatScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class ReceiveChatScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ReceiveChatScene);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Layout * createMessageLayout(int i);
    
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    private:
};
#endif /* ReceiveChatScene_hpp */

//
//  ChatScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/12.
//

#ifndef ChatScene_hpp
#define ChatScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class ChatScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ChatScene);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::Layer* createMessageLayer(int i, cocos2d::Size  innerSize);
};
#endif /* ChatScene_hpp */

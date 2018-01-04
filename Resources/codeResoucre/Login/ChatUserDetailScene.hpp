//
//  ChatUserDetailScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/11.
//

#ifndef ChatUserDetailScene_hpp
#define ChatUserDetailScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class ChatUserDetailScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ChatUserDetailScene);
    
    void createScrollDetailView(cocos2d::ui::ScrollView* superV);
    float createLabel(cocos2d::Vec2 point,std::string name1,std::string name2,cocos2d::Sprite* superV);
    
    //用于上传影像
    cocos2d::Layer* createUpdateImageLayer();
    //用于上传头像
    cocos2d::Layer* createAlbumLayer();
    
};

#endif /* ChatUserDetailScene_hpp */

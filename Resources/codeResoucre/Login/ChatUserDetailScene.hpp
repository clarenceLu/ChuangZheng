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
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
class ChatUserDetailScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(ChatUserDetailScene);
    
    void createScrollDetailView(cocos2d::ui::ScrollView* superV);
    float createLabel(cocos2d::Vec2 point,std::string name1,std::string name2,cocos2d::Sprite* superV);
    
    //用于上传影像
    cocos2d::Layer* createUpdateImageLayer();
    //用于上传头像
    cocos2d::Layer* createAlbumLayer();
    
    rapidjson::Document infoData;
    
    
    std::string searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data);
private:
    cocos2d::ui::ScrollView* scrollView;
    
     rapidjson::Document contentData;
    
    
    void getUserDataToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
};

#endif /* ChatUserDetailScene_hpp */

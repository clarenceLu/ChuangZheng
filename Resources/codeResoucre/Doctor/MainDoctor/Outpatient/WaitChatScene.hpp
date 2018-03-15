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

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class WaitChatScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    
    CREATE_FUNC(WaitChatScene);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Layout * createMessageLayout(int i);
    
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void createContentWithRapidjsonValueData(rapidjson::Value&data,cocos2d::Sprite* bkView);
    
    
private:
//当isReceive为2时，选中的是接待列表，当isReceive为3时，选中的是拒绝列表
    int isReceive;
    rapidjson::Document infoData;
    rapidjson::Document waitingData;
    rapidjson::Document refuseData;
    cocos2d::ui::ListView* lv;
    
    
};

#endif /* WaitChatScene_hpp */

//
//  MarkScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#ifndef MarkScene_hpp
#define MarkScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class MarkScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(MarkScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    std::string searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data);
    
    
    void pushRisserToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
    
    cocos2d::Layer* createSelectLayer();
    void createSelectItem(std::string title,float Y,cocos2d::Sprite* contentV);
    
    
private:
    cocos2d::ui::ListView* lv;
    rapidjson::Document infoData;
    rapidjson::Document asiaData;
    rapidjson::Document VASData;
    
    std::string risserStr;
};

#endif /* MarkScene_hpp */

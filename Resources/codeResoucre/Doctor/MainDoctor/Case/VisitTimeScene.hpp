//
//  VisitTimeScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/16.
//

#ifndef VisitTimeScene_hpp
#define VisitTimeScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class VisitTimeScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(VisitTimeScene);
    void createSelectTime(cocos2d::Sprite*contentV,int tag,cocos2d::Vec2 origin,std::string month);
     cocos2d::Layer* createPromptLayer(std::string content);
    
     void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
private:
    rapidjson::Document infoData;
    std::string contentStr;
};

#endif /* VisitTimeScene_hpp */

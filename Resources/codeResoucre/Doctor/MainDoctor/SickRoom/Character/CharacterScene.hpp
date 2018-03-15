//
//  CharacterScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef CharacterScene_hpp
#define CharacterScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class CharacterScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(CharacterScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    std::string searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data);
    
    
private:
    cocos2d::ui::ListView* lv;
    rapidjson::Document infoData;
    rapidjson::Document actionData;
    rapidjson::Document dystoniaUpData;
     rapidjson::Document dystoniaDownData;
    rapidjson::Document appearanceData1;
    rapidjson::Document appearanceData2;
    rapidjson::Document appearanceData3;
    rapidjson::Document appearanceData4;
    rapidjson::Document appearanceData5;
    rapidjson::Document appearanceData6;
    rapidjson::Document reflectAbnormalData;
    rapidjson::Document reflectData;
    rapidjson::Document senseData;
    
     rapidjson::Document spineData;
    
};

#endif /* CharacterScene_hpp */

//
//  OutpatientCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#ifndef OutpatientCaseScene_hpp
#define OutpatientCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class OutpatientCaseScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(OutpatientCaseScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    void createTextFieldView(cocos2d::ui::Layout* contentV);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    
    Size calculateFontSize(const char *str );
    
    cocos2d::ui::ScrollView* createImageScroll(cocos2d::Vec2 origin,Size visibleSize);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void getCaseInfoToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void getUserDataToNetWork();
    std::string searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data);
private:
    cocos2d::ui::ListView* lv;
    
    rapidjson::Document infoData;
    rapidjson::Document userData;
    //impression
    rapidjson::Document impressData;
    rapidjson::Document formationData;
    rapidjson::Document infectData;
    rapidjson::Document injuryData;
};

#endif /* OutpatientCaseScene_hpp */

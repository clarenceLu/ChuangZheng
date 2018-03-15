//
//  CaseHistoryScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#ifndef CaseHistoryScene_hpp
#define CaseHistoryScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class CaseHistoryScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(CaseHistoryScene);
    void  createLabelWithoutField(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name,int tag);
    void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    cocos2d::Layer* addCaseLayer();
    
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushCaseDetailToNetWork();
    
    void createContentView();
    void createContentCaseView();
    
//用于传值
    std::string patientId;
    std::string caseId;
private:
    
    cocos2d::Sprite *bkView;
    
    rapidjson::Document infoData;
    rapidjson::Document caseData;
};

#endif /* CaseHistoryScene_hpp */

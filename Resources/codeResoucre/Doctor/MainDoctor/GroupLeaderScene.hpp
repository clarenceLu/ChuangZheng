//
//  GroupLeaderScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/28.
//

#ifndef GroupLeaderScene_hpp
#define GroupLeaderScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class GroupLeaderScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GroupLeaderScene);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void menuLoginCallback(cocos2d::Ref* pSender);
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    float creatBlueLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    float createPopUpView(cocos2d::Vec2 point,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    
    cocos2d::Layer* createPromptLayer(std::string content);
    
    
#pragma-用于加载数据
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushMemberToNetWork();
    
    void onHttpRequestCompleted3(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDeleteToNetWork(std::string doctorId);
    
    void onHttpRequestCompleted4(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushAffirmToNetWork(std::string requestId,std::string doctorId);
    
    
private:
    rapidjson::Document applicationData;
    rapidjson::Document memberData;
    rapidjson::Document deleteData;
    rapidjson::Document affirmData;
    
    
    int currentDeleteIndex;
    
    //用于存储数据
    ValueMap map1;
    Map<int, Sprite*> wholeDic;
    Map<int, cocos2d::ui::CheckBox*> boxDic;
    cocos2d::ui::ScrollView *scrollV;
    Sprite *moveView;
};
#endif /* GroupLeaderScene_hpp */

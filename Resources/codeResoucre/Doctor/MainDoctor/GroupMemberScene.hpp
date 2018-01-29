//
//  GroupLeaderScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/28.
//

#ifndef GroupMemberScene_hpp
#define GroupMemberScene_hpp


#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class GroupMemberScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GroupMemberScene);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void menuLoginCallback(cocos2d::Ref* pSender);
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    float creatBlueLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    float createPopUpView(cocos2d::Vec2 point,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    
    cocos2d::Layer* createPromptLayer(std::string content);
    void showServerMessage( std::string ch );
    
#pragma-用于加载数据
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushMemberToNetWork();
    
    void onHttpRequestCompleted3(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushJoinToNetWork(std::string groupId);
    
    
    
private:
    rapidjson::Document applicationData;
    rapidjson::Document memberData;
    rapidjson::Document joinData;
    
    int currentJoinIndex;
    
    //用于存储数据
    ValueMap map1;
    Map<int, Sprite*> wholeDic;
    Map<int, cocos2d::ui::CheckBox*> boxDic;
    cocos2d::ui::ScrollView *scrollV;
    Sprite *moveView;
};
#endif /* GroupLeaderScene_hpp */

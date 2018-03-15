//
//  MessageNotificationScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/31.
//

#ifndef MessageNotificationScene_hpp
#define MessageNotificationScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class MessageNotificationScene:public cocos2d::Scene{
    public:
        static  cocos2d::Scene* createScene();
        virtual bool init();
        void menuLoginCallback(cocos2d::Ref* pSender);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
        CREATE_FUNC(MessageNotificationScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    cocos2d::ui::Layout *createMessageLayout(int i,rapidjson::Value& object);
    
    cocos2d::Layer* createPromptLayer(std::string content);
    
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void deleteRemindToNetWork(int  reminderId);
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
    private:
    rapidjson::Document infoData;
    int typeForData;//1为通知 ,0位提醒
    
    cocos2d::ui::ListView* lv;
    
    Vector<cocos2d::ui::CheckBox*> boxVec;
    Map<int, cocos2d::ui::CheckBox*> boxDic;
//    std::shared_ptr<cocos2d::Vector<cocos2d::ui::CheckBox*>>  boxVec;
};

#endif /* MessageNotificationScene_hpp */

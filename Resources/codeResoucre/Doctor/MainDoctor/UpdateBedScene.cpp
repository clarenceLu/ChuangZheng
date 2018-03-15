//
//  UpdateBedScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/15.
//

#include "UpdateBedScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *UpdateBedScene::createScene(){
    return UpdateBedScene::create();
}

bool UpdateBedScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    
    return true;
}


#pragma-绑定床位
void UpdateBedScene::updateBedToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/updateBed?patientId=%s&caseId=%s&bedId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted2, this),nullptr);
}

void UpdateBedScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    //    rapidjson::Document Jsondata;
    infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (infoData.HasParseError()) {
        return;
    }
    if(infoData.HasMember("status")){
        if (infoData["status"].GetInt()==0) {
            rapidjson::Value& object = infoData["data"];
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            infoData.Accept(writer);
            CCLOG("%s", buffer.GetString());
        }
    }
}



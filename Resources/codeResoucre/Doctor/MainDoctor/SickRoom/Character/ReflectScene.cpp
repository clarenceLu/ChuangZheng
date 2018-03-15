//
//  ReflectScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "ReflectScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ReflectScene::createScene(){
    return ReflectScene::create();
}
bool ReflectScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_reflect.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    this->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_step4_sure.png", "btn_step4_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-80, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            pushDataToNetWork();
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    createSelectView(1, bkView, 875,"Hoffman征阳性");
    createSelectView(3, bkView, 755,"Babinski征阳性");
    createSelectView(5, bkView, 635,"踝阵挛阳性");
    
    return true;
}

void ReflectScene::createSelectView(int tag,Sprite*bkView,float originY,string title){
    auto senseLB = Label::createWithSystemFont(title,"Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,originY+50));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("L","Arial",35,Size(80,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, originY));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, originY));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ReflectScene::checkBoxCallback,this));
    addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("R","Arial",35,Size(80,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(184, originY));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(264, originY));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(ReflectScene::checkBoxCallback,this));
    addChild(refuseBox);
    boxDic.insert(tag+1, refuseBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,originY-15));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV8);
    
}



void ReflectScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            if (tag>=1&&tag<3) {
                for (int i=1; i<3; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
            else  if (tag>=3&&tag<5) {
                for (int i=3; i<5; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
            else  if (tag>=5&&tag<7) {
                for (int i=5; i<7; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
        {
        }
            break;
        default:
            break;
    }
}

std::string ReflectScene::getJsonData(int type)
{
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    if (type==0) {
        document.SetArray();
        for (int i=1; i<3; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==1){//两侧不对称
        document.SetArray();
        for (int i=3; i<5; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==2){//肌肉萎缩
        document.SetArray();
        for (int i=5; i<7; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void ReflectScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    sprintf(jsonStr,"%s;%s;%s",getJsonData(0).c_str(),getJsonData(1).c_str(),getJsonData(2).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"tz_ycfs_Hoffman;tz_ycfs_Babinski;tz_ycfs_hzl",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(ReflectScene::onHttpRequestCompleted, this),url);
}

void ReflectScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    if(!response -> isSucceed()){
        log("response failed");
        log("error buffer: %s", response -> getErrorBuffer());
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    rapidjson::Document jsondata;
    
    jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (jsondata.HasParseError()) {
        
        return;
    }
    if(jsondata.HasMember("status")){
        if (jsondata["status"].GetInt()==0) {
            Director::getInstance()->popScene();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}




string ReflectScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 1:case 3:case 5:
            content="L";
            break;
        case 2:case 4:case 6:
            content="R";
            break;
            
        default:
            break;
    }
    return content;
}




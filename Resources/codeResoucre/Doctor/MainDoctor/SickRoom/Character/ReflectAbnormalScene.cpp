//
//  ReflectAbnormalScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "ReflectAbnormalScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ReflectAbnormalScene::createScene(){
    return ReflectAbnormalScene::create();
}
bool ReflectAbnormalScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_reflect_abnormal.png");
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
    
    createSelectView(1, bkView, 875,"肱二头肌反射");
    createSelectView(4, bkView, 755,"肱三头肌反射");
    createSelectView(7, bkView, 635,"桡骨膜反射");
     createSelectView2(10, bkView, 515,"提睾反射");
    createSelectView2(12, bkView, 395,"肛门反射");
    createSelectView2(14, bkView, 275,"腹壁反射");
    createSelectView(16, bkView, 155,"膝跳反射");
    createSelectView(19, bkView, 35,"跟腱反射");
    
    return true;
}
void ReflectAbnormalScene::createSelectView(int tag,Sprite*bkView,float originY,string title){
    auto senseLB = Label::createWithSystemFont(title,"Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,originY+50));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("亢进","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, originY));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, originY));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("活跃","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(214, originY));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(294, originY));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(refuseBox);
    boxDic.insert(tag+1, refuseBox);
    
    auto otherLB= Label::createWithSystemFont("未引出","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    otherLB->setPosition(Vec2(374, originY));
    otherLB->setTextColor(Color4B(0,0,0, 255/3*2));
    otherLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(otherLB);
    auto otherBox = CheckBox::create("select_circle.png","select_sure.png");
    otherBox->setPosition(Vec2(484, originY));
    otherBox->setAnchorPoint(Vec2(0, 0));
    otherBox->setTag(tag+2);
    otherBox->setTouchEnabled(true);
    otherBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(otherBox);
    boxDic.insert(tag+2, otherBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,originY-15));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(575, 2.5));
    bkView->addChild(lineV8);
    
}

void ReflectAbnormalScene::createSelectView2(int tag,Sprite*bkView,float originY,string title){
    auto senseLB = Label::createWithSystemFont(title,"Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,originY+50));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("L未引出","Arial",35,Size(180,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, originY));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(194, originY));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("R未引出","Arial",35,Size(180,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(284, originY));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(424, originY));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(refuseBox);
    boxDic.insert(tag+1, refuseBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,originY-15));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(575, 2.5));
    bkView->addChild(lineV8);
    
}



void ReflectAbnormalScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    log("tag:%d",tag);
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            if (tag>=1&&tag<4) {
                for (int i=1; i<4; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=4&&tag<7) {
                for (int i=4; i<7; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=7&&tag<10) {
                for (int i=7; i<10; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=10&&tag<12) {
                for (int i=10; i<12; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=12&&tag<14) {
                for (int i=12; i<14; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=14&&tag<16) {
                for (int i=14; i<16; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=16&&tag<19) {
                for (int i=16; i<19; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=19&&tag<22) {
                for (int i=19; i<22; i++) {
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



std::string ReflectAbnormalScene::getJsonData(int type)
{
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    if (type==0) {
        document.SetArray();
        for (int i=1; i<4; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==1){//两侧不对称
        document.SetArray();
        for (int i=4; i<7; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==2){//肌肉萎缩
        document.SetArray();
        for (int i=7; i<10; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==3){
        document.SetArray();
        for (int i=10; i<12; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==4){
        document.SetArray();
        for (int i=12; i<14; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==5){
        document.SetArray();
        for (int i=14; i<16; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==6){
        document.SetArray();
        for (int i=16; i<19; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==7){
        document.SetArray();
        for (int i=19; i<22; i++) {
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
void ReflectAbnormalScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    sprintf(jsonStr,"%s;%s;%s;%s;%s;%s;%s;%s",getJsonData(0).c_str(),getJsonData(1).c_str(),getJsonData(2).c_str(),getJsonData(3).c_str(),getJsonData(4).c_str(),getJsonData(5).c_str(),getJsonData(6).c_str(),getJsonData(7).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"tz_slyc_he;tz_slyc_hs;tz_slyc_jgm;tz_slyc_fb;tz_slyc_tg;tz_slyc_gm;tz_slyc_qt;tz_slyc_gj",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(ReflectAbnormalScene::onHttpRequestCompleted, this),url);
}

void ReflectAbnormalScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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




string ReflectAbnormalScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 1: case 4: case 7: case 16: case 19:
            content="亢进";break;
        case 2: case 5: case 8: case 17: case 20:
            content="活跃";break;
        case 3: case 6: case 9: case 18: case 21:
            content="未引出";break;
        case 10: case 12: case 14:
            content="L未引出";break;
            //双侧不对称
        case 11: case 13: case 15:
            content="R未引出";break;
            
        default:
            break;
    }
    return content;
}




//
//  SelectStep2Scene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#include "SelectStep2Scene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SelectStep2Scene::createScene(){
    return SelectStep2Scene::create();
}
bool SelectStep2Scene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_step2.png");
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
    sureBtn->loadTextures("btn_step2_sure.png", "btn_step2_sure.png");
    sureBtn->setPosition(Vec2(185, 474));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.86);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
           pushDataToNetWork();
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    textFieldContent= TextField::create("一百字以内","Arial",35);
    textFieldContent->setMaxLength(240);
//用于多行输入
    textFieldContent->ignoreContentAdaptWithSize(false);
    textFieldContent->setTouchSize(Size(visibleSize.width-80, 300));
    textFieldContent->setPosition(Vec2(40,visibleSize.height-250));
    textFieldContent->setAnchorPoint(Vec2(0,1));
    textFieldContent->setContentSize(Size(visibleSize.width-80,300));
    textFieldContent->setTextColor(Color4B::BLACK);
    textFieldContent->setPlaceHolderColor(Color4B::GRAY);
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->addEventListener(CC_CALLBACK_2(SelectStep2Scene::eventCallBack, this));
    bkView->addChild(textFieldContent);
    
    return true;
};



void SelectStep2Scene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    switch (type){
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("DETACH_WITH_IME");
            
            break;
    }
}


#pragma-用于加载网络数据
void SelectStep2Scene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string content="";
    if (strcmp("", textFieldContent->getString().c_str())) {
        log("length:%d,%s",textFieldContent->getStringLength(),textFieldContent->getString().c_str());
        content=textFieldContent->getString();
    }
    char memberUrl[1000]={0};
    sprintf(memberUrl,"userId=%s&step2=%s",UserDefault::getInstance()->getStringForKey("userId").c_str(),content.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateCase";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(SelectStep2Scene::onHttpRequestCompleted, this),url);
}

void SelectStep2Scene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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



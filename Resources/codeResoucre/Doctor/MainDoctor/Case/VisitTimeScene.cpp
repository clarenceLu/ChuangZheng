//
//  VisitTimeScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/16.
//

#include "VisitTimeScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *VisitTimeScene::createScene(){
    return VisitTimeScene::create();
}
bool VisitTimeScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_visit_time.png");
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
    sureBtn->loadTextures("btn_group_leader_sure.png", "btn_group_leader_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            for (int i=0; i<7; i++) {
                CheckBox*box=(CheckBox*)this->getChildByTag(i);
                if (box->getSelectedState()) {
                    char str[50];
                    sprintf(str,"随访时间为%d个月后吗",box->getTag()+1);
                    string title=str;
                    if (box->getTag()==6) {
                        title="随访时间为12个月后吗";
                    }
                    auto layer=createPromptLayer(title);
                    layer->setTag(2001);
                    this->addChild(layer);
                }
            }
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    createSelectTime(bkView, 0, Vec2(51, visibleSize.height-150-65), "1");
    createSelectTime(bkView, 1, Vec2(51, visibleSize.height-150-65*2), "2");
     createSelectTime(bkView, 2, Vec2(51, visibleSize.height-150-65*3), "3");
     createSelectTime(bkView, 3, Vec2(51, visibleSize.height-150-65*4), "4");
     createSelectTime(bkView, 4, Vec2(51, visibleSize.height-150-65*5), "5");
     createSelectTime(bkView, 5, Vec2(51, visibleSize.height-150-65*6), "6");
     createSelectTime(bkView, 6, Vec2(51, visibleSize.height-150-65*7), "12");
    
    
    return true;
}
void  VisitTimeScene::createSelectTime(Sprite*contentV,int tag,Vec2 origin,string month){
     Size visibleSize=Director::getInstance()->getVisibleSize();
    auto timeBox = CheckBox::create("alpha.png","bk_visittime_gray.png");
    timeBox->setAnchorPoint(Vec2(0, 0));
    timeBox->setPosition(origin);
    timeBox->setScale(0.85);
    timeBox->setTag(tag);
    timeBox->setTouchEnabled(true);
    timeBox->addEventListener(CC_CALLBACK_2(VisitTimeScene::checkBoxCallback,this));
    addChild(timeBox);
    auto monthLB= Label::createWithSystemFont(month,"Arial",40,Size(100,65),TextHAlignment::CENTER,TextVAlignment::CENTER);
    monthLB->setPosition(Vec2(200, origin.y));
    monthLB->setTextColor(Color4B(91, 144, 229, 255));
    monthLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(monthLB);
    auto monthLB2= Label::createWithSystemFont("个月后","Arial",40,Size(160,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    monthLB2->setPosition(Vec2(300, origin.y));
    monthLB2->setTextColor(Color4B(91, 144, 229, 255));
    monthLB2->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(monthLB2);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, origin.y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    contentV->addChild(lineV);
    
}
cocos2d::Layer* VisitTimeScene::createPromptLayer(std::string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255/3));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    auto contentV = Sprite::create("bk_group_leader_prompt.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(120, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            pushDataToNetWork();
            this->removeChildByTag(2001);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(2001);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto contentLB=Label::createWithSystemFont(content,"Arial",36,Size(contentV->getContentSize().width-40,120),TextHAlignment::CENTER,TextVAlignment::CENTER);
    contentLB->setPosition(Vec2(20,120));
    contentLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(contentLB);
    
    return layer;
}

void VisitTimeScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    //     bool selected  = checkBox->getSelectedState();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:{
            for (int i=0; i<7; i++) {
                CheckBox*box=(CheckBox*)this->getChildByTag(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }

            contentStr="";
            if (tag==6) {//赋值
                contentStr.append(to_string(12));
            }else{
            contentStr.append(to_string(tag+1));
            }
            contentStr.append("个月后将要随访，请提前做好准备");
            break;
        }
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:{
            contentStr="";
            log("UNSELECTED!");
            break;}
        default:
            break;
    }
}

#pragma-设置随访时间
void VisitTimeScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    
    char memberUrl[1000]={0};
    sprintf(memberUrl,"patientId=%s&doctorId=%s&context=%s",UserDefault::getInstance()->getStringForKey("patientId").c_str(),UserDefault::getInstance()->getStringForKey("id").c_str(),contentStr.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/patientInform";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(VisitTimeScene::onHttpRequestCompleted, this),url);
}

void VisitTimeScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    // rapidjson::Document Jsondata;
    
    this->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        if (this->infoData["status"].GetInt()==0) {
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}

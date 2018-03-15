//
//  SenseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "SenseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SenseAbnormalScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SenseScene::createScene(){
    return SenseScene::create();
}
bool SenseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_sense.png");
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
    
    auto senseLB = Label::createWithSystemFont("感觉","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,927));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("减退","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, 857));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, 857));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(1);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(SenseScene::checkBoxCallback,this));
    addChild(acceptBox);
    boxDic.insert(1, acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("消失","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(214, 857));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(294, 857));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(2);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(SenseScene::checkBoxCallback,this));
    addChild(refuseBox);
    boxDic.insert(2, refuseBox);
    
    auto allLB= Label::createWithSystemFont("过敏","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    allLB->setPosition(Vec2(374, 857));
    allLB->setTextColor(Color4B(0,0,0, 255/3*2));
    allLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(allLB);
    auto allBox = CheckBox::create("select_circle.png","select_sure.png");
    allBox->setPosition(Vec2(454, 857));
    allBox->setAnchorPoint(Vec2(0, 0));
    allBox->setTag(3);
    allBox->setTouchEnabled(true);
    allBox->addEventListener(CC_CALLBACK_2(SenseScene::checkBoxCallback,this));
    addChild(allBox);
    boxDic.insert(3, allBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,842));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV8);
    
    auto otherLB = Label::createWithSystemFont("符合神经支配皮区分布","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    otherLB->setPosition(Point(54,770));
    otherLB->setTextColor(Color4B(91,144,230, 255));
    otherLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(otherLB);
    
    auto confirmBtn=Button::create();
    confirmBtn->loadTextures("btn_sense_sure.png", "btn_sense_sure.png");
    confirmBtn->setPosition(Vec2(167, 714));
    confirmBtn->setScale(0.87);
    confirmBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Director::getInstance()->popScene();
        }
            
        default:
            break;
    }
    });
    this->addChild(confirmBtn);
    
    auto cancelBtn=Button::create();
    cancelBtn->loadTextures("btn_sense_cancel.png", "btn_sense_cancel.png");
    cancelBtn->setPosition(Vec2(335, 714));
    cancelBtn->setScale(0.87);
    cancelBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Director::getInstance()->popScene();
        }
            
        default:
            break;
    }
    });
    this->addChild(cancelBtn);
    
    
    
    return true;
}
void SenseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            for (int i=1; i<4; i++) {
                CheckBox*box=(CheckBox*)this->getChildByTag(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
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



std::string SenseScene::getJsonData(int type)
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    for (int i=1; i<4; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
            document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void SenseScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    sprintf(jsonStr,"%s",getJsonData(0).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"tz_gjyc_gj",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(SenseScene::onHttpRequestCompleted, this),url);
    
}

void SenseScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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

string SenseScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 1:
            content="减退";
            break;
        case 2:
            content="消失";
            break;
        case 3:
            content="过敏";break;//神经根型颈椎病
            
            
        default:
            break;
    }
    return content;
}



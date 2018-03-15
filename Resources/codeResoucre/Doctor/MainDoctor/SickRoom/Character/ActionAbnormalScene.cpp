//
//  ActionAbnormalScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/21.
//

#include "ActionAbnormalScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ActionAbnormalScene::createScene(){
    return ActionAbnormalScene::create();
}
bool ActionAbnormalScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_action_abnormal.png");
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
        case ui::Widget::TouchEventType::ENDED:{
            pushDataToNetWork();
            
        }
            
        default:
            break;
    }
    });
    bkView->addChild(sureBtn);
    float pointY1 =creatLabelView(Vec2(59, visibleSize.height-200), bkView, "步态不稳",1);
    float pointY2=creatLabelView(Vec2(59, pointY1-50), bkView, "平车/轮椅推入",2);
    float pointY3=creatLabelView(Vec2(59, pointY2-50), bkView, "限制体位",3);
    
    return true;
}

float ActionAbnormalScene::creatLabelView(Vec2 point,Sprite* bkView,string name,int tag){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto box = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(visibleSize.width-100,point.y+2));
    box->setScale(0.87);
    box->setAnchorPoint(Vec2(0, 0));
    box->setTag(tag);
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(ActionAbnormalScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(box);
    boxDic.insert(tag, box);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-10));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    return point.y-20;
}

void ActionAbnormalScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED");
            break;
        default:
            break;
    }
}




std::string ActionAbnormalScene::getJsonData(int type)
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
void ActionAbnormalScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    sprintf(jsonStr,"%s;%s;%s;%s",getJsonData(0).c_str(),getJsonData(1).c_str(),getJsonData(2).c_str(),getJsonData(3).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"tz_xdyc",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(ActionAbnormalScene::onHttpRequestCompleted, this),url);
    
}

void ActionAbnormalScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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

string ActionAbnormalScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 1:
            content="步态不稳";
            break;
        case 2:
            content="平车/轮椅推入";
            break;
        case 3:
            content="限制体位";break;//神经根型颈椎病
            
            
        default:
            break;
    }
    return content;
}

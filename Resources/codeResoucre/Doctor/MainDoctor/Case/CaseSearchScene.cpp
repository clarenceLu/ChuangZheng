//
//  CaseSearchScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#include "CaseSearchScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "CaseListScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *CaseSearchScene::createScene(){
    return CaseSearchScene::create();
}
bool CaseSearchScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_case_search.png");
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
            pushDataToNetWork();
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    //二维码
    auto judgeBtn=Button::create();
    judgeBtn->loadTextures("btn_caseSearch_next.png", "btn_caseSearch_next.png");
    judgeBtn->setPosition(Vec2(visibleSize.width-85, 415));
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            
        }
        default:
            break;
    }
    });
    bkView->addChild(judgeBtn);
    
    
     textFiledName=createBasicData(bkView, Vec2(56, 910), "姓名：","未填写");
    textFiledSex=createBasicData(bkView, Vec2(56, 820), "性别：","男/女");
    textFiledAge=createBasicData(bkView, Vec2(56, 730), "年龄：","未填写");
    textFiledCase=createBasicData(bkView, Vec2(56, 640), "病案号：","未填写");
    
//住院区间
    auto userName = Label::createWithSystemFont("住院区间：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(Vec2(56, 550));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    textFiledDate1 = TextField::create("2017/08/05","Arial",35);
    textFiledDate1->setMaxLength(40);
    textFiledDate1->setTouchSize(Size(visibleSize.width-300, 50));
    textFiledDate1->setPosition(Vec2(visibleSize.width-70,500));
    textFiledDate1->setAnchorPoint(Vec2(1,0));
    textFiledDate1->setContentSize(Size(visibleSize.width-300,50));
    textFiledDate1->setTextColor(Color4B::BLACK);
    textFiledDate1->setPlaceHolderColor(Color4B::GRAY);
    textFiledDate1->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFiledDate1->addEventListener(CC_CALLBACK_2(CaseSearchScene::eventCallBack, this));
    bkView->addChild(textFiledDate1);
    
    auto separateLB = Label::createWithSystemFont("至","Arial",35,Size(80,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    separateLB->setPosition(Vec2(visibleSize.width/2, 500));
    separateLB->setTextColor(Color4B(91, 144, 229, 255));
    separateLB->setAnchorPoint(Vec2(0.5, 0));
    bkView->addChild(separateLB);
    
    textFiledDate2 = TextField::create("2017/06/05","Arial",35);
    textFiledDate2->setMaxLength(40);
    textFiledDate2->setTouchSize(Size(visibleSize.width-300, 50));
    textFiledDate2->setPosition(Vec2(56,500));
    textFiledDate2->setAnchorPoint(Vec2(0,0));
    textFiledDate2->setContentSize(Size(visibleSize.width-300,50));
    textFiledDate2->setTextColor(Color4B::BLACK);
    textFiledDate2->setPlaceHolderColor(Color4B::GRAY);
    textFiledDate2->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFiledDate2->addEventListener(CC_CALLBACK_2(CaseSearchScene::eventCallBack, this));
    bkView->addChild(textFiledDate2);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(50, 490));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    
    createLabelWithoutField(bkView,Vec2(56, 410),"二维码：");
    
    return true;
}
void  CaseSearchScene::createLabelWithoutField(Sprite* bkView,Vec2 point,string name){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(50, point.y-15));
    lineV->setAnchorPoint(Vec2(0, 0));
     lineV->setScaleX(0.85);
    bkView->addChild(lineV);
}
TextField*  CaseSearchScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name1,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto textFieldUser = TextField::create(name2,"Arial",35);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(visibleSize.width-300, 50));
    textFieldUser->setPosition(Vec2(visibleSize.width-70,point.y));
    textFieldUser->setAnchorPoint(Vec2(1,0));
    textFieldUser->setContentSize(Size(visibleSize.width-300,50));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->addEventListener(CC_CALLBACK_2(CaseSearchScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-15));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}
void CaseSearchScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    int tag= textField->getTag();
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            if (tag>=1000&&tag<=1002) {
                
            }
            CCLOG("DETACH_WITH_IME");
            break;
    }
}
#pragma-用于加载网络数据
void CaseSearchScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string content="";    int count=0;
    if (strcmp( textFiledName->getString().c_str(), "")!=0) {
        content.append("name=");  content.append(textFiledName->getString()); count++;
    }
    if (strcmp( textFiledSex->getString().c_str(), "")!=0) {
        if (strcmp(textFiledSex->getString().c_str(), "男") ==0) {
            if (count==0) {
                content.append("gender=");  content.append("M");}else{content.append("&gender=");  content.append("M");}
        }else if(strcmp(textFiledSex->getString().c_str(), "女") ==0){
            if (count==0) {
                content.append("gender=");  content.append("F");}else{content.append("&gender=");  content.append("F");}
        } count++;
    }
    if (strcmp( textFiledAge->getString().c_str(), "")!=0) {
        if (count==0) {content.append("age=");}else{content.append("&age=");}  content.append(textFiledAge->getString());count++;
    }
    if (strcmp( textFiledCase->getString().c_str(), "")!=0) {
        if (count==0) {content.append("caseNum=");}else{content.append("&caseNum=");}  content.append(textFiledCase->getString());count++;
    }
    if (strcmp( textFiledDate1->getString().c_str(), "")!=0) {
        if (count==0) {content.append("startTime=");}else{content.append("&startTime=");}  content.append(textFiledDate1->getString());count++;
    }
    if (strcmp( textFiledDate2->getString().c_str(), "")!=0) {
        if (count==0) {content.append("endtime=");}else{content.append("&endtime=");}  content.append(textFiledDate2->getString());count++;
    }
    char memberUrl[1000]={0};
    sprintf(memberUrl,"%s",content.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/searchCase";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(CaseSearchScene::onHttpRequestCompleted, this),url);
    
    
    
   /* char memberUrl[500]={0};
    string name="";
    if (textFiledName->getString().length()) {
        name=textFiledName->getString();
    }
    string gender="";
    if (textFiledSex->getString().length()) {
        if (textFiledSex->getString()=="男") {
            gender="M";
        }else if(textFiledSex->getString()=="女"){
        gender="F";
        }
    }
    string age="";
    if (textFiledAge->getString().length()) {
        age=textFiledAge->getString();
    }
    string caseNum="";
    if (textFiledCase->getString().length()) {
        caseNum=textFiledCase->getString();
    }
    string startTime="";
    if (textFiledDate1->getString().length()) {
        startTime=textFiledDate1->getString();
    }
    string endTime="";
    if (textFiledDate2->getString().length()) {
        endTime=textFiledDate2->getString();
    }
    sprintf(memberUrl,"http://czapi.looper.pro/web/searchCase?name=%s&gender=%s&caseNo=%s&age=%s&starttime=%s&endtime=%s",name.c_str(),gender.c_str(),caseNum.c_str(),age.c_str(),startTime.c_str(),endTime.c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(CaseSearchScene::onHttpRequestCompleted, this),nullptr);  */
}

void CaseSearchScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
            auto scene=(CaseListScene*)CaseListScene::createScene();
            scene->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
            Director::getInstance()->pushScene(scene);
//            rapidjson::Value& object = this->infoData["data"];
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}



//
//  AddVisitCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#include "AddVisitCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "VisitCaseScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *AddVisitCaseScene::createScene(){
    return AddVisitCaseScene::create();
}
bool AddVisitCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_add_visist.png");
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
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_addCase_add.png", "btn_addCase_add.png");
    addBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
        if (strcmp(textfieldName->getString().c_str(), "")!=0&&strcmp(textfieldAge->getString().c_str(), "")!=0&&strcmp(sexLB.c_str(), "")!=0) {
                getUserDataToNetWork();
            }
//            auto SC=(VisitCaseScene*)VisitCaseScene::createScene();
//            Director::getInstance()->pushScene(SC);
        }
        default:
            break;
    }
    });
    this->addChild(addBtn);
    
    
    auto importCompleteBtn=Button::create();
    importCompleteBtn->loadTextures("import_complete_info.png", "import_complete_info.png");
    importCompleteBtn->setPosition(Vec2(visibleSize.width/2, 600));
    importCompleteBtn->setScale(0.87);
    importCompleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            
        }
        default:
            break;
    }
    });
    this->addChild(importCompleteBtn);
    
    
    
    textfieldName=createBasicData(bkView, Vec2(59, 910), "用户名：", "张牧之");
    
    auto Sex = Label::createWithSystemFont("性别","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Sex->setPosition(Vec2(59, 820));
    Sex->setTextColor(Color4B(91, 144, 229, 255));
    Sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Sex);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51,810));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    auto manCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    manCheckBox->setPosition(Vec2(340, 822));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(50);
    //设置CheckBox是否可点击
    manCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    manCheckBox->addEventListener(CC_CALLBACK_2(AddVisitCaseScene::checkBoxCallback,this));
    addChild(manCheckBox);
    auto manLB= Label::createWithSystemFont("男","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    manLB->setPosition(Vec2(380, 822));
    manLB->setTextColor(Color4B::GRAY);
    manLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(manLB);
    
    auto womanCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    womanCheckBox->setPosition(Vec2(460, 822));
    womanCheckBox->setTag(51);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    womanCheckBox->setTouchEnabled(true);
    womanCheckBox->addEventListener(CC_CALLBACK_2(AddVisitCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(womanCheckBox);
    auto womanLB= Label::createWithSystemFont("女","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    womanLB->setPosition(Vec2(500, 822));
    womanLB->setTextColor(Color4B::GRAY);
    womanLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(womanLB);
    
    textfieldAge=createBasicData(bkView, Vec2(59, 730), "年龄：", "32");
    
    return true;
}

TextField*  AddVisitCaseScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
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
    textFieldUser->addEventListener(CC_CALLBACK_2(AddVisitCaseScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-11));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}

//实现CheckBox回调函数
void AddVisitCaseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    MenuItem* item = (MenuItem*)ref;
    int tag= item->getTag();
    CheckBox *checkBox;
    if (tag==50) {
        checkBox=(CheckBox*)this->getChildByTag(51);
    }else{
        checkBox=(CheckBox*)this->getChildByTag(50);
    }
    //     bool selected  = checkBox->getSelectedState();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            if (tag==50) {sexLB="M";}     else{sexLB="F";}
            log("SELECTED!");
            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            sexLB="";
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}


void AddVisitCaseScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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
#pragma-个人资料界面
void AddVisitCaseScene::getUserDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"userId=%s",textfieldName->getString().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/getUserById";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(AddVisitCaseScene::onHttpRequestCompleted2, this),url);
}

void AddVisitCaseScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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
    userData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (userData.HasParseError()) {
        return;
    }
    if(userData.HasMember("status")){
        if (userData["status"].GetInt()==0) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            userData.Accept(writer);
            CCLOG("病人个人资料：  %s", buffer.GetString());
            if (userData["data"]!=false) {
                createCaseToNetWork();
            }else{
                getUserInfoToNetWork();
            }
        }else{
            getUserInfoToNetWork();
        }
    }
}

//新建用户
std::string AddVisitCaseScene::getTimeForSystem(){
    //获取系统时间
    struct timeval now;
    struct tm *time;
    gettimeofday(&now, NULL);
    time = localtime(&now.tv_sec);      //microseconds: 微秒
    int year = time->tm_year +1900;
    log("year = %d", year);         //显示年份
    char date1[32] = {0};
    sprintf(date1, "%d %02d %02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday);
    log("%s", date1);        //显示年月日
    char date2[50] = {0};
    sprintf(date2, "%02d %02d %02d", (int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
    log("%s", date2);       //显示时分秒
    char date[100] = {0};
    sprintf(date, "%d%d%d%d%d%d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday,(int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
    return date;
}
void AddVisitCaseScene::getUserInfoToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"userId=%s&passwd=%s&name=%s&sex=%s&age=%s&caseNo=%s",textfieldName->getString().c_str(),"123456",textfieldName->getString().c_str(),sexLB.c_str(),textfieldAge->getString().c_str(),getTimeForSystem().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/createUser";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(AddVisitCaseScene::onHttpRequestCompleted, this),url);
}

void AddVisitCaseScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    userData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (userData.HasParseError()) {
        
        return;
    }
    if(userData.HasMember("status")){
        if (userData["status"].GetInt()==0) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        userData.Accept(writer);
        CCLOG("%s", buffer.GetString());
            createCaseToNetWork();
        }
    }
}

#pragma-新建病例
void AddVisitCaseScene::createCaseToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string keyValue="";
    if (!userData["data"]["step2"].IsNull()) {
        keyValue.append("&remark=");
        keyValue.append(userData["data"]["step2"].GetString());
    }
    char memberUrl[1000]={0};
    sprintf(memberUrl,"patientId=%s&doctorId=%s&type=%s&status=%s%s",userData["data"]["id"].GetString(),UserDefault::getInstance()->getStringForKey("id").c_str(),"new","followed",keyValue.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    UserDefault::getInstance()->setStringForKey("patientId",userData["data"]["id"].GetString());
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(AddVisitCaseScene::onHttpRequestCompleted3, this),url);
}

void AddVisitCaseScene::onHttpRequestCompleted3(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
     rapidjson::Document Jsondata;
    
    Jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (Jsondata.HasParseError()) {
        
        return;
    }
    if(Jsondata.HasMember("status")){
        if (Jsondata["status"].GetInt()==0) {
            UserDefault::getInstance()->setStringForKey("caseId", Jsondata["recordId"].GetString());
            auto SC=(VisitCaseScene*)VisitCaseScene::createScene();
            Director::getInstance()->pushScene(SC);
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        Jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}

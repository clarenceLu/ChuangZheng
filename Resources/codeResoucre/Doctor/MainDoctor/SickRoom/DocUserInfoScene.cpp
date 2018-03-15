//
//  DocUserInfoScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "DocUserInfoScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *DocUserInfoScene::createScene(){
    return DocUserInfoScene::create();
}
bool DocUserInfoScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    bkView=Sprite::create("bk_doctor_userInfo.png");
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
            updatePatientInfoToNetWork();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto headImageBtn=Button::create();
    headImageBtn->loadTextures("bk_headIV.png", "bk_headIV.png");
    float height=headImageBtn->getContentSize().height;
    headImageBtn->setPosition(Vec2(52, 830));
    headImageBtn->setAnchorPoint(Vec2(0, 0));
    headImageBtn->setScale(141.0/height);
    headImageBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *headLayer= createAlbumLayer();
            headLayer->setTag(200);
            this->addChild(headLayer);
        }
        default:
            break;
    }
    });
    this->addChild(headImageBtn);

    pushDataToNetWork();
    return true;
}

void DocUserInfoScene::createContentViewWithBkView(){
    rapidjson::Value&data=infoData["data"];
    auto userName = Label::createWithSystemFont("用户名：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(Point(233,886));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    string userId="未知";
    if (!data["userId"].IsNull()) {
        userId=data["userId"].GetString();
    }
    auto userName2 = Label::createWithSystemFont(userId,"Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName2->setPosition(Vec2(360,886));
    userName2->setTextColor(Color4B(40, 40, 40, 255));
    userName2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName2);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(210, 880));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.6);
    bkView->addChild(lineV);
    
    auto sex = Label::createWithSystemFont("性别：","Arial",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    sex->setPosition(Point(233,822));
    sex->setTextColor(Color4B(91, 144, 229, 255));
    sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(sex);
    
    auto age = Label::createWithSystemFont("年龄：","Arial",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    age->setPosition(Point(412,822));
    age->setTextColor(Color4B(91, 144, 229, 255));
    age->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(age);
    
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(210, 816));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setScaleX(0.6);
    bkView->addChild(lineV2);
    
    
    string gender="男";
    if (!data["sex"].IsNull()) {
        if (strcmp(data["sex"].GetString(),"F")==0) {
            gender="女";
        }else if(strcmp(data["sex"].GetString(),"M")==0){
            gender="男";
        }
    }
    textFieldSex = TextField::create(gender,"Arial",35);
    textFieldSex->setMaxLength(40);
    textFieldSex->setTouchSize(Size(80, 50));
    textFieldSex->setPosition(Vec2(340,822));
    textFieldSex->setAnchorPoint(Vec2(0,0));
    textFieldSex->setContentSize(Size(80,50));
    textFieldSex->setTextColor(Color4B::BLACK);
    textFieldSex->setPlaceHolderColor(Color4B::GRAY);
    textFieldSex->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldSex->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldSex);

    string ageStr="未知";
    if (!data["age"].IsNull()) {
        ageStr=data["age"].GetString();
    }
    textFieldAge = TextField::create(ageStr,"Arial",35);
    textFieldAge->setMaxLength(40);
    textFieldAge->setTouchSize(Size(120, 50));
    textFieldAge->setPosition(Vec2(530,822));
    textFieldAge->setAnchorPoint(Vec2(0,0));
    textFieldAge->setContentSize(Size(120,50));
    textFieldAge->setTextColor(Color4B::BLACK);
    textFieldAge->setPlaceHolderColor(Color4B::GRAY);
    textFieldAge->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldAge->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldAge);
    
    string nameStr="未知";
    if (!data["name"].IsNull()) {  nameStr=data["name"].GetString();  }
    textfieldName=createBasicData(bkView, Vec2(59, 758), "真实姓名：", nameStr);
    string caseNoStr="未知";
    if (!data["caseNo"].IsNull()) {  caseNoStr=data["caseNo"].GetString();  }
    textfieldNum=createBasicData(bkView, Vec2(59, 688), "病案号：",caseNoStr);
    string caseId="未知";
    if (!data["number"].IsNull()) {  caseId=UserDefault::getInstance()->getStringForKey("caseId");  }
    textfieldCase=createBasicData(bkView, Vec2(59, 618), "病历号：", caseId);
    textfieldSponsor=createBasicData(bkView, Vec2(59, 548), "介绍人：", "未填写");
    textfieldRecommend=createBasicData(bkView, Vec2(59, 478), "推荐人：", "未填写");
    string phone="未知";
    if (!data["phone"].IsNull()) {  phone=data["phone"].GetString();  }
    textfieldTel1=createBasicData(bkView, Vec2(59, 408), "电话：", phone);
    string phone1="未知";
    if (!data["phone1"].IsNull()) {  phone1=data["phone1"].GetString();  }
    textfieldTel2=createBasicData(bkView, Vec2(59, 338), "电话2：", phone1);
    string phone2="未知";
    if (!data["phone2"].IsNull()) {  phone2=data["phone2"].GetString();  }
    textfieldTel3=createBasicData(bkView, Vec2(59, 268), "电话3：", phone2);
}


TextField*  DocUserInfoScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
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
    textFieldUser->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}



//上传头像
Layer* DocUserInfoScene::createAlbumLayer(){
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
    auto contentV = Sprite::create("update_album.png");
    contentV->setAnchorPoint(Vec2(0,1));
    contentV->setPosition(Vec2(57,visibleSize.height-300));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto cameraBtn=Button::create();
    cameraBtn->setScale9Enabled(true);
    cameraBtn->setPosition(Vec2(0, 88));
    cameraBtn->setAnchorPoint(Vec2(0,0));
    cameraBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    cameraBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(cameraBtn);
    
    auto albumBtn=Button::create();
    albumBtn->setScale9Enabled(true);
    albumBtn->setPosition(Vec2(0, 168));
    albumBtn->setAnchorPoint(Vec2(0,0));
    albumBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    albumBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(albumBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(111, 15));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->cocos2d::Node::setScale(0.87);
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(200);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    
    return layer;
}

void DocUserInfoScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
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
#pragma-查询病人信息
void DocUserInfoScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getUserById?patientId=%s",UserDefault::getInstance()->getStringForKey("patientId").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(DocUserInfoScene::onHttpRequestCompleted, this),nullptr);
}

void DocUserInfoScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
            createContentViewWithBkView();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}
#pragma-backBtn更新个人信息
void DocUserInfoScene::updatePatientInfoToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    string name="";if(strcmp("未知", textfieldName->getPlaceHolder().c_str())){name=textfieldName->getPlaceHolder();};
    if (strcmp("", textfieldName->getString().c_str())) {
        name=textfieldName->getString();
    }
    string gender="";if(strcmp("未知", textFieldSex->getPlaceHolder().c_str())){gender=textFieldSex->getPlaceHolder();};
    if (strcmp("", textFieldSex->getString().c_str())==0) {
        if (strcmp(textFieldSex->getPlaceHolder().c_str(), "男")==0) {
            gender="M";
        }else if(strcmp(textFieldSex->getPlaceHolder().c_str(), "女")==0){
            gender="F";
        }
    }
    if (strcmp("", textFieldSex->getString().c_str())) {
        if (strcmp(textFieldSex->getString().c_str(), "男")==0) {
            gender="M";
        }else if(strcmp(textFieldSex->getString().c_str(), "女")==0){
            gender="F";
        }
    }
    string age="";if(strcmp("未知", textFieldAge->getPlaceHolder().c_str())){age=textFieldAge->getPlaceHolder();};
     if (strcmp("", textFieldAge->getString().c_str())) {
        age=textFieldAge->getString();
    }
    string tel1="";if(strcmp("未知", textfieldTel1->getPlaceHolder().c_str())){tel1=textfieldTel1->getPlaceHolder();};
      if (strcmp("", textfieldTel1->getString().c_str())) {
        tel1=textfieldTel1->getString();
    }
    string tel2="";if(strcmp("未知", textfieldTel2->getPlaceHolder().c_str())){tel2=textfieldTel2->getPlaceHolder();};
      if (strcmp("", textfieldTel2->getString().c_str())) {
        tel2=textfieldTel2->getString();
    }
    string tel3="";if(strcmp("未知", textfieldTel3->getPlaceHolder().c_str())){tel3=textfieldTel3->getPlaceHolder();};
      if (strcmp("", textfieldTel3->getString().c_str())) {
        tel2=textfieldTel3->getString();
    }
    sprintf(memberUrl,"userId=%s&name=%s&sex=%s&phone=%s&phone1=%s&phone2=%s&age=%s",infoData["data"]["userId"].GetString(),name.c_str(),gender.c_str(),tel1.c_str(),tel2.c_str(),tel3.c_str(),age.c_str());
    string memberURL="http://czapi.looper.pro/web/updatePersonalInfo";
    char* url=memberUrl;
    
    
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(DocUserInfoScene::onHttpRequestCompleted2, this),url);
}

void DocUserInfoScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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
    
        rapidjson::Document updateData;
    
    updateData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (updateData.HasParseError()) {
        
        return;
    }
    if(updateData.HasMember("status")){
        if (updateData["status"].GetInt()==0) {
            Director::getInstance()->popScene();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        updateData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}



//
//  WelcomeScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#include "WelcomeScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "MainScene.hpp"
#include "NetWrokMangerData.hpp"


using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *WelcomeScene::createScene(){
    return WelcomeScene::create();
}
bool WelcomeScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_welcome.png");
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
    
    auto contentV=Sprite::create("welcome_content.png");
    contentV->setPosition(Vec2(20, 543));
    contentV->setAnchorPoint(Vec2(0, 0));
    contentV->setContentSize(Size(visibleSize.width-40, 429));
    bkView->addChild(contentV);
    
    string detail="您的信息是否正确？正确请进行下一步。如有问题，请联系后台及时纠正\n电话：123-456789";
    auto detailLB = Label::createWithSystemFont(detail,"Arial",30,Size(560,140),TextHAlignment::LEFT,TextVAlignment::CENTER);
    detailLB->setPosition(Vec2(20,10));
    detailLB->setTextColor(Color4B(0, 0, 0, 255/2));
    detailLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(detailLB);
    
    auto name = Label::createWithSystemFont("姓名：","Arial",40,Size(120,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    name->setPosition(Vec2(20,265));
    name->setTextColor(Color4B(91, 144, 229, 255));
    name->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(name);
    auto nameLB= Label::createWithSystemFont(UserDefault::getInstance()->getStringForKey("name"),"Arial",40,Size(450,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    nameLB->setPosition(Vec2(150,265));
    nameLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    nameLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(nameLB);
    
    
    auto job = Label::createWithSystemFont("身份：","Arial",40,Size(120,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    job->setPosition(Vec2(20,180));
    job->setTextColor(Color4B(91, 144, 229, 255));
    job->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(job);
    auto jobLB = Label::createWithSystemFont(getEducationFromRole(UserDefault::getInstance()->getStringForKey("role")),"Arial",40,Size(450,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    jobLB->setPosition(Vec2(150,180));
    jobLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    jobLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(jobLB);
    
    auto nextBtn=Button::create();
    nextBtn->loadTextures("btn_welcome_next.png", "btn_welcome_next.png");
    nextBtn->setPosition(Vec2(197, 413));
    nextBtn->setAnchorPoint(Vec2(0, 0));
    nextBtn->setScale(0.87);
    nextBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto mainScene=MainScene::createScene();
            Director::getInstance()->pushScene(mainScene);
        }
        default:
            break;
    }
    });
    this->addChild(nextBtn);
 
    return true;
}
string WelcomeScene::getEducationFromRole(std::string role){
    if (role=="1") {
        return "带组教授";
    }else if(role=="2"){
        return "主治医生";
    }else if (role=="3"){
        return "住院医生";
    }else{
        return "研究生";
    }
    return "医生";
}

void WelcomeScene::onEnter(){
    Scene::onEnter();
//     pushDataToNetWork();
}

std::string WelcomeScene::getJsonData()
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
//    document.AddMember("recordId", "108", allocator);
    
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value array2(rapidjson::kArrayType);
    rapidjson::Value array3(rapidjson::kArrayType);
    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("no", 1, allocator);
    object.AddMember("content", "hello", allocator);
    object.AddMember("state", true, allocator);
//    array.PushBack(object, allocator);
    array.PushBack("无敌是夺目寂寞", allocator);
    array2.PushBack("无敌是夺目山岭", allocator);
    array3.PushBack("无敌是夺目呵呵", allocator);
    
    document.AddMember("胸椎", array, allocator);
    document.AddMember("腰椎", array2, allocator);
    document.AddMember("颈椎", array3, allocator);
    
//    document.AddMember("胸椎", "shijg", allocator);
//    document.AddMember("doctorId", "10", allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void WelcomeScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
/*    char memberUrl[500]={0};
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s","21","yx_tb",getJsonData().c_str());
    char* url=memberUrl;
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(WelcomeScene::onHttpRequestCompleted, this),url); */
    
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getCaseById?caseId=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str());
    netManeger->postHttpRequest(memberUrl,CC_CALLBACK_2(WelcomeScene::onHttpRequestCompleted, this),nullptr);
    
}

void WelcomeScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    // rapidjson::Document Jsondata;
    
    this->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
        
        
        
        if (this->infoData["status"].GetInt()==0) {
            if(infoData["data"].HasMember("yx_tb")){
                const rapidjson::Value& val_form = infoData["data"];
            if(val_form.IsObject()){
                 log("   yx_tb: %s", val_form["yx_tb"].GetString());
                impressData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_tb"].GetString());
    //遍历数据
                string content="退变~";
                for (auto j=impressData.MemberBegin(); j!=impressData.MemberEnd(); ++j) {
                    auto key = (j->name).GetString();
                    if (impressData[key].Size()) {
                    content.append(key);
                    content.append(":");
                    }
                    log("key:%s", key);
                    for(auto i = 0; i < impressData[key].Size(); ++i){
                        content.append(impressData[key][i].GetString());
                        if (i==impressData[key].Size()-1&&j==impressData.MemberEnd()-1) {}else{content.append(" ");}
                         log("%s", impressData[key][i].GetString());
                    }
                }
                content.append(";");
                log("content:%s",content.c_str());
/*            if(impressData.HasMember("腰椎")){
                        const rapidjson::Value& info = impressData["腰椎"];
                        CC_ASSERT(info.IsArray());
                        for(unsigned int i = 0; i < info.Size(); ++i){
                            const rapidjson::Value& record = info[i];
                             log(" content: %s", record.GetString());
//                            CC_ASSERT(record.HasMember("content"));
//                            log("       content: %s", record["content"].GetString());
                        }
            }   */
                }
            }
        }
/*        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());   */
    }
}

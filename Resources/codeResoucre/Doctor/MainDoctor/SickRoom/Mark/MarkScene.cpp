//
//  MarkScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#include "MarkScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NeckJOAScene.hpp"
#include "WaistJOAScene.hpp"
#include "ASIAScene.hpp"
#include "VASScene.hpp"
#include "NDIScene.hpp"
#include "OPLLScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MarkScene::createScene(){
    return MarkScene::create();
}
bool MarkScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_mark.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    this->addChild(bkView);
    risserStr="";
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            if (strcmp(risserStr.c_str(),"")!=0) {
        //需要上传risserStr数据
                pushRisserToNetWork();
            }else{
            Director::getInstance()->popScene();
            }
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
            if (strcmp(risserStr.c_str(),"")!=0) {
                //需要上传risserStr数据
                pushRisserToNetWork();
            }else{
                Director::getInstance()->popScene();
            }
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-200));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,50));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MarkScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(MarkScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    return true;
    
}

void MarkScene::onEnter()

{
    Scene::onEnter();
    lv->removeAllItems();
    auto layer1 = createMessageLayout(0,"颈椎JOA","");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(1,"腰椎JOA","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(2,"ASIA","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(3,"Lenke分型","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(4,"Risser","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createMessageLayout(5,"NDI","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createMessageLayout(6,"VAS","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createMessageLayout(7,"OPLL","");
    lv->insertCustomItem(layer8,7);
    pushDataToNetWork();
}

//Risser选择
Layer* MarkScene::createSelectLayer(){
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
    
    auto contentV = Sprite::create("bk_strength_select.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,244));
    contentV->setContentSize(Size(508,681));
    layer->addChild(contentV);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(114, 15));
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
    
    auto fiveBtn=Button::create();
    fiveBtn->loadTextures("alpha.png", "alpha.png");
    fiveBtn->setTitleText("V");
    fiveBtn->setTitleColor(Color3B(40, 40, 40));
    fiveBtn->setTitleFontSize(45);
    fiveBtn->setPosition(Vec2(0, 83));
    fiveBtn->setAnchorPoint(Vec2(0,0));
    fiveBtn->setScale9Enabled(true);
    fiveBtn->setContentSize(Size(508, 83));
    fiveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            lv->removeChildByTag(4);
            auto layer5 = createMessageLayout(4,"Risser","V");
            risserStr="V";
            lv->insertCustomItem(layer5,4);
            this->removeChildByTag(200);
        }
        default:
            break;
    }
    });
    contentV->addChild(fiveBtn);
    
    createSelectItem("IV", 83*2, contentV);
    createSelectItem("III", 83*3, contentV);
    createSelectItem("II", 83*4, contentV);
    createSelectItem("I", 83*5, contentV);
    createSelectItem("0", 83*6, contentV);
    
    return layer;
}

void MarkScene::createSelectItem(string title,float Y,Sprite* contentV){
    auto fourBtn=Button::create();
    fourBtn->loadTextures("alpha.png", "alpha.png");
    fourBtn->setTitleText(title);
    fourBtn->setTitleColor(Color3B(40, 40, 40));
    fourBtn->setTitleFontSize(45);
    fourBtn->setPosition(Vec2(0, Y));
    fourBtn->setAnchorPoint(Vec2(0,0));
    fourBtn->setScale9Enabled(true);
    fourBtn->setContentSize(Size(508, 83));
    fourBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Button *btn=(Button *)sender;
            lv->removeChildByTag(4);
            auto layer5 = createMessageLayout(4,"Risser",btn->getTitleText());
            risserStr=btn->getTitleText();
            lv->insertCustomItem(layer5,4);
            this->removeChildByTag(200);
        }
        default:
            break;
    }
    });
    contentV->addChild(fourBtn);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, Y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(508, 1.5));
    contentV->addChild(lineV);
    
}




Layout *MarkScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
      layout->setTag(i);
    
    float height=10;
if (strcmp(title.c_str(),"VAS")==0) {
        if (content.c_str()!=nullptr) {
            auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-150,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
            height=contentLB->getContentSize().height+10;
            contentLB->setPosition(Point(37,10));
            contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
            contentLB->setAnchorPoint(Vec2(0, 0));
            layout->addChild(contentLB);
        }
        
        auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
        titleLB->setPosition(Point(37,height));
        titleLB->setTextColor(Color4B(91, 144, 229, 255));
        titleLB->setAnchorPoint(Vec2(0, 0));
        layout->addChild(titleLB);
}else{
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",38,Size(visibleSize.width-300,0),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
        contentLB->setPosition(Point(visibleSize.width-110,15));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(1, 0));
        layout->addChild(contentLB);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
}
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(30, 0));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-100, 2.0));
    layout->addChild(lineV);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+70));
    
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, height+10));
    layout->addChild(judgeBtn);
    
    
    return layout;
}

void MarkScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            long index=listView->getCurSelectedIndex();
            if (index==0) {
                auto neckSC=NeckJOAScene::createScene();
                Director::getInstance()->pushScene(neckSC);
            }else if (index==1){
                auto waistSC=WaistJOAScene::createScene();
                Director::getInstance()->pushScene(waistSC);
            }else if (index==2){
                auto asiaSC=ASIAScene::createScene();
                Director::getInstance()->pushScene(asiaSC);
            }else if (index==6){
                auto vasSC=VASScene::createScene();
                Director::getInstance()->pushScene(vasSC);
            }else if (index==5){
                auto ndiSC=NDIScene::createScene();
                Director::getInstance()->pushScene(ndiSC);
            }else if (index==7){
                auto opllSC=OPLLScene::createScene();
                Director::getInstance()->pushScene(opllSC);
            }else if (index==4){
                Layer *layer=createSelectLayer();
                layer->setTag(200);
                this->addChild(layer);
            }
            
            break;
        }
        default:
            break;
    }
}
void MarkScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
    switch (type) {
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM://滑动到底部
            CCLOG("SCROLL_TO_BOTTOM");
            break;
        case ui::ScrollView::EventType::SCROLL_TO_TOP://滑动到头部
            CCLOG("SCROLL_TO_TOP");
            break;
        default:
            break;
    }
}



void MarkScene::pushRisserToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"pf_risser",risserStr.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(MarkScene::onHttpRequestCompleted2, this),url);
}

void MarkScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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







#pragma-网络数据
void MarkScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getCaseById?caseId=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str());
    netManeger->postHttpRequest(memberUrl,CC_CALLBACK_2(MarkScene::onHttpRequestCompleted, this),nullptr);
}

void MarkScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
            const rapidjson::Value& val_form = infoData["data"];
            if(val_form.IsObject()){
                string VASContent="";//VAS
                if (!val_form["pf_VAS"].IsNull()) {
                    VASData.Parse<rapidjson::kParseDefaultFlags>(val_form["pf_VAS"].GetString());
                    VASContent=searchContentForInfoData(VASContent,"",VASData);
                }
                lv->removeChildByTag(6);
                auto layer7 = createMessageLayout(6,"VAS",VASContent);
                lv->insertCustomItem(layer7,6);
                
                string NDIContent="";//NDI
                if (!val_form["pf_jNDI_total"].IsNull()) {
                    NDIContent=val_form["pf_jNDI_total"].GetString();
                }
                lv->removeChildByTag(5);
                auto layer6 = createMessageLayout(5,"NDI",NDIContent);
                lv->insertCustomItem(layer6,5);
                
                string waistContent="";//腰部JOA
                if (!val_form["pf_yJOA_total"].IsNull()) {
                    waistContent=val_form["pf_yJOA_total"].GetString();
                }
                lv->removeChildByTag(1);
                auto layer2 = createMessageLayout(1,"腰椎JOA",waistContent);
                lv->insertCustomItem(layer2,1);
                
                string neckJOAContent="";//颈部JOA
                if (!val_form["pf_jJOA_total"].IsNull()) {
                    neckJOAContent=val_form["pf_jJOA_total"].GetString();
                }
                lv->removeChildByTag(0);
                auto layer1 = createMessageLayout(0,"颈椎JOA",neckJOAContent);
                lv->insertCustomItem(layer1,0);
                
                string asiaContent="";//ASIA
                if (!val_form["pf_ASIA"].IsNull()) {
                    asiaData.Parse<rapidjson::kParseDefaultFlags>(val_form["pf_ASIA"].GetString());
                    asiaContent=searchContentForInfoData(asiaContent, "",asiaData);
                }
                lv->removeChildByTag(2);
                auto layer3 = createMessageLayout(2,"ASIA",asiaContent);
                lv->insertCustomItem(layer3,2);
                
                if (!val_form["pf_risser"].IsNull()) {
                    lv->removeChildByTag(4);
                    auto layer5 = createMessageLayout(4,"Risser",val_form["pf_risser"].GetString());
                    lv->insertCustomItem(layer5,4);
                }
                
                
            }}
        
    }
}

std::string MarkScene::searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data){
    if (data.IsObject()) {
        content.append(title);
for (auto j=data.MemberBegin(); j!=data.MemberEnd(); ++j) {
            auto key = (j->name).GetString();
    if (data[key].IsArray()) {
            if (data[key].Size()) {
                content.append(key);
                content.append(":");
              }
            log("key:%s", key);
            for(auto i = 0; i < data[key].Size(); ++i){
                content.append(data[key][i].GetString());
                if (i==data[key].Size()-1&&j==data.MemberEnd()-1) {}else{
                    content.append(" ");}
                
                log("%s", data[key][i].GetString());
               }
    }else if(data[key].IsString()){
       content.append(key);
       content.append(":");
       content.append(data[key].GetString());
        content.append(" ");
    }
}
    }else if(data.IsArray()){
        if (data.Size()>0) {
            content.append(title);
        }
        for(auto i = 0; i < data.Size(); ++i){
            content.append(data[i].GetString());
            content.append(" ");
            log("%s", data[i].GetString());
        }
    }
    log("content：%s",content.c_str());
    return content;
}










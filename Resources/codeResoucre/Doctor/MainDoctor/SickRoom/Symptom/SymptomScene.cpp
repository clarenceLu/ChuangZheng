//
//  SymptomScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "SymptomScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SymptomScene::createScene(){
    return SymptomScene::create();
}
bool SymptomScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_symptom.png");
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
    
    ListView* lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-190));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,40));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(SymptomScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(SymptomScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layer1 = createMessageLayout(0,"四肢麻木","双手,双脚,双前臂,双脚,双大腿");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(0,"四肢无力","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(0,"四肢肌肉萎缩","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(0,"四肢活动不灵活","");
    lv->insertCustomItem(layer4,3);
    auto layer13 = createMessageLayout(0,"疼痛","");
    lv->insertCustomItem(layer13,4);
    auto layer5 = createItemLayout(0, "行走困难");
    lv->insertCustomItem(layer5,5);
    auto layer6 = createItemLayout(1, "间歇性跛行");
    lv->insertCustomItem(layer6,6);
    auto layer7 = createItemLayout(2, "踩棉感");
    lv->insertCustomItem(layer7,7);
    auto layer8 = createItemLayout(3, "胸腹部束带感");
    lv->insertCustomItem(layer8,8);
    auto layer9 = createItemLayout(4, "足下垂");
    lv->insertCustomItem(layer9,9);
    auto layer10 = createItemLayout(5, "大小便障碍");
    lv->insertCustomItem(layer10,10);
    auto layer11 = createItemLayout(6, "勃起困难");
    lv->insertCustomItem(layer11,11);
    auto layer12 = createItemLayout(7, "心慌头昏");
    lv->insertCustomItem(layer12,12);
    
    return true;
    
}

Layout *SymptomScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-150,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        height=contentLB->getContentSize().height+10;
        contentLB->setPosition(Point(37,10));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        layout->addChild(contentLB);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height+10));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(30, 0));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-100, 1.5));
    layout->addChild(lineV);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+80));
    
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, height+20));
    layout->addChild(judgeBtn);
    
    
    return layout;
}

Layout *SymptomScene::createItemLayout(int i,string title){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height+10));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(30, 0));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-100, 1.5));
    layout->addChild(lineV);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+80));
    
    auto box = CheckBox::create("btn_appearance_unsure.png","btn_appearance_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(visibleSize.width-110, height+10));
    box->setScale(0.87);
    box->setTag(i);
    box->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(SymptomScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    layout->addChild(box);
    boxDic.insert(i, box);
    
    return layout;
}

void SymptomScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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


void SymptomScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            
            break;
        }
        default:
            break;
    }
}
void SymptomScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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


std::string SymptomScene::getJsonData()
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        for (int i=0; i<8; i++) {
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
void SymptomScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"zz",getJsonData().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(SymptomScene::onHttpRequestCompleted, this),url);
    
}

void SymptomScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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




string SymptomScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 0:
            content="行走困难";
            break;
        case 1:
            content="间歇性跛行";
            break;
        case 2:
            content="踩棉感";
            break;
        case 3:
            content="胸腹部束带感";break;//神经根型颈椎病
        case 4:
            content="足下垂";break;
        case 5:
            content="大小便障碍";break;
        case 6:
            content="勃起困难";break;
        case 7:
            content="心慌头昏";break;
        case 8:
            content="其他";break;
            
        default:
            break;
    }
    return content;
}


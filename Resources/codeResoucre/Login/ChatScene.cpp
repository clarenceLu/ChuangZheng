//
//  ChatScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/12.
//

#include "ChatScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "ChatUserDetailScene.hpp"
#include "SearchScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ChatScene::createScene(){
    return ChatScene::create();
}
bool ChatScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_chat.png");
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
    
 /*   auto searchBtn=Button::create();
    searchBtn->loadTextures("btn_search.png", "btn_search.png");
    searchBtn->setPosition(Vec2(553, visibleSize.height-85));
    searchBtn->setScale(0.87);
    searchBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto searchSC=SearchScene::createScene();
            Director::getInstance()->pushScene(searchSC);
        }
        default:
            break;
    }
    });
    this->addChild(searchBtn);   */
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width, visibleSize.height-150));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(0,0));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ChatScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(ChatScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    pushDataToNetWork();
   
    return true;
}
void ChatScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
#pragma-跳转聊天界面
            break;
        }
        default:
            break;
    }
}
void ChatScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

Layout* ChatScene::createMessageLayer(int i, Size  innerSize){
    rapidjson::Value& object = infoData["data"];
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, 153));
    layout->setTag(1000+i);
    
    auto bkView=Sprite::create("bk_tableView_white.png");
    bkView->setPosition(Vec2(visibleSize.width/2, 0));
    bkView->setAnchorPoint(Vec2(0.5, 0));
    bkView->setContentSize(layout->getContentSize());
    layout->addChild(bkView);
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(15, 15));
    headBtn->setTouchEnabled(true);
    float height=headBtn->getContentSize().height;
    headBtn->setScale(120.0/height);
    headBtn->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
/*            auto chatSC=ChatUserDetailScene::createScene();
            Director::getInstance()->pushScene(chatSC);    */
        }
    });
 
        auto contentLB = Label::createWithSystemFont("未知","Arial",32,Size(380,50),TextHAlignment::LEFT,TextVAlignment::TOP);
        contentLB->setPosition(Point(150,10));
        contentLB->setTextColor(Color4B(0, 0, 0, 255/2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(contentLB);

        auto jobLB = Label::createWithSystemFont("介绍人:无","Arial",32,Size(380,50),TextHAlignment::RIGHT,TextVAlignment::TOP);
        jobLB->setPosition(Point(visibleSize.width-400,10));
        jobLB->setTextColor(Color4B(0, 0, 0, 255/2));
        jobLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(jobLB);
    
  /*  "0" : {
        "doctorId" : "10",
        "userId" : "shijg",
        "name" : "lica",
        "role" : "1",
        "headUrl" : {
        },
        "groupId" : "4"
    },   */
    if (!object["name"].IsNull()) {
        string name=object["name"].GetString();
    auto nameLB = Label::createWithSystemFont(name,"Arial",35,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(150,80));
    nameLB->setTextColor(Color4B(0, 0, 0, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(nameLB);
    }
    
    auto timeLB = Label::createWithSystemFont("上午","Arial",25,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(513,80));
    timeLB->setTextColor(Color4B(0, 0, 0, 255/3));
    timeLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(timeLB);
    return layout;
}

#pragma-网络请求
void ChatScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char strtest[500] = {0};
    sprintf(strtest,"http://czapi.looper.pro/web/getMyChatList?patientId=%s", UserDefault::getInstance()->getStringForKey("userId").c_str());
    string url=strtest;
    netManeger->sendMessage(url,CC_CALLBACK_2(ChatScene::onHttpRequestCompleted, this),nullptr);
}
void ChatScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    //     rapidjson::Document Jsondata;
    
    infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (infoData.HasParseError()) {
        
        return;
    }
    if(infoData.HasMember("data")){
        rapidjson::Value& object = infoData["data"];
        for (int i=0; i<object.Size(); i++) {
            auto layer1 = createMessageLayer(i,lv->getInnerContainerSize());
            lv->insertCustomItem(layer1,i);
        }
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    infoData.Accept(writer);
    CCLOG("%s", buffer.GetString());
}


//
//  ReceiveChatScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#include "ReceiveChatScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "WaitChatDetailScene.hpp"
#include "SearchScene.hpp"
#include "ChatViewScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ReceiveChatScene::createScene(){
    return ReceiveChatScene::create();
}
bool ReceiveChatScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_receive.png");
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
 /*
    auto searchBtn=Button::create();
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
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ReceiveChatScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(ReceiveChatScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    pushDataToNetWork();
    return true;
}
cocos2d::ui::Layout * ReceiveChatScene::createMessageLayout(int i){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
     rapidjson::Value& data = this->receiveData["data"][i];
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setContentSize(Size(visibleSize.width, 160));
    layout->setTouchEnabled(true);
    
    auto bkView=Sprite::create("bk_tableView_white.png");
    bkView->setPosition(Vec2(visibleSize.width/2, 0));
    bkView->setAnchorPoint(Vec2(0.5, 0));
    bkView->setContentSize(Size(visibleSize.width, 160));
    layout->addChild(bkView);
    
    
    auto headBtn=ImageView::create("bk_headIV.png");
    float height=headBtn->getContentSize().height;
    headBtn->setPosition(Vec2(15, 15));
    headBtn->setTouchEnabled(true);
    headBtn->setScale(120.0/height);
    headBtn->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
           
        }
    });
    
    auto contentLB = Label::createWithSystemFont(data["caseNo"].GetString(),"Arial",32,Size(380,40),TextHAlignment::LEFT,TextVAlignment::TOP);
    contentLB->setPosition(Point(150,10));
    contentLB->setTextColor(Color4B(0, 0, 0, 255/2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(contentLB);
    
    auto jobLB = Label::createWithSystemFont("介绍人:无","Arial",30,Size(380,40),TextHAlignment::RIGHT,TextVAlignment::TOP);
    jobLB->setPosition(Point(visibleSize.width-400,10));
    jobLB->setTextColor(Color4B(0, 0, 0, 255/2));
    jobLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(jobLB);
    
    auto recommandLB = Label::createWithSystemFont("推荐人:无","Arial",30,Size(380,40),TextHAlignment::RIGHT,TextVAlignment::TOP);
    recommandLB->setPosition(Point(visibleSize.width-400,50));
    recommandLB->setTextColor(Color4B(0, 0, 0, 255/2));
    recommandLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(recommandLB);
    
    auto nameLB = Label::createWithSystemFont(data["name"].GetString(),"Arial",35,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(150,60));
    nameLB->setTextColor(Color4B(0, 0, 0, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(nameLB);
    
    auto timeLB = Label::createWithSystemFont(data["requestTime"].GetString(),"Arial",25,Size(380,40),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(620,110));
    timeLB->setTextColor(Color4B(0, 0, 0, 255/3));
    timeLB->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(timeLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0,2));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width, 1.5));
    bkView->addChild(lineV);
    return layout;
}


void ReceiveChatScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
#pragma-在这里添加跳转聊天界面的接口
            
            
            
            auto chatSC=(ChatViewScene*)ChatViewScene::createScene();
            chatSC->createHubView();
            Director::getInstance()->pushScene(chatSC);
            
            
            
//            auto chatSC=(WaitChatDetailScene*)WaitChatDetailScene::createScene();
//            chatSC->type=1;
//            Director::getInstance()->pushScene(chatSC);
            break;
        }
        default:
            break;
    }
}
void ReceiveChatScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

#pragma-用于加载网络数据
void ReceiveChatScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getMyOutpatientList?doctorId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(ReceiveChatScene::onHttpRequestCompleted, this),nullptr);
}

void ReceiveChatScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
            receiveData.SetObject();
            rapidjson::Document::AllocatorType& allocator = receiveData.GetAllocator();
            rapidjson::Value array(rapidjson::kArrayType);
            for (int i=0; i<this->infoData["data"].Size(); i++) {
                rapidjson::Value& object = this->infoData["data"][i];
                log("status:%s",object["status"].GetString());
                if (strcmp(object["status"].GetString(),"accepted")==0) {
                    array.PushBack(object, allocator);
                }
            }
            receiveData.AddMember("data", array, allocator);
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            receiveData.Accept(writer);
            CCLOG("%s", buffer.GetString());
            lv->removeAllItems();
            for (int i=0; i<receiveData["data"].Size(); i++) {
                auto layer1 = createMessageLayout(i);
                lv->insertCustomItem(layer1,i);
            }
        }
    }
}




//
//  WaitChatScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#include "WaitChatScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SearchScene.hpp"
#include "WaitChatDetailScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *WaitChatScene::createScene(){
    return WaitChatScene::create();
}
bool WaitChatScene::init(){
    if (!Scene::init()) {
        return false;
    }
     isReceive=2;
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_wait.png");
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
    this->addChild(searchBtn);
    
    auto receiveCheckBox = CheckBox::create("btn_receive_unselect.png","btn_receive_select.png");
    //设置CheckBox的位置
    receiveCheckBox->setPosition(Vec2(0, visibleSize.height-220));
    receiveCheckBox->setAnchorPoint(Vec2(0, 0));
    receiveCheckBox->setTag(50);
    receiveCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    receiveCheckBox->setTouchEnabled(true);
    receiveCheckBox->setSelected(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    receiveCheckBox->addEventListener(CC_CALLBACK_2(WaitChatScene::checkBoxCallback,this));
    addChild(receiveCheckBox);
    
    auto waitCheckBox = CheckBox::create("btn_refuse_unselect.png","btn_refuse_select.png");
    //设置CheckBox的位置
    waitCheckBox->setPosition(Vec2(visibleSize.width/2+1, visibleSize.height-220));
    waitCheckBox->setAnchorPoint(Vec2(0, 0));
    waitCheckBox->setScale(0.87);
    waitCheckBox->setTag(51);
    //设置CheckBox是否可点击
    waitCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    waitCheckBox->addEventListener(CC_CALLBACK_2(WaitChatScene::checkBoxCallback,this));
    addChild(waitCheckBox);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, visibleSize.height-225));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width, 2));
    bkView->addChild(lineV);
    
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(visibleSize.width/2-1, visibleSize.height-225));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setContentSize(Size(2, 80));
    addChild(lineV2);
    
    
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width, visibleSize.height-225));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(0,0));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(WaitChatScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(WaitChatScene::selectedItemEventScrollView, this));
    this->addChild(lv);
//    pushDataToNetWork();
    return true;
}

void WaitChatScene::onEnter(){
    Scene::onEnter();
    pushDataToNetWork();
}

cocos2d::ui::Layout * WaitChatScene::createMessageLayout(int i){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
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
    
    
    if (isReceive==2) {
    rapidjson::Value& data =this->waitingData["data"][i];
    createContentWithRapidjsonValueData(data, bkView);
}else  if(isReceive==3){
    rapidjson::Value& data = this->refuseData["data"][i];
    createContentWithRapidjsonValueData(data, bkView);
    }
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0,2));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width, 1.5));
    bkView->addChild(lineV);
    
    return layout;
}

void WaitChatScene::createContentWithRapidjsonValueData(rapidjson::Value&data,Sprite* bkView){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    string caseNo="";
    if (data["caseNo"].IsNull()) {}else{
        caseNo=data["caseNo"].GetString();
    }
    auto contentLB = Label::createWithSystemFont(caseNo,"Arial",32,Size(380,40),TextHAlignment::LEFT,TextVAlignment::TOP);
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
    
    string name="";
    if (data["name"].IsNull()) {}else{
        name=data["name"].GetString();
    }
    auto nameLB = Label::createWithSystemFont(name,"Arial",35,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(150,60));
    nameLB->setTextColor(Color4B(0, 0, 0, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(nameLB);
    
    string time="";
    if (data["requestTime"].IsNull()) {}else{
        time=data["requestTime"].GetString();
    }
    auto timeLB = Label::createWithSystemFont(time,"Arial",25,Size(380,40),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(620,110));
    timeLB->setTextColor(Color4B(0, 0, 0, 255/3));
    timeLB->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(timeLB);
}



void WaitChatScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            int index=listView->getCurSelectedIndex();
            auto chatSC=(WaitChatDetailScene*)WaitChatDetailScene::createScene();
            chatSC->type=isReceive;
            if (isReceive==2) {
                chatSC->infoData.SetObject();
                rapidjson::Document::AllocatorType& allocator = chatSC->infoData.GetAllocator();
                rapidjson::Value array(rapidjson::kArrayType);
                array=this->waitingData["data"];
                chatSC->infoData.AddMember("data", array, allocator);
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                chatSC->infoData.Accept(writer);
                CCLOG("%s", buffer.GetString());
            }else if(isReceive==3){
                chatSC->infoData.SetObject();
                rapidjson::Document::AllocatorType& allocator = chatSC->infoData.GetAllocator();
                rapidjson::Value array(rapidjson::kArrayType);
                array=this->refuseData["data"];
                chatSC->infoData.AddMember("data", array, allocator);
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                chatSC->infoData.Accept(writer);
                CCLOG("%s", buffer.GetString());
            }
            chatSC->indexForData=index;
//            chatSC->data=data;
//            log("%s",chatSC->data["status"].GetString());
            Director::getInstance()->pushScene(chatSC);
            break;
        }
        default:
            break;
    }
}
void WaitChatScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

void WaitChatScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    CheckBox *checkBox;
    if (tag==50) {
        isReceive=2;
        checkBox=(CheckBox*)this->getChildByTag(51);
        pushDataToNetWork();
    }else{
         isReceive=3;
        checkBox=(CheckBox*)this->getChildByTag(50);
        pushDataToNetWork();
    }
    //     bool selected  = checkBox->getSelectedState();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            item->setSelected(true);
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

#pragma-用于加载网络数据
void WaitChatScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getMyOutpatientList?doctorId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(WaitChatScene::onHttpRequestCompleted, this),nullptr);
}

void WaitChatScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
         /*   rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            infoData.Accept(writer);
            CCLOG("%s", buffer.GetString());  */
if (isReceive==2) {
            waitingData.SetObject();
            rapidjson::Document::AllocatorType& allocator = waitingData.GetAllocator();
            rapidjson::Value array(rapidjson::kArrayType);
            for (int i=0; i<this->infoData["data"].Size(); i++) {
                rapidjson::Value& object = this->infoData["data"][i];
                log("status:%s",object["status"].GetString());
                if (strcmp(object["status"].GetString(),"waitting")==0) {
                    array.PushBack(object, allocator);
                }
            }
            waitingData.AddMember("data", array, allocator);
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            waitingData.Accept(writer);
            CCLOG("%s", buffer.GetString());
            lv->removeAllItems();
            for (int i=0; i<waitingData["data"].Size(); i++) {
                auto layer1 = createMessageLayout(i);
                lv->insertCustomItem(layer1,i);
                   }
}else if(isReceive==3){
                refuseData.SetObject();
                rapidjson::Document::AllocatorType& allocator = refuseData.GetAllocator();
                rapidjson::Value array(rapidjson::kArrayType);
                for (int i=0; i<this->infoData["data"].Size(); i++) {
                    rapidjson::Value& object = this->infoData["data"][i];
                    if (strcmp(object["status"].GetString(),"refused")==0) {
                        array.PushBack(object, allocator);
                    }
                }
                refuseData.AddMember("data", array, allocator);
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                refuseData.Accept(writer);
                CCLOG("%s", buffer.GetString());
                lv->removeAllItems();
                for (int i=0; i<refuseData["data"].Size(); i++) {
                    auto layer1 = createMessageLayout(i);
                    lv->insertCustomItem(layer1,i);
                }
}
        }
    }
}


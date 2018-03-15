//
//  MessageNotificationScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/31.
//

#include "MessageNotificationScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MessageNotificationScene::createScene(){
    return MessageNotificationScene::create();
}
bool MessageNotificationScene::init(){
    if (!Scene::init()) {
        return false;
    }
    typeForData=0;
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_notificaion_message.png");
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
    
    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_notificationTop_select.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_notification_delete.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(MessageNotificationScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(Vec2(visibleSize.width-120, visibleSize.height-105));  //设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setTag(-3);
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    box->setTag(-3);
    this->addChild(box);
    
    auto tempBedBox=CheckBox::create("btn_notificationInfo_unselect.png","btn_notificationInfo_select.png");
    //设置CheckBox的位置
    tempBedBox->setPosition(Vec2(visibleSize.width/2,918));
    tempBedBox->setTag(-1);
    tempBedBox->setAnchorPoint(Vec2(0, 0));
    tempBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    tempBedBox->setTouchEnabled(true);
    tempBedBox->addEventListener(CC_CALLBACK_2(MessageNotificationScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(tempBedBox);
    boxVec.pushBack(tempBedBox);
//    boxVec->pushBack(tempBedBox);
    auto fixedBedBox=CheckBox::create("btn_notification_not_remind.png","btn_notification_remind.png");
    //设置CheckBox的位置
    fixedBedBox->setPosition(Vec2(0,918));
    fixedBedBox->setTag(-2);
    fixedBedBox->setAnchorPoint(Vec2(0, 0));
    fixedBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    fixedBedBox->setTouchEnabled(true);
    fixedBedBox->setSelected(true);
    fixedBedBox->addEventListener(CC_CALLBACK_2(MessageNotificationScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(fixedBedBox);
    boxVec.pushBack(fixedBedBox);
//    boxVec->pushBack(fixedBedBox);
    
    auto line1=Sprite::create("userInfo_line.png");
    line1->setPosition(Vec2(0, 915));
    line1->setAnchorPoint(Vec2(0, 0));
    line1->setScaleX(1.05);
    bkView->addChild(line1);
    
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(visibleSize.width/2+4, visibleSize.height-220));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setContentSize(Size(2, 75));
    bkView->addChild(lineV2);
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-230));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,0));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MessageNotificationScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(MessageNotificationScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    pushDataToNetWork();
    
    return true;
}

Layout *MessageNotificationScene::createMessageLayout(int i,rapidjson::Value& object){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    auto whiteV=Sprite::create("bk_impress_rect_white.png");
    whiteV->setPosition(Vec2(0, 20));
    whiteV->setAnchorPoint(Vec2(0, 0));
//    whiteV->setContentSize(Size(visibleSize.width-80, 60*(index+1)));
    layout->addChild(whiteV);
    string content="下午开会，没事别迟到";
    if (typeForData==1) {
    content=object["msg"].GetString();
    }else{
       content=object["content"].GetString();
    }
    string time=object["ctime"].GetString();
    float height=20;  //下面 空20
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-110,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        height=20+(contentLB->getContentSize().height+20);
        contentLB->setPosition(Point(37,10));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        whiteV->addChild(contentLB);
    }
    whiteV->setContentSize(Size(visibleSize.width-40, height+40)); //算上蓝色的高度60，上面还需空20 ，所以layer为height+80
    
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(0, height));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-40, 60));
    layout->addChild(blueV);
    auto timeLB = Label::createWithSystemFont(time,"Arial",38,Size(visibleSize.width-200,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    timeLB->setPosition(Point(37,0));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(timeLB);
     if (typeForData==0) {
    auto box = CheckBox::create("btn_appearance_unsure.png","btn_appearance_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(visibleSize.width-100,10));
    box->setScale(0.87);
    box->setTag(i);
    box->setTag(atoi(object["id"].GetString()));
    box->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->setVisible(false);
    box->addEventListener(CC_CALLBACK_2(MessageNotificationScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueV->addChild(box);
    boxDic.insert(i,box);
     }
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+80));
    
    return layout;
}
void MessageNotificationScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
void MessageNotificationScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

cocos2d::Layer* MessageNotificationScene::createPromptLayer(std::string content){
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
    auto contentV = Sprite::create("bk_group_leader_prompt.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(120, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
#pragma-用于传值
            for (int i=0; i<boxDic.size(); i++) {
                CheckBox* box=boxDic.at(i);
                if (box->getSelectedState()) {
                    deleteRemindToNetWork(box->getTag());
                }
            }
            for (int i=0; i<boxDic.size(); i++) {
                CheckBox* box=boxDic.at(i);
                box->setVisible(false);
            }
            Menu *menu=(Menu *)this->getChildByTag(-3);
            MenuItemToggle *box=(MenuItemToggle *)menu->getChildByTag(-3);
            box->setSelectedIndex(0);
            this->removeChildByTag(2001);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(2001);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto contentLB=Label::createWithSystemFont(content,"Arial",36,Size(contentV->getContentSize().width-40,120),TextHAlignment::CENTER,TextVAlignment::CENTER);
    contentLB->setPosition(Vec2(20,120));
    contentLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(contentLB);
    
    return layer;
}



void MessageNotificationScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    if (index==1) {
        log("删除");
        for (int i=0; i<boxDic.size(); i++) {
            CheckBox* box=boxDic.at(i);
            box->setVisible(true);
        }
    }else{
        log("选择");
        item->setSelectedIndex(1);
        Layer *layer= createPromptLayer("确认删除当前所选内容吗");
        layer->setTag(2001);
        this->addChild(layer);
    }
    
}
//实现CheckBox回调函数
void MessageNotificationScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if (tag==-1||tag==-2) {
            //临时病床和固定病床
            for (int i=0; i<2; i++) {
                CheckBox *box=boxVec.at(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
        }
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            if (tag==-1||tag==-2) {
                if (tag==-1) {
                    typeForData=1;
                Menu *menu=(Menu *)this->getChildByTag(-3);
                    menu->setVisible(false);
                    pushDataToNetWork();
                }else{
                    typeForData=0;
                    Menu *menu=(Menu *)this->getChildByTag(-3);
                    menu->setVisible(true);
                    pushDataToNetWork();
                }
            }
            if (tag>=0) {
                for (int i=0; i<boxDic.size(); i++) {
                    CheckBox* box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelectedState(false);
                    }
                }
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            if (tag==-1||tag==-2) {
                item->setSelected(true);
            }
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

#pragma-用于加载网络数据
void MessageNotificationScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getInform?doctorId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(MessageNotificationScene::onHttpRequestCompleted, this),nullptr);
}

void MessageNotificationScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
            rapidjson::Value& object = this->infoData["data"];
            if (typeForData==0) {
                lv->removeAllItems();
                boxDic.clear();
                for (int i=0; i<object["reminder"].Size(); i++) {
                    auto layer1 = createMessageLayout(i,object["reminder"][i]);
                    lv->insertCustomItem(layer1,i);
                }
            }else if(typeForData==1){
                lv->removeAllItems();
                 for (int i=0; i<object["inform"].Size(); i++) {
                auto layer1 = createMessageLayout(i,object["inform"][i]);
                lv->insertCustomItem(layer1,i);
                 }
            }
            
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}

#pragma-用于加载网络数据-删除提醒
void MessageNotificationScene::deleteRemindToNetWork(int  reminderId){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/deleteReminder?reminderId=%d",reminderId);
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(MessageNotificationScene::onHttpRequestCompleted, this),nullptr);
}

void MessageNotificationScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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
           pushDataToNetWork();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}



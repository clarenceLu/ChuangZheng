//
//  SelectStep4Scene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#include "SelectStep4Scene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SearchScene.hpp"

using namespace rapidjson; // 命名空间
#include "NetWrokMangerData.hpp"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SelectStep4Scene::createScene(){
    return SelectStep4Scene::create();
}
ScrollView *Select4Scroll;
rapidjson::Value dataArr(rapidjson::kArrayType);
bool SelectStep4Scene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
   
    auto bkView=Sprite::create("bk_step4.png");
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
    bkView->addChild(backBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_step4_sure.png", "btn_step4_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-70, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:

        default:
            break;
    }
    });
    bkView->addChild(sureBtn);
    
    auto serachV=Sprite::create("bk_step4_search.png");
    serachV->setPosition(Vec2(14, 915));
    serachV->setAnchorPoint(Vec2(0, 0));
    serachV->setScale(0.86);
    bkView->addChild(serachV);
    
    auto searchBtn=Button::create();
    searchBtn->loadTextures("btn_step4_search.png", "btn_step4_search.png");
    searchBtn->setPosition(Vec2(serachV->getContentSize().width-61,20));
        searchBtn->setAnchorPoint(Vec2(0, 0));
    searchBtn->setScale9Enabled(true);
    searchBtn->setContentSize(Size(41, 37));
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
    serachV->addChild(searchBtn);
    
#pragma-TableView
     
    
    auto searchText = TextField::create("最多可选三位医生发送您的病历","Arial",30);
    searchText->setMaxLength(40);
    searchText->setTouchSize(Size(visibleSize.width-300, 40));
    searchText->setPosition(Vec2(120,20));
    searchText->setAnchorPoint(Vec2(0,0));
    searchText->setContentSize(Size(visibleSize.width-300,40));
    searchText->setTextColor(Color4B::BLACK);
    searchText->setPlaceHolderColor(Color4B(91, 144, 230, 255/2));
    searchText->setTextHorizontalAlignment(TextHAlignment::LEFT);
    searchText->addEventListener(CC_CALLBACK_2(SelectStep4Scene::eventCallBack, this));
    serachV->addChild(searchText);
    
    Select4Scroll=createTableView(Vec2(0, 0), Size(visibleSize.width, 910));
    bkView->addChild(Select4Scroll);
    
    return true;
}

ScrollView* SelectStep4Scene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string url="http://czapi.looper.pro/web/getDoctor";
    netManeger->sendMessage(url,CC_CALLBACK_2(SelectStep4Scene::onHttpRequestCompleted, this),nullptr);
    return scrollView;
}

Layer* SelectStep4Scene::createMessageLayer(int i, Size  innerSize){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
//Data
     rapidjson::Value& object = this->loginData["data"][i];
    if (dataArr.GetArray().Size()) {
        object=dataArr[i];
    }
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(Size(visibleSize.width-40, 140));
    layer->setPosition(Point(20,innerSize.height-160*(i+1)+10));
    layer->setAnchorPoint(Vec2(0, 0));
    layer->setTag(1000+i);
    
    auto bkView=Sprite::create("bk_tableView_white.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(layer->getContentSize());
    layer->addChild(bkView);
    
    auto headV=Sprite::create("bk_headIV.png");
    headV->setPosition(Vec2(5, 5));
    headV->setAnchorPoint(Vec2(0, 0));
    headV->setScale(0.87);
    bkView->addChild(headV);
    auto headBtn=ImageView::create("HelloWorld.png");
    headBtn->setPosition(Vec2(10, 10));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
    headBtn->ignoreContentAdaptWithSize(true);
    headBtn->setScale9Enabled(true);
    headBtn->setContentSize(Size(125, 125));
    headBtn->setColor(Color3B::RED);
    headBtn->setTag(i);
    headV->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                                                if (type == Widget::TouchEventType::ENDED){
                                                    log("点击上传头像");
                                                }
    });
    string name=object["name"].GetString();
    
    if (object["intro"].IsObject()||object["intro"].IsNull()) {
    }else{
         string info=object["intro"].GetString();
        auto contentLB = Label::createWithSystemFont(info,"Arial",28,Size(380,80),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        contentLB->setPosition(Point(140,10));
        contentLB->setTextColor(Color4B(0, 0, 0, 255/2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(contentLB);
    }
    
    if (object["education"].IsObject()||object["education"].IsNull()) {
    }else{
    string education=object["education"].GetString();
        auto jobLB = Label::createWithSystemFont(education,"Arial",32,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        jobLB->setPosition(Point(300,80));
        jobLB->setTextColor(Color4B(0, 0, 0, 240));
        jobLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(jobLB);
    }
    auto nameLB = Label::createWithSystemFont(name,"Arial",35,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(140,80));
    nameLB->setTextColor(Color4B(0, 0, 0, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(nameLB);
    
    auto selectCheckBox = CheckBox::create("btn_step4_unselect.png","btn_step4_select.png");
    //设置CheckBox的位置
    selectCheckBox->setPosition(Vec2(layer->getContentSize().width-60, 45));
    selectCheckBox->setTag(100+i);
    selectCheckBox->setAnchorPoint(Vec2(0, 0));
    selectCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    selectCheckBox->setTouchEnabled(true);
    selectCheckBox->addEventListener(CC_CALLBACK_2(SelectStep4Scene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(selectCheckBox);
    
    return layer;
}

//实现CheckBox回调函数
void SelectStep4Scene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    MenuItem* item = (MenuItem*)ref;
    int tag= item->getTag();
     auto   checkBox=(CheckBox*)this->getChildByTag(tag);
//tag值100以及100+
    //     bool selected  = checkBox->getSelectedState();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
//            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}


void SelectStep4Scene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    switch (type){
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            if (textField->getString().length()) {
                log("有数据");
               for (int i=0; i<loginData["data"].Size(); i++) {
                    rapidjson::Value& object = this->loginData["data"][i];
                   rapidjson::Document::AllocatorType&allocator= loginData.GetAllocator();
                    CCLOG("%s", object["name"].GetString());
                 if(strcmp(object["name"].GetString(), textField->getString().c_str())==0){
                       log("%s",object["name"].GetString());
                     dataArr.PushBack(object, allocator);
                   }
               }
                if (dataArr.GetArray().Size()>0) {
                    for (int j=0; j<loginData["data"].Size(); j++) {
                        Select4Scroll->removeChildByTag(1000+j);
                    }
                    for (int k=0; k<dataArr.GetArray().Size(); k++) {
                        Size visibleSize=Director::getInstance()->getVisibleSize();
                        Select4Scroll->setInnerContainerSize(Size(visibleSize.width, 160*dataArr.GetArray().Size()));//设置内容大小
                        auto layer1 = createMessageLayer(k,Select4Scroll->getInnerContainerSize());
                        Select4Scroll->addChild(layer1);
                    }
                }
                
                log("%d",dataArr.GetArray().Size());
            }
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            if (textField->getString().length()) {
                  log("%s",textField->getString().c_str());
            }else{
                Size visibleSize=Director::getInstance()->getVisibleSize();
                Select4Scroll->setInnerContainerSize(Size(visibleSize.width, 160*loginData["data"].Size()));//设置内容大小
                    for (int j=0; j<dataArr.GetArray().Size(); j++) {
                        Select4Scroll->removeChildByTag(1000+j);
                        dataArr.Clear();
                    }
                 log("%d",loginData["data"].Size());
                for (int i=0; i<loginData["data"].Size(); i++) {
                    Size visibleSize=Director::getInstance()->getVisibleSize();
                    Select4Scroll->setInnerContainerSize(Size(visibleSize.width, 160*loginData["data"].Size()));//设置内容大小
                    auto layer1 = createMessageLayer(i,Select4Scroll->getInnerContainerSize());
                    Select4Scroll->addChild(layer1);
                }
            }
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            
            CCLOG("DETACH_WITH_IME");
            
            break;
            
    }
    
}



#pragma-用于加载网络数据

void SelectStep4Scene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string url="http://czapi.looper.pro/web/getDoctor";
    netManeger->sendMessage(url,CC_CALLBACK_2(SelectStep4Scene::onHttpRequestCompleted, this),nullptr);
}

void SelectStep4Scene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    // rapidjson::Document Jsondata;
    this->loginData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (this->loginData.HasParseError()) {
        return;
    }
    if(this->loginData.HasMember("data")){
        Size visibleSize=Director::getInstance()->getVisibleSize();
        Select4Scroll->setInnerContainerSize(Size(visibleSize.width, 160*loginData["data"].Size()));//设置内容大小
        for (int i=0; i<loginData["data"].Size(); i++) {
            auto layer1 = createMessageLayer(i,Select4Scroll->getInnerContainerSize());
            Select4Scroll->addChild(layer1);
        }
//                for(int i = 0; i < this->loginData["data"].Size(); i++) {
//                    rapidjson::Value& object = this->loginData["data"][i];
//                    CCLOG("%s", object["name"].GetString());
//                }
    }
    
}


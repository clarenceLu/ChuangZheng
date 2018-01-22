//
//  SickRoomScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/4.
//

#include "SickRoomScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "MarkScene.hpp"
#include "CharacterScene.hpp"
#include "DocUserInfoScene.hpp"
#include "SymptomScene.hpp"
#include "ImpressionScene.hpp"
#include "TreatScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SickRoomScene::createScene(){
    return SickRoomScene::create();
}
bool SickRoomScene::init(){
    if (!Scene::init()) {
        return false;
    }
    bedNum=1;
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_sickroomDetail.png");
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
    
    auto calendarBtn=Button::create();
    calendarBtn->loadTextures("btn_sickroom_calendar.png", "btn_sickroom_calendar.png");
    calendarBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    calendarBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=addCalendarLayer();
            layer->setTag(1000);
            this->addChild(layer);
        }
            
        default:
            break;
    }
    });
    this->addChild(calendarBtn);
    
    auto visitBtn=Button::create();
    visitBtn->loadTextures("btn_visit_config.png", "btn_visit_config.png");
    visitBtn->setPosition(Vec2(57, 70));
    visitBtn->setScale(0.87);
    visitBtn->setAnchorPoint(Vec2(0, 0));
    visitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("随访设置");
        }
            
        default:
            break;
    }
    });
    bkView->addChild(visitBtn);
    
    auto recoverBtn=Button::create();
    recoverBtn->loadTextures("btn_recover.png", "btn_recover.png");
    recoverBtn->setPosition(Vec2(visibleSize.width-57, 70));
    recoverBtn->setAnchorPoint(Vec2(1, 0));
    recoverBtn->setScale(0.87);
    recoverBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("出院");
        }
            
        default:
            break;
    }
    });
    bkView->addChild(recoverBtn);
    
    return true;
    
}
void SickRoomScene::onEnter()
{
    
    log("%d",bedNum);
    Size visibleSize=Director::getInstance()->getVisibleSize();
    Scene::onEnter();
    char str[10];
    sprintf(str,"%d床",bedNum);
    string title=str;
    auto timeLB = Label::createWithSystemFont(title,"Arial",45,Size(380,60),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(visibleSize.width/2,1023));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(timeLB);
    
    if (lv==nullptr) {
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-300));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,150));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(SickRoomScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(SickRoomScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layer1 = createMessageLayout(0,"张牧之","男    54    20171816");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(1,"负责医生","元亨      张建华    熊青春");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(2,"印象","上肢发达  双臂麻木   双大腿抽筋    左前方脊椎疼痛  脑袋晕");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(3,"症状","上肢发达  双臂麻木   双大腿抽筋");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(4,"体征","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createMessageLayout(5,"影像","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createMessageLayout(6,"评分","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createMessageLayout(7,"治疗方式","");
    lv->insertCustomItem(layer8,7);
    auto layer9 = createMessageLayout(8,"备注","");
    lv->insertCustomItem(layer9,8);
    }
    
}

Layout *SickRoomScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
    if (content.c_str()!=nullptr) {
    auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-200,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    height=contentLB->getContentSize().height+10;
    contentLB->setPosition(Point(37,10));
    contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(contentLB);
    }
    if (i==5) {
//影像
        ScrollView *imageScrol=createImageScroll(Vec2(35, 10), Size(visibleSize.width-150, 80));
        height=imageScrol->getContentSize().height+10;
        layout->addChild(imageScrol);
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

ScrollView* SickRoomScene::createImageScroll(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);//方向
    scrollView->setScrollBarEnabled(false);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    for (int i=0; i<10; i++) {
#pragma-修改影像的图片
    auto imageV1=Sprite::create("HelloWorld.png");
        imageV1->setPosition(Vec2((visibleSize.height+20)*i, 0));
        imageV1->setAnchorPoint(Vec2(0, 0));
        imageV1->setContentSize(Size(visibleSize.height, visibleSize.height));
        scrollView->addChild(imageV1);
    }
    scrollView->setInnerContainerSize(Size((visibleSize.height+20)*10, visibleSize.height));
    
    return scrollView;
}


Layer* SickRoomScene::addCalendarLayer(){
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
    auto contentV = Sprite::create("bk_sickroom_calendar.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508, 349));
    layer->addChild(contentV);
    auto cancelBtn=Button::create();
    cancelBtn->loadTextures("btn_addCase_cancel.png", "btn_addCase_cancel.png");
    cancelBtn->setPosition(Vec2(120, 15));
    cancelBtn->setAnchorPoint(Vec2(0,0));
    cancelBtn->setScale(0.87);
    cancelBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(1000);
        }
            break;
        default:
            break;
    }
    });
    contentV->addChild(cancelBtn);
    
    //出院
    auto outpatientBtn=Button::create();
    outpatientBtn->loadTextures("alpha.png", "alpha.png");
    outpatientBtn->setPosition(Vec2(visibleSize.width/2, 563));
    outpatientBtn->setScale9Enabled(true);
    outpatientBtn->setContentSize(Size(508, 42));
    outpatientBtn->setTitleText("出院");
    outpatientBtn->setTitleColor(Color3B(40, 40, 40));
    outpatientBtn->setTitleFontSize(40);
    outpatientBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("出院");
        }
        default:
            break;
    }
    });
    layer->addChild(outpatientBtn);
    
    //手术
    auto visitBtn=Button::create();
    visitBtn->loadTextures("alpha.png", "alpha.png");
    visitBtn->setPosition(Vec2(visibleSize.width/2, 648));
    visitBtn->setScale9Enabled(true);
    visitBtn->setContentSize(Size(508, 42));
    visitBtn->setTitleText("手术");
    visitBtn->setTitleColor(Color3B(40, 40, 40));
    visitBtn->setTitleFontSize(40);
    visitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("手术");
        }
        default:
            break;
    }
    });
    layer->addChild(visitBtn);
    
    auto timeLB = Label::createWithSystemFont("选择29日安排病人","Arial",40,Size(visibleSize.width,60),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(visibleSize.width/2,710));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0.5, 0));
    layer->addChild(timeLB);
    
    
    return layer;
    
}


void SickRoomScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            if (index==6) {//评分
                auto markSC=MarkScene::createScene();
                Director::getInstance()->pushScene(markSC);
            }else if(index==4){
                auto charSC=CharacterScene::createScene();
                Director::getInstance()->pushScene(charSC);
            }else if(index==0){
                auto SC=DocUserInfoScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==3){
                auto SC=SymptomScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==2){
                auto SC=ImpressionScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==7){
                auto SC=TreatScene::createScene();
                Director::getInstance()->pushScene(SC);
            }
            
            
            break;
        }
        default:
            break;
    }
}
void SickRoomScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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
    

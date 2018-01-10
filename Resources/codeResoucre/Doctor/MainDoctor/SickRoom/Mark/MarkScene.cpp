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
    
    ListView* lv = ListView::create();
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
    
    auto layer1 = createMessageLayout(0,"颈椎JOA","2");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(0,"腰椎JOA","2");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(0,"ASIA","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(0,"Lenke分型","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(0,"Risser","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createMessageLayout(0,"NDI","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createMessageLayout(0,"VAS","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createMessageLayout(0,"OPLL","");
    lv->insertCustomItem(layer8,7);
    
    return true;
    
}

Layout *MarkScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
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

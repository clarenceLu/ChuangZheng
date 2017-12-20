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

    ScrollView* Select4Scroll=createTableView(Vec2(0, 0), Size(visibleSize.width, visibleSize.height-150));
    bkView->addChild(Select4Scroll);
    return true;
}
ScrollView* ChatScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    scrollView->setInnerContainerSize(Size(visibleSize.width, 160*10));//设置内容大小
    for (int i=0; i<10; i++) {
        auto layer1 = createMessageLayer(i,scrollView->getInnerContainerSize());
        scrollView->addChild(layer1);
    }
    return scrollView;
}

Layer* ChatScene::createMessageLayer(int i, Size  innerSize){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(Size(visibleSize.width, 153));
    layer->setPosition(Point(0,innerSize.height-160*(i+1)+10));
    layer->setAnchorPoint(Vec2(0, 0));
    layer->setTag(1000+i);
    
    auto bkView=Sprite::create("bk_tableView_white.png");
    bkView->setPosition(Vec2(visibleSize.width/2, 0));
    bkView->setAnchorPoint(Vec2(0.5, 0));
    bkView->setContentSize(layer->getContentSize());
    layer->addChild(bkView);
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(15, 15));
    headBtn->setTouchEnabled(true);
    headBtn->ignoreContentAdaptWithSize(true);
    headBtn->setScale9Enabled(true);
    headBtn->setContentSize(Size(120, 120));
    headBtn->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            auto chatSC=ChatUserDetailScene::createScene();
            Director::getInstance()->pushScene(chatSC);
        }
    });
 
        auto contentLB = Label::createWithSystemFont("20160608","Arial",32,Size(380,50),TextHAlignment::LEFT,TextVAlignment::TOP);
        contentLB->setPosition(Point(150,10));
        contentLB->setTextColor(Color4B(0, 0, 0, 255/2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(contentLB);

        auto jobLB = Label::createWithSystemFont("介绍人:周大伟","Arial",32,Size(380,50),TextHAlignment::RIGHT,TextVAlignment::TOP);
        jobLB->setPosition(Point(visibleSize.width-400,10));
        jobLB->setTextColor(Color4B(0, 0, 0, 255/2));
        jobLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(jobLB);
                                   
    auto nameLB = Label::createWithSystemFont("张敏","Arial",35,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(150,80));
    nameLB->setTextColor(Color4B(0, 0, 0, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(nameLB);
    
    auto timeLB = Label::createWithSystemFont("早上6:00","Arial",25,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(513,80));
    timeLB->setTextColor(Color4B(0, 0, 0, 255/3));
    timeLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(timeLB);
    return layer;
}


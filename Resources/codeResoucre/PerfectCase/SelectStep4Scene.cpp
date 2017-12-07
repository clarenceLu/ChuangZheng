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
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SelectStep4Scene::createScene(){
    return SelectStep4Scene::create();
}
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
    
    return true;
}

ScrollView* SelectStep4Scene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    scrollView->setInnerContainerSize(Size(visibleSize.width*4, 200));//设置内容大小
    for (int i=0; i<4; i++) {
        auto layer1 = LayerColor::create(Color4B(arc4random()%255, arc4random()%255, arc4random()%255, 255));
        layer1->setContentSize(Size(visibleSize.width, 200));
        layer1->setPosition(Point(visibleSize.width*i, 0));
        layer1->setAnchorPoint(Vec2(0, 0));
        scrollView->addChild(layer1);
    }
    
    return scrollView;
}

void SelectStep4Scene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    switch (type){
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            
            CCLOG("DETACH_WITH_IME");
            
            break;
            
    }
    
}

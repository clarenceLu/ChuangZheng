//
//  SpineTendernessScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/21.
//

#include "SpineTendernessScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SpineTendernessScene::createScene(){
    return SpineTendernessScene::create();
}
bool judgeTouchMoveWith(Vec2 origin,cocos2d::Ref * ref);
bool SpineTendernessScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_SpineTenderness.png");
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
        case ui::Widget::TouchEventType::ENDED:
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    createRectButton(Vec2(100, 400),101);
    
    
//添加触控监听
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_2(SpineTendernessScene::onTouchesBegan,this);
    listen->onTouchesMoved = CC_CALLBACK_2(SpineTendernessScene::onTouchesMoved,this);
    listen->onTouchesEnded = CC_CALLBACK_2(SpineTendernessScene::onTouchesEnded,this);
    listen->onTouchesCancelled = CC_CALLBACK_2(SpineTendernessScene::onTouchesCancelled,this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
    return true;
}

void   SpineTendernessScene::createRectButton(Vec2 point,int tag){
    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_spine_white.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_spine_blue.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(SpineTendernessScene::menuSelectCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(point); //设置坐标在屏幕居中
    toggle->setTag(tag);
    toggle->setAnchorPoint(Vec2(0, 0));
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    box->setTag(tag);
    this->addChild(box);
    
    auto endLB=Label::createWithSystemFont("3","Arial",40,Size(start->getContentSize()),TextHAlignment::CENTER,TextVAlignment::CENTER);
    endLB->setPosition(point);
    endLB->setTextColor(Color4B(0, 0, 0, 255));
    endLB->setColor(Color3B::WHITE);
    endLB->setTag(tag+100);
    endLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(endLB);
}

void SpineTendernessScene::menuSelectCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    int tag= item->getTag();
    Label *num=(Label*)this->getChildByTag(tag+100);
    if (index==1) {
            num->setTextColor(Color4B::WHITE);
        }else{
            num->setTextColor(Color4B::BLACK);
        }
}


//触摸事件开始，手指按下时
void SpineTendernessScene::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    for(auto &item : touches)
    {
        auto touch = item;
        auto pos1 = touch->getLocation();
        auto pos2 = touch->getLocationInView();
        auto pos3 = Director::getInstance()->convertToUI(pos2);
        if (pos1.x-pos3.x<0) {
            log("从右往左滑动");
        }
        if (pos1.y-pos3.y<0) {
             log("从上往下滑动");
        }
//        CheckBox* testBox=(CheckBox*)this->getChildByTag(101);
//        if (judgeTouchMoveWith(pos1, testBox)) {
//            testBox->setSelected(true);
//        }
    }
}
//触摸移动事件，也就是手指在屏幕滑动的过程
void SpineTendernessScene::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    log("TouchTest onTouchesMoved");
    for(auto &item : touches)
    {
        auto touch = item;
        auto pos1 = touch->getLocation();
        auto pos2 = touch->getLocationInView();
        auto pos3 = Director::getInstance()->convertToUI(pos2);
        log("pos1 x: %f, y: %f",pos1.x,pos1.y);
        log("pos2 x: %f, y: %f",pos2.x,pos2.y);
        log("pos2 x: %f, y: %f",pos3.x,pos3.y);
        Menu* menu=(Menu*)this->getChildByTag(101);
        MenuItemToggle *toggle=(MenuItemToggle*)menu->getChildByTag(101);
        Label *num=(Label*)this->getChildByTag(201);
        if (judgeTouchMoveWith(pos1, toggle)) {
            toggle->setSelectedIndex(1);
            num->setTextColor(Color4B::WHITE);
        }
    }
}
//触摸事件结束，也就是手指松开时
void SpineTendernessScene::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    log("TouchTest onTouchesEnded");
}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断
void SpineTendernessScene::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    log("TouchTest onTouchesCancelled");
}
#pragma -touchMove路径上是否触摸的sprite等
bool judgeTouchMoveWith(Vec2 origin,cocos2d::Ref * ref){
    MenuItemToggle* item = (MenuItemToggle*)ref;
    if (origin.x>=item->getPosition().x&&origin.x<=item->getContentSize().width+item->getPosition().x&&origin.y>=item->getPosition().y&&origin.y<=item->getContentSize().height+item->getPosition().y) {
        return true;
    }
    return false;
}


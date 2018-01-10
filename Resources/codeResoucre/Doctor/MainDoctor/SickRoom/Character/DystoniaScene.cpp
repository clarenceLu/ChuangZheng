//
//  DystoniaScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "DystoniaScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *DystoniaScene::createScene(){
    return DystoniaScene::create();
}
bool DystoniaScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_muscle.png");
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
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    auto senseLB = Label::createWithSystemFont("上肢","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,927));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("减弱","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, 877));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, 877));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(1);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(DystoniaScene::checkBoxCallback,this));
    addChild(acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("增强","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(214, 877));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(294, 877));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(2);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(DystoniaScene::checkBoxCallback,this));
    addChild(refuseBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,862));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV8);
    
    
    auto senseLB2 = Label::createWithSystemFont("下肢","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB2->setPosition(Point(54,792));
    senseLB2->setTextColor(Color4B(91,144,230, 255));
    senseLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB2);
    
    auto acceptLB2= Label::createWithSystemFont("减弱","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB2->setPosition(Vec2(54, 732));
    acceptLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB2);
    auto acceptBox2 = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox2->setPosition(Vec2(134, 732));
    acceptBox2->setAnchorPoint(Vec2(0, 0));
    acceptBox2->setTag(3);
    acceptBox2->setTouchEnabled(true);
    acceptBox2->addEventListener(CC_CALLBACK_2(DystoniaScene::checkBoxCallback,this));
    addChild(acceptBox2);
    
    auto refuseLB2= Label::createWithSystemFont("增强","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB2->setPosition(Vec2(214, 732));
    refuseLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB2);
    auto refuseBox2 = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox2->setPosition(Vec2(294, 732));
    refuseBox2->setAnchorPoint(Vec2(0, 0));
    refuseBox2->setTag(4);
    refuseBox2->setTouchEnabled(true);
    refuseBox2->addEventListener(CC_CALLBACK_2(DystoniaScene::checkBoxCallback,this));
    addChild(refuseBox2);
    
    
    return true;
}
void DystoniaScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            if (tag==1||tag==2) {
            for (int i=1; i<3; i++) {
                CheckBox*box=(CheckBox*)this->getChildByTag(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }}
            if (tag==3||tag==4) {
                for (int i=3; i<5; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
        {
        }
            break;
        default:
            break;
    }
}

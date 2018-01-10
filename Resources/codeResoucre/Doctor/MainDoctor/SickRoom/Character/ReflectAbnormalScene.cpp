//
//  ReflectAbnormalScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "ReflectAbnormalScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ReflectAbnormalScene::createScene(){
    return ReflectAbnormalScene::create();
}
bool ReflectAbnormalScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_reflect_abnormal.png");
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
    
    createSelectView(1, bkView, 875,"肱二头肌反射");
    createSelectView(4, bkView, 755,"肱三头肌反射");
    createSelectView(7, bkView, 635,"桡骨膜反射");
     createSelectView2(10, bkView, 515,"提睾反射");
    createSelectView2(12, bkView, 395,"肛门反射");
    createSelectView2(14, bkView, 275,"腹壁反射");
    createSelectView(16, bkView, 155,"膝跳反射");
    createSelectView(19, bkView, 35,"跟腱反射");
    
    return true;
}
void ReflectAbnormalScene::createSelectView(int tag,Sprite*bkView,float originY,string title){
    auto senseLB = Label::createWithSystemFont(title,"Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,originY+50));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("亢进","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, originY));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, originY));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("活跃","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(214, originY));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(294, originY));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(refuseBox);
    
    auto otherLB= Label::createWithSystemFont("未引出","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    otherLB->setPosition(Vec2(374, originY));
    otherLB->setTextColor(Color4B(0,0,0, 255/3*2));
    otherLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(otherLB);
    auto otherBox = CheckBox::create("select_circle.png","select_sure.png");
    otherBox->setPosition(Vec2(484, originY));
    otherBox->setAnchorPoint(Vec2(0, 0));
    otherBox->setTag(tag+2);
    otherBox->setTouchEnabled(true);
    otherBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(otherBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,originY-15));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(575, 2.5));
    bkView->addChild(lineV8);
    
}

void ReflectAbnormalScene::createSelectView2(int tag,Sprite*bkView,float originY,string title){
    auto senseLB = Label::createWithSystemFont(title,"Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,originY+50));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("L未引出","Arial",35,Size(180,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, originY));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(194, originY));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("R未引出","Arial",35,Size(180,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(284, originY));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(424, originY));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(ReflectAbnormalScene::checkBoxCallback,this));
    addChild(refuseBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,originY-15));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(575, 2.5));
    bkView->addChild(lineV8);
    
}



void ReflectAbnormalScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            if (tag>=1&&tag<4) {
                for (int i=1; i<4; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=4&&tag<7) {
                for (int i=4; i<7; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=7&&tag<10) {
                for (int i=7; i<10; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=10&&tag<12) {
                for (int i=10; i<12; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=12&&tag<14) {
                for (int i=12; i<14; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=14&&tag<16) {
                for (int i=14; i<16; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=16&&tag<19) {
                for (int i=16; i<19; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
          else  if (tag>=19&&tag<22) {
                for (int i=19; i<22; i++) {
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

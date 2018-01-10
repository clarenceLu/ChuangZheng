//
//  ReflectScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "ReflectScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ReflectScene::createScene(){
    return ReflectScene::create();
}
bool ReflectScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_reflect.png");
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
    
    createSelectView(1, bkView, 875,"Hoffman征阳性");
    createSelectView(3, bkView, 755,"Babinski征阳性");
    createSelectView(5, bkView, 635,"踝阵挛阳性");
    
    return true;
}

void ReflectScene::createSelectView(int tag,Sprite*bkView,float originY,string title){
    auto senseLB = Label::createWithSystemFont(title,"Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,originY+50));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("L","Arial",35,Size(80,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, originY));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, originY));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ReflectScene::checkBoxCallback,this));
    addChild(acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("R","Arial",35,Size(80,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(184, originY));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(264, originY));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(ReflectScene::checkBoxCallback,this));
    addChild(refuseBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,originY-15));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV8);
    
}



void ReflectScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            if (tag>=1&&tag<3) {
                for (int i=1; i<3; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
            else  if (tag>=3&&tag<5) {
                for (int i=3; i<5; i++) {
                    CheckBox*box=(CheckBox*)this->getChildByTag(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }}
            else  if (tag>=5&&tag<7) {
                for (int i=5; i<7; i++) {
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

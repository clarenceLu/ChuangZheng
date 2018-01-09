//
//  SenseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "SenseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SenseAbnormalScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SenseScene::createScene(){
    return SenseScene::create();
}
bool SenseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_sense.png");
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
    
    auto senseLB = Label::createWithSystemFont("感觉","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    senseLB->setPosition(Point(54,927));
    senseLB->setTextColor(Color4B(91,144,230, 255));
    senseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(senseLB);
    
    auto acceptLB= Label::createWithSystemFont("减退","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(54, 857));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(134, 857));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(1);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(SenseScene::checkBoxCallback,this));
    addChild(acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("消失","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(214, 857));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(294, 857));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(2);
    refuseBox->setTouchEnabled(true);
    refuseBox->addEventListener(CC_CALLBACK_2(SenseScene::checkBoxCallback,this));
    addChild(refuseBox);
    
    auto allLB= Label::createWithSystemFont("过敏","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    allLB->setPosition(Vec2(374, 857));
    allLB->setTextColor(Color4B(0,0,0, 255/3*2));
    allLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(allLB);
    auto allBox = CheckBox::create("select_circle.png","select_sure.png");
    allBox->setPosition(Vec2(454, 857));
    allBox->setAnchorPoint(Vec2(0, 0));
    allBox->setTag(3);
    allBox->setTouchEnabled(true);
    allBox->addEventListener(CC_CALLBACK_2(SenseScene::checkBoxCallback,this));
    addChild(allBox);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,842));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV8);
    
    auto otherLB = Label::createWithSystemFont("符合神经支配皮区分布","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    otherLB->setPosition(Point(54,770));
    otherLB->setTextColor(Color4B(91,144,230, 255));
    otherLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(otherLB);
    
    auto confirmBtn=Button::create();
    confirmBtn->loadTextures("btn_sense_sure.png", "btn_sense_sure.png");
    confirmBtn->setPosition(Vec2(167, 714));
    confirmBtn->setScale(0.87);
    confirmBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto senseSC=SenseAbnormalScene::createScene();
            Director::getInstance()->pushScene(senseSC);
        }
            
        default:
            break;
    }
    });
    this->addChild(confirmBtn);
    
    auto cancelBtn=Button::create();
    cancelBtn->loadTextures("btn_sense_cancel.png", "btn_sense_cancel.png");
    cancelBtn->setPosition(Vec2(335, 714));
    cancelBtn->setScale(0.87);
    cancelBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto senseSC=SenseAbnormalScene::createScene();
            Director::getInstance()->pushScene(senseSC);
        }
            
        default:
            break;
    }
    });
    this->addChild(cancelBtn);
    
    
    
    return true;
}
void SenseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            for (int i=1; i<4; i++) {
                CheckBox*box=(CheckBox*)this->getChildByTag(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
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


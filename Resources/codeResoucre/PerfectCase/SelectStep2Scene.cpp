//
//  SelectStep2Scene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#include "SelectStep2Scene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SelectStep2Scene::createScene(){
    return SelectStep2Scene::create();
}
bool SelectStep2Scene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_step2.png");
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
    sureBtn->loadTextures("btn_step2_sure.png", "btn_step2_sure.png");
    sureBtn->setPosition(Vec2(185, 474));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.86);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    auto textFieldContent= TextField::create("一百字以内","Arial",35);
    textFieldContent->setMaxLength(240);
//用于多行输入
    textFieldContent->ignoreContentAdaptWithSize(false);
    textFieldContent->setTouchSize(Size(visibleSize.width-80, 300));
    textFieldContent->setPosition(Vec2(40,visibleSize.height-250));
    textFieldContent->setAnchorPoint(Vec2(0,1));
    textFieldContent->setContentSize(Size(visibleSize.width-80,300));
    textFieldContent->setTextColor(Color4B::BLACK);
    textFieldContent->setPlaceHolderColor(Color4B::GRAY);
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->addEventListener(CC_CALLBACK_2(SelectStep2Scene::eventCallBack, this));
    bkView->addChild(textFieldContent);
    
    return true;
};


void SelectStep2Scene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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

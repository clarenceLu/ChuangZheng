//
//  PerfectCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#include "PerfectCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "UserCaseScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *PerfectCaseScene::createScene(){
    return PerfectCaseScene::create();
}
bool PerfectCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_perfect_case.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    this->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-90));
    backBtn->setScale(0.87);
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto step1Btn=Button::create();
    step1Btn->loadTextures("step1.png", "step1.png");
    step1Btn->setPosition(Vec2(20, visibleSize.height-300));
    step1Btn->setAnchorPoint(Vec2(0,0));
    step1Btn->setScale(0.86);
    step1Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            
        }
        default:
            break;
    }
    });
    this->addChild(step1Btn);
    
    auto step2Btn=Button::create();
    step2Btn->loadTextures("step2.png", "step2.png");
    step2Btn->setPosition(Vec2(20, visibleSize.height-450));
    step2Btn->setAnchorPoint(Vec2(0,0));
    step2Btn->setScale(0.86);
    step2Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            
        }
        default:
            break;
    }
    });
    this->addChild(step2Btn);
    
    auto step3Btn=Button::create();
    step3Btn->loadTextures("step3.png", "step3.png");
    step3Btn->setPosition(Vec2(20, visibleSize.height-600));
    step3Btn->setAnchorPoint(Vec2(0,0));
    step3Btn->setScale(0.86);
    step3Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            
        }
        default:
            break;
    }
    });
    this->addChild(step3Btn);
    
    auto step4Btn=Button::create();
    step4Btn->loadTextures("step4.png", "step4.png");
    step4Btn->setPosition(Vec2(20, visibleSize.height-750));
    step4Btn->setAnchorPoint(Vec2(0,0));
    step4Btn->setScale(0.86);
    step4Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            
        }
        default:
            break;
    }
    });
    this->addChild(step4Btn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_perfect_sure.png", "btn_perfect_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width/2-135, visibleSize.height-930));
    sureBtn->setAnchorPoint(Vec2(0, 0));
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
    
    auto bottom=Sprite::create("bk_perfect_bottom.png");
    bottom->setPosition(Vec2(0, 0));
    bottom->setAnchorPoint(Vec2(0, 0));
    this->addChild(bottom);
    
    
    auto caseCheckBox = CheckBox::create("btn_case_unselect.png","btn_case_select.png");
    //设置CheckBox的位置
    caseCheckBox->setPosition(Vec2(50,15));
    caseCheckBox->setTag(0);
    caseCheckBox->setAnchorPoint(Vec2(0, 0));
    caseCheckBox->setScale(0.9);
    //设置CheckBox是否可点击
    caseCheckBox->setTouchEnabled(true);
    caseCheckBox->addEventListener(CC_CALLBACK_2(PerfectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(caseCheckBox);
    
    auto informCheckBox = CheckBox::create("btn_inform_unselect.png","btn_inform_select.png");
    //设置CheckBox的位置
    informCheckBox->setPosition(Vec2(200,15));
    informCheckBox->setTag(1);
    informCheckBox->setAnchorPoint(Vec2(0, 0));
    informCheckBox->setScale(0.9);
    //设置CheckBox是否可点击
    informCheckBox->setTouchEnabled(true);
    informCheckBox->addEventListener(CC_CALLBACK_2(PerfectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(informCheckBox);
    
    auto dynamicCheckBox = CheckBox::create("btn_dynamic_unselect.png","btn_dynamic_select.png");
    //设置CheckBox的位置
    dynamicCheckBox->setPosition(Vec2(340,15));
    dynamicCheckBox->setTag(2);
    dynamicCheckBox->setAnchorPoint(Vec2(0, 0));
    dynamicCheckBox->setScale(0.9);
    //设置CheckBox是否可点击
    dynamicCheckBox->setTouchEnabled(true);
    dynamicCheckBox->addEventListener(CC_CALLBACK_2(PerfectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(dynamicCheckBox);
    
    auto userCheckBox = CheckBox::create("btn_user_unselect.png","btn_user_select.png");
    //设置CheckBox的位置
    userCheckBox->setPosition(Vec2(520,15));
    userCheckBox->setTag(3);
    userCheckBox->setAnchorPoint(Vec2(0, 0));
    userCheckBox->setScale(0.9);
    //设置CheckBox是否可点击
    userCheckBox->setTouchEnabled(true);
    userCheckBox->addEventListener(CC_CALLBACK_2(PerfectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(userCheckBox);
    
    return true;
}


//实现CheckBox回调函数
void PerfectCaseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        for (int i=0; i<4; i++) {
            if (i!=tag) {
         CheckBox * checkBox=(CheckBox*)this->getChildByTag(i);
                checkBox->setSelected(false);
            }
        }
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            if (tag==0) {
                auto userCaseSC=UserCaseScene::create();
                Director::getInstance()->replaceScene(userCaseSC);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

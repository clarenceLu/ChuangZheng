//
//  CaseSearchScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#include "CaseSearchScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "CaseListScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *CaseSearchScene::createScene(){
    return CaseSearchScene::create();
}
bool CaseSearchScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_case_search.png");
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
    sureBtn->loadTextures("btn_group_leader_sure.png", "btn_group_leader_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto scene=CaseListScene::createScene();
            Director::getInstance()->pushScene(scene);
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    //二维码
    auto judgeBtn=Button::create();
    judgeBtn->loadTextures("btn_caseSearch_next.png", "btn_caseSearch_next.png");
    judgeBtn->setPosition(Vec2(visibleSize.width-85, 415));
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            
        }
        default:
            break;
    }
    });
    bkView->addChild(judgeBtn);
    
    
     textFiledName=createBasicData(bkView, Vec2(56, 910), "姓名：","未填写");
    textFiledSex=createBasicData(bkView, Vec2(56, 820), "性别：","未填写");
    textFiledAge=createBasicData(bkView, Vec2(56, 730), "年龄：","未填写");
    textFiledCase=createBasicData(bkView, Vec2(56, 640), "病案号：","未填写");
    
//住院区间
    auto userName = Label::createWithSystemFont("住院区间：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(Vec2(56, 550));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto textFiledDate1 = TextField::create("2017.08.05","Arial",35);
    textFiledDate1->setMaxLength(40);
    textFiledDate1->setTouchSize(Size(visibleSize.width-300, 50));
    textFiledDate1->setPosition(Vec2(visibleSize.width-70,500));
    textFiledDate1->setAnchorPoint(Vec2(1,0));
    textFiledDate1->setContentSize(Size(visibleSize.width-300,50));
    textFiledDate1->setTextColor(Color4B::BLACK);
    textFiledDate1->setPlaceHolderColor(Color4B::GRAY);
    textFiledDate1->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFiledDate1->addEventListener(CC_CALLBACK_2(CaseSearchScene::eventCallBack, this));
    bkView->addChild(textFiledDate1);
    
    auto separateLB = Label::createWithSystemFont("至","Arial",35,Size(80,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    separateLB->setPosition(Vec2(visibleSize.width/2, 500));
    separateLB->setTextColor(Color4B(91, 144, 229, 255));
    separateLB->setAnchorPoint(Vec2(0.5, 0));
    bkView->addChild(separateLB);
    
    auto textFiledDate2 = TextField::create("2017.06.05","Arial",35);
    textFiledDate2->setMaxLength(40);
    textFiledDate2->setTouchSize(Size(visibleSize.width-300, 50));
    textFiledDate2->setPosition(Vec2(56,500));
    textFiledDate2->setAnchorPoint(Vec2(0,0));
    textFiledDate2->setContentSize(Size(visibleSize.width-300,50));
    textFiledDate2->setTextColor(Color4B::BLACK);
    textFiledDate2->setPlaceHolderColor(Color4B::GRAY);
    textFiledDate2->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFiledDate2->addEventListener(CC_CALLBACK_2(CaseSearchScene::eventCallBack, this));
    bkView->addChild(textFiledDate2);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(50, 490));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    
    createLabelWithoutField(bkView,Vec2(56, 410),"二维码：");
    
    return true;
}
void  CaseSearchScene::createLabelWithoutField(Sprite* bkView,Vec2 point,string name){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(50, point.y-15));
    lineV->setAnchorPoint(Vec2(0, 0));
     lineV->setScaleX(0.85);
    bkView->addChild(lineV);
}
TextField*  CaseSearchScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name1,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto textFieldUser = TextField::create(name2,"Arial",35);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(visibleSize.width-300, 50));
    textFieldUser->setPosition(Vec2(visibleSize.width-70,point.y));
    textFieldUser->setAnchorPoint(Vec2(1,0));
    textFieldUser->setContentSize(Size(visibleSize.width-300,50));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->addEventListener(CC_CALLBACK_2(CaseSearchScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-15));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}
void CaseSearchScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    int tag= textField->getTag();
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            if (tag>=1000&&tag<=1002) {
                
            }
            CCLOG("DETACH_WITH_IME");
            
            break;
            
    }
    
}

//
//  MedicalRecordScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/14.
//

#include "MedicalRecordScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MedicalRecordScene::createScene(){
    return MedicalRecordScene::create();
}
bool MedicalRecordScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_medicalRecord.png");
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
    
     float height1=createLabel(Vec2(0, 900), "责任医生：", "刘玄德,张翼德,关云长",bkView);
    float height2= createLabel(Vec2(0, 810+41-height1), "印象：", "头后仰上身麻无敌无敌无敌无敌无敌", bkView);
    float height3= createLabel(Vec2(0, 720+41*2-height2-height1), "症状：", "右手麻木，右手疼痛", bkView);
    float height4= createLabel(Vec2(0, 630+41*3-height3-height2-height1), "体征：", "体质弱", bkView);
    float height5= createLabel(Vec2(0, 540+41*4-height4-height3-height2-height1), "影像：", "无", bkView);
    float height6= createLabel(Vec2(0, 450+41*5-height5-height4-height3-height2-height1), "评分：", "颈椎", bkView);
    float height7= createLabel(Vec2(0, 360+41*6-height6-height5-height4-height3-height2-height1), "治疗方式：", "手术，支架", bkView);
    float height8= createLabel(Vec2(0, 270+41*7-height7-height6-height5-height4-height3-height2-height1), "备注：", "多喝水", bkView);
    
    return true;
}

float MedicalRecordScene::createLabel(Vec2 point,string name1,string name2,Sprite* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto nameLB = Label::createWithSystemFont(name1,"fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(56,point.y));
    nameLB->setTextColor(Color4B(91,144,230, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB);
    
    auto nameLB2 = Label::createWithSystemFont(name2,"Arial",35,Size(visibleSize.width-265,0),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    float height=nameLB2->getContentSize().height;
    nameLB2->setPosition(Point(218,point.y+41-height));
    nameLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    nameLB2->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB2);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y+31-height));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.87);
    superV->addChild(lineV);
    
    return height;
}


void MedicalRecordScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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


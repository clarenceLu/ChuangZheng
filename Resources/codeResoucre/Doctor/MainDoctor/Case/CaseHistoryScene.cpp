//
//  CaseHistoryScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#include "CaseHistoryScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "AddHospitalCaseScene.hpp"
#include "AddVisitCaseScene.hpp"
#include "AddOutpatientCaseScene.hpp"
#include "WaitChatDetailScene.hpp"
#include "SickRoomScene.hpp"
#include "VisitCaseScene.hpp"
#include "OutpatientCaseScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *CaseHistoryScene::createScene(){
    return CaseHistoryScene::create();
}
bool CaseHistoryScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_caseHistory.png");
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
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_addCase_add.png", "btn_addCase_add.png");
    addBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=addCaseLayer();
            layer->setTag(1000);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    this->addChild(addBtn);
    
    createLabelWithoutField(bkView,Vec2(56, 910),"张牧之",1);
    auto sex = Label::createWithSystemFont("男","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    sex->setPosition(Vec2(250, 910));
    sex->setTextColor(Color4B(91, 144, 229, 255));
    sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(sex);
    auto age = Label::createWithSystemFont("60","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    age->setPosition(Vec2(350, 910));
    age->setTextColor(Color4B(91, 144, 229, 255));
    age->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(age);
    auto num = Label::createWithSystemFont("865","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    num->setPosition(Vec2(450, 910));
    num->setTextColor(Color4B(91, 144, 229, 255));
    num->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(num);
    
    createLabelWithoutField(bkView,Vec2(56, 800),"随访",2);
    auto time1 = Label::createWithSystemFont("2017-12-14","Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    time1->setPosition(Vec2(160, 800));
    time1->setTextColor(Color4B(91, 144, 229, 255));
    time1->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(time1);
    
    createLabelWithoutField(bkView,Vec2(56, 710),"门诊",3);
    auto time2 = Label::createWithSystemFont("2017-12-14","Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    time2->setPosition(Vec2(160, 710));
    time2->setTextColor(Color4B(91, 144, 229, 255));
    time2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(time2);
    
    createLabelWithoutField(bkView,Vec2(56, 620),"住院",4);
    auto time3 = Label::createWithSystemFont("2017-12-14","Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    time3->setPosition(Vec2(160, 620));
    time3->setTextColor(Color4B(91, 144, 229, 255));
    time3->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(time3);
    
    createLabelWithoutField(bkView,Vec2(56, 530),"自建",5);
    auto time4 = Label::createWithSystemFont("2017-12-14","Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    time4->setPosition(Vec2(160, 530));
    time4->setTextColor(Color4B(91, 144, 229, 255));
    time4->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(time4);
    return true;
    
}

void  CaseHistoryScene::createLabelWithoutField(Sprite* bkView,Vec2 point,string name,int tag){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto judgeBtn=Button::create();
    judgeBtn->loadTextures("btn_caseSearch_next.png", "btn_caseSearch_next.png");
    judgeBtn->setPosition(Vec2(visibleSize.width-85, point.y+5));
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setTag(tag);
    judgeBtn->addTouchEventListener(CC_CALLBACK_2(CaseHistoryScene::buttonCallback, this));
    bkView->addChild(judgeBtn);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(50, point.y-15));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
}

//新建病例
Layer* CaseHistoryScene::addCaseLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255/3));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    auto contentV = Sprite::create("bk_addCase.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,352));
    contentV->setContentSize(Size(508, 428));
    layer->addChild(contentV);
    auto cancelBtn=Button::create();
    cancelBtn->loadTextures("btn_addCase_cancel.png", "btn_addCase_cancel.png");
    cancelBtn->setPosition(Vec2(120, 15));
    cancelBtn->setAnchorPoint(Vec2(0,0));
    cancelBtn->setScale(0.87);
    cancelBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(1000);
        }
            break;
        default:
            break;
    }
    });
    contentV->addChild(cancelBtn);
    
//住院
    auto hospitalBtn=Button::create();
    hospitalBtn->loadTextures("alpha.png", "alpha.png");
    hospitalBtn->setPosition(Vec2(visibleSize.width/2, 478));
    hospitalBtn->setScale9Enabled(true);
    hospitalBtn->setContentSize(Size(508, 42));
    hospitalBtn->setTitleText("新建住院病历");
    hospitalBtn->setTitleColor(Color3B(40, 40, 40));
    hospitalBtn->setTitleFontSize(40);
    hospitalBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto hospitalCase=AddHospitalCaseScene::createScene();
            Director::getInstance()->pushScene(hospitalCase);
        }
        default:
            break;
    }
    });
    layer->addChild(hospitalBtn);
    
    //门诊
    auto outpatientBtn=Button::create();
    outpatientBtn->loadTextures("alpha.png", "alpha.png");
    outpatientBtn->setPosition(Vec2(visibleSize.width/2, 563));
    outpatientBtn->setScale9Enabled(true);
    outpatientBtn->setContentSize(Size(508, 42));
    outpatientBtn->setTitleText("新建门诊病历");
    outpatientBtn->setTitleColor(Color3B(40, 40, 40));
    outpatientBtn->setTitleFontSize(40);
    outpatientBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto outpatientCase=AddOutpatientCaseScene::createScene();
            Director::getInstance()->pushScene(outpatientCase);
        }
        default:
            break;
    }
    });
    layer->addChild(outpatientBtn);
    
    //随访
    auto visitBtn=Button::create();
    visitBtn->loadTextures("alpha.png", "alpha.png");
    visitBtn->setPosition(Vec2(visibleSize.width/2, 648));
    visitBtn->setScale9Enabled(true);
    visitBtn->setContentSize(Size(508, 42));
    visitBtn->setTitleText("新建随访病历");
    visitBtn->setTitleColor(Color3B(40, 40, 40));
    visitBtn->setTitleFontSize(40);
    visitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto visitCase=AddVisitCaseScene::createScene();
            Director::getInstance()->pushScene(visitCase);
        }
        default:
            break;
    }
    });
    layer->addChild(visitBtn);
    return layer;
    
}




void CaseHistoryScene::buttonCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Button* item = (Button*)pSender;
            int tag= item->getTag();
            log("%d",tag);
            if (tag==1) {
                auto chatSC=(WaitChatDetailScene*)WaitChatDetailScene::createScene();
                chatSC->type=1;
                Director::getInstance()->pushScene(chatSC);
            }
            if (tag==4) {
                auto sickroomSC=(SickRoomScene*)SickRoomScene::createScene();
                Director::getInstance()->pushScene(sickroomSC);
            }if (tag==2) {
                auto SC=(VisitCaseScene*)VisitCaseScene::createScene();
                Director::getInstance()->pushScene(SC);
            }if (tag==3) {
                auto SC=(OutpatientCaseScene*)OutpatientCaseScene::createScene();
                Director::getInstance()->pushScene(SC);
            }
            
        }
        default:
            break;
    }
}


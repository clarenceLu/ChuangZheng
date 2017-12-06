//
//  UserCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#include "UserCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SelectCaseScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *UserCaseScene::createScene(){
    return UserCaseScene::create();
}
LayerMultiplex *multLayer;
bool UserCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    
    auto layer2=createInformLayer();
    auto layer1=createCaseLayer();
    multLayer = LayerMultiplex::create(layer1, layer2, nullptr);
    addChild(multLayer, 0);
    
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
    caseCheckBox->setSelected(true);
    caseCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
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
    informCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
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
    dynamicCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
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
    userCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(userCheckBox);
    return true;
}

//通知
Layer* UserCaseScene::createInformLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(origin.x, origin.y));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_notification.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto notificationHospitalBtn=Button::create();
    notificationHospitalBtn->loadTextures("btn_notification_hospital.png", "btn_notification_hospital.png");
    notificationHospitalBtn->setPosition(Vec2(20, visibleSize.height-170));
    notificationHospitalBtn->setAnchorPoint(Vec2(0, 1));
    notificationHospitalBtn->setScale(0.85);
    notificationHospitalBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
        {
            auto sprite = Sprite::create("notification_none.png");
                sprite->setPosition(Vec2(130, 520));
                sprite->setAnchorPoint(Vec2(0, 0));
                setOpacity(30);
                this->addChild(sprite, 0);
                 sprite->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            break;
    }
    }
    });
    layer->addChild(notificationHospitalBtn);
    
    auto chatBtn=Button::create();
    chatBtn->loadTextures("btn_notification_chat.png", "btn_notification_chat.png");
    chatBtn->setPosition(Vec2(20, visibleSize.height-300));
    chatBtn->setAnchorPoint(Vec2(0, 1));
    chatBtn->setScale(0.85);
    chatBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    layer->addChild(chatBtn);
    
    auto informBtn=Button::create();
    informBtn->loadTextures("btn_notification_info.png", "btn_notification_info.png");
    informBtn->setPosition(Vec2(20, visibleSize.height-430));
    informBtn->setAnchorPoint(Vec2(0, 1));
    informBtn->setScale(0.85);
    informBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *informLayer=createNotificationInformLayer();
            informLayer->setTag(1000);
            this->addChild(informLayer);
        }
        default:
            break;
    }
    });
    layer->addChild(informBtn);
    
    
    return layer;
}
//复诊说明
Layer* UserCaseScene::createNotificationInformLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(origin.x, origin.y));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    
    auto bkView=Sprite::create("bk_notification_info.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1000);
        default:
            break;
    }
    });
    layer->addChild(backBtn);
    return layer;
}
//病例
Layer* UserCaseScene::createCaseLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_usercase.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_usercase_add.png", "btn_usercase_add.png");
    addBtn->setPosition(Vec2(560, visibleSize.height-90));
    addBtn->setScale(0.95);
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            
        default:
            break;
    }
    });
    layer->addChild(addBtn);
    
    auto blueBK=Sprite::create("usercase_bluerect.png");
    blueBK->setPosition(Vec2(20, visibleSize.height-270));
    blueBK->setAnchorPoint(Vec2(0, 0));
    blueBK->setScale(0.87);
    layer->addChild(blueBK);
    
    auto label = Label::createWithSystemFont("张三丰","fonts/Marker Felt.ttf",45,Size(160,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    label->setPosition(Point(20,28));
    label->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(label);
    
    auto sexLB = Label::createWithSystemFont("男","fonts/Marker Felt.ttf",45,Size(60,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    sexLB->setPosition(Point(200,28));
    sexLB->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(sexLB);
    
    auto ageLB = Label::createWithSystemFont("32岁","Arial",45,Size(120,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    ageLB->setPosition(Point(280,28));
    ageLB->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(ageLB);
    
    auto numLB = Label::createWithSystemFont("330681199404058945","Arial",40,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    numLB->setPosition(Point(400,30));
    numLB->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(numLB);
    
    auto detailBtn=Button::create();
    detailBtn->loadTextures("usercase_detail.png", "usercase_detail.png");
    detailBtn->setPosition(Vec2(20, visibleSize.height-370));
    detailBtn->setAnchorPoint(Vec2(0, 0));
    detailBtn->setScale(0.87);
    detailBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    layer->addChild(detailBtn);
    
    auto detailLB = Label::createWithSystemFont("住院","fonts/Marker Felt.ttf",40,Size(120,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    detailLB->setPosition(Point(20,10));
    detailLB->setTextColor(Color4B::BLACK);
    detailLB->setAnchorPoint(Vec2(0, 0));
    detailBtn->addChild(detailLB);
    
    auto timeLB = Label::createWithSystemFont("2017-04-05","Arial",40,Size(visibleSize.width-280,60),TextHAlignment::CENTER,TextVAlignment::TOP);
    timeLB->setPosition(Point(140,10));
    timeLB->setTextColor(Color4B::BLACK);
    timeLB->setAnchorPoint(Vec2(0, 0));
    detailBtn->addChild(timeLB);
    
    
    
    auto selfBtn=Button::create();
    selfBtn->loadTextures("usercase_detail.png", "usercase_detail.png");
    selfBtn->setPosition(Vec2(20, visibleSize.height-470));
    selfBtn->setAnchorPoint(Vec2(0, 0));
    selfBtn->setScale(0.87);
    selfBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto selectScene= SelectCaseScene::create();
            Director::getInstance()->pushScene(selectScene);
        }
        default:
            break;
    }
    });
    layer->addChild(selfBtn);
    
    auto selfLB = Label::createWithSystemFont("自述","fonts/Marker Felt.ttf",40,Size(120,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    selfLB->setPosition(Point(20,10));
    selfLB->setTextColor(Color4B::BLACK);
    selfLB->setAnchorPoint(Vec2(0, 0));
    selfBtn->addChild(selfLB);
    
    auto selfTime = Label::createWithSystemFont("2017-04-05","Arial",40,Size(visibleSize.width-280,60),TextHAlignment::CENTER,TextVAlignment::TOP);
    selfTime->setPosition(Point(140,10));
    selfTime->setTextColor(Color4B::BLACK);
    selfTime->setAnchorPoint(Vec2(0, 0));
    selfBtn->addChild(selfTime);
    
    return layer;
}




//实现CheckBox回调函数
void UserCaseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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
            if (tag==0||tag==1) {
            multLayer->switchTo(tag);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

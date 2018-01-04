//
//  SickRoomScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/4.
//

#include "SickRoomScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SickRoomScene::createScene(){
    return SickRoomScene::create();
}
bool SickRoomScene::init(){
    if (!Scene::init()) {
        return false;
    }
    bedNum=1;
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_sickroomDetail.png");
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
    
    auto calendarBtn=Button::create();
    calendarBtn->loadTextures("btn_sickroom_calendar.png", "btn_sickroom_calendar.png");
    calendarBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    calendarBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=addCalendarLayer();
            layer->setTag(1000);
            this->addChild(layer);
        }
            
        default:
            break;
    }
    });
    this->addChild(calendarBtn);
    
    return true;
    
}
void SickRoomScene::onEnter()
{
    
    log("%d",bedNum);
    Size visibleSize=Director::getInstance()->getVisibleSize();
    //原谅我用的是layerColor和layer一样的
    Scene::onEnter();
    char str[10];
    sprintf(str,"%d床",bedNum);
    string title=str;
    auto timeLB = Label::createWithSystemFont(title,"Arial",45,Size(380,60),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(visibleSize.width/2,1023));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(timeLB);
    
}

Layer* SickRoomScene::addCalendarLayer(){
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
    auto contentV = Sprite::create("bk_sickroom_calendar.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508, 349));
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
    
    //出院
    auto outpatientBtn=Button::create();
    outpatientBtn->loadTextures("alpha.png", "alpha.png");
    outpatientBtn->setPosition(Vec2(visibleSize.width/2, 563));
    outpatientBtn->setScale9Enabled(true);
    outpatientBtn->setContentSize(Size(508, 42));
    outpatientBtn->setTitleText("出院");
    outpatientBtn->setTitleColor(Color3B(40, 40, 40));
    outpatientBtn->setTitleFontSize(40);
    outpatientBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("出院");
        }
        default:
            break;
    }
    });
    layer->addChild(outpatientBtn);
    
    //手术
    auto visitBtn=Button::create();
    visitBtn->loadTextures("alpha.png", "alpha.png");
    visitBtn->setPosition(Vec2(visibleSize.width/2, 648));
    visitBtn->setScale9Enabled(true);
    visitBtn->setContentSize(Size(508, 42));
    visitBtn->setTitleText("手术");
    visitBtn->setTitleColor(Color3B(40, 40, 40));
    visitBtn->setTitleFontSize(40);
    visitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("手术");
        }
        default:
            break;
    }
    });
    layer->addChild(visitBtn);
    
    auto timeLB = Label::createWithSystemFont("选择29日安排病人","Arial",40,Size(visibleSize.width,60),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(visibleSize.width/2,710));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0.5, 0));
    layer->addChild(timeLB);
    
    
    return layer;
    
}
    

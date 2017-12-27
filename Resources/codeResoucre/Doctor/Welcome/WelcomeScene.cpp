//
//  WelcomeScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#include "WelcomeScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "MainScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *WelcomeScene::createScene(){
    return WelcomeScene::create();
}
bool WelcomeScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_welcome.png");
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
    
    auto contentV=Sprite::create("welcome_content.png");
    contentV->setPosition(Vec2(20, 543));
    contentV->setAnchorPoint(Vec2(0, 0));
    contentV->setContentSize(Size(visibleSize.width-40, 429));
    bkView->addChild(contentV);
    
    string detail="您的信息是否正确？正确请进行下一步。如有问题，请联系后台及时纠正\n电话：123-456789";
    auto detailLB = Label::createWithSystemFont(detail,"Arial",30,Size(560,140),TextHAlignment::LEFT,TextVAlignment::CENTER);
    detailLB->setPosition(Vec2(20,10));
    detailLB->setTextColor(Color4B(0, 0, 0, 255/2));
    detailLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(detailLB);
    
    auto name = Label::createWithSystemFont("姓名：","Arial",40,Size(120,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    name->setPosition(Vec2(20,265));
    name->setTextColor(Color4B(91, 144, 229, 255));
    name->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(name);
    auto nameLB= Label::createWithSystemFont("赵抗议","Arial",40,Size(450,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    nameLB->setPosition(Vec2(150,265));
    nameLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    nameLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(nameLB);
    
    
    auto job = Label::createWithSystemFont("身份：","Arial",40,Size(120,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    job->setPosition(Vec2(20,180));
    job->setTextColor(Color4B(91, 144, 229, 255));
    job->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(job);
    auto jobLB = Label::createWithSystemFont("主治医生","Arial",40,Size(450,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    jobLB->setPosition(Vec2(150,180));
    jobLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    jobLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(jobLB);
    
    auto nextBtn=Button::create();
    nextBtn->loadTextures("btn_welcome_next.png", "btn_welcome_next.png");
    nextBtn->setPosition(Vec2(197, 413));
    nextBtn->setAnchorPoint(Vec2(0, 0));
    nextBtn->setScale(0.87);
    nextBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto mainScene=MainScene::createScene();
            Director::getInstance()->pushScene(mainScene);
        }
        default:
            break;
    }
    });
    this->addChild(nextBtn);
    return true;
}

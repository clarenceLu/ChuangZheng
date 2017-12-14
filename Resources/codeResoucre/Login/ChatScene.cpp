//
//  ChatScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/12.
//

#include "ChatScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "ChatUserDetailScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ChatScene::createScene(){
    return ChatScene::create();
}
bool ChatScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_chat.png");
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
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(visibleSize.width/2, 890));
    headBtn->setTouchEnabled(true);
    headBtn->ignoreContentAdaptWithSize(true);
    headBtn->setScale9Enabled(true);
    headBtn->setContentSize(Size(visibleSize.width-40, 151));
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            auto chatSC=ChatUserDetailScene::createScene();
            Director::getInstance()->pushScene(chatSC);
        }
    });

    return true;
}

//
//  SelectStep3Scene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#include "SelectStep3Scene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SelectStep3Scene::createScene(){
    return SelectStep3Scene::create();
}
bool SelectStep3Scene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_step3.png");
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
    
    auto cameraBtn=Button::create("btn_step3_camera.png");
    cameraBtn->loadTextures("btn_step3_camera.png", "btn_step3_camera.png");
    cameraBtn->setPosition(Vec2(68, 528));
    cameraBtn->setAnchorPoint(Vec2(0,0));
         cameraBtn->setScale(0.86);
    cameraBtn->setColor(Color3B(240, 240, 240));
    cameraBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:{
            auto nextLayer=createMessageLayer();
            nextLayer->setTag(1000);
            this->addChild(nextLayer);
        }
            break;
    }
    });
    bkView->addChild(cameraBtn);
    
    auto albumBtn=Button::create("btn_step3_album.png");
    albumBtn->loadTextures("btn_step3_album.png", "btn_step3_album.png");
    albumBtn->setPosition(Vec2(68, 611));
    albumBtn->setAnchorPoint(Vec2(0,0));
      albumBtn->setScale(0.86);
    albumBtn->setColor(Color3B(240, 240, 240));
    albumBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    bkView->addChild(albumBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(180, 450));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->cocos2d::Node::setScale(0.87);
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            Director::getInstance()->popScene();
            break;
    }
    });
    bkView->addChild(deleteBtn);
    return true;
}

Layer* SelectStep3Scene::createMessageLayer(){
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
    
    auto contentV = Sprite::create("bk_step3_next.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_step3_sure.png", "btn_step3_sure.png");
    sureBtn->setPosition(Vec2(180, 347));
    sureBtn->setScale(0.87);
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(1000);
            
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    return layer;
}


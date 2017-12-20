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
#include "SelectCaseScene.hpp"
#include "RegisterScene.hpp"
#include "SelectStep2Scene.hpp"
#include "SelectStep3Scene.hpp"
#include "SelectStep4Scene.hpp"
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
    
    auto step1Btn=Button::create();
    step1Btn->loadTextures("step1.png", "step1.png");
    step1Btn->setPosition(Vec2(20, visibleSize.height-300));
    step1Btn->setAnchorPoint(Vec2(0,0));
    step1Btn->setScale(0.86);
    step1Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto step1SC=SelectCaseScene::create();
            Director::getInstance()->pushScene(step1SC);
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
            auto step2SC=SelectStep2Scene::create();
            Director::getInstance()->pushScene(step2SC);
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
            auto nextLayer=createMessageLayer();
            nextLayer->setTag(1000);
            this->addChild(nextLayer);
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
            auto step4SC=SelectStep4Scene::create();
            Director::getInstance()->pushScene(step4SC);
        }
        default:
            break;
    }
    });
    this->addChild(step4Btn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_perfect_sure.png", "btn_perfect_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width/2-135, 100));
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
    
    return true;
}

Layer* PerfectCaseScene::createMessageLayer(){
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
            auto albumLayer=createAlbumLayer();
            albumLayer->setTag(1001);
            this->addChild(albumLayer);
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    return layer;
}
Layer* PerfectCaseScene::createAlbumLayer(){
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
    
    auto bkView=Sprite::create("bk_step3.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
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
            this->removeChildByTag(1001);
        default:
            
            break;
    }
    });
    bkView->addChild(deleteBtn);
    return layer;
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
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

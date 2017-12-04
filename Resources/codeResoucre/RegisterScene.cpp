//
//  RegisterScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/11/29.
//

#include "RegisterScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "RegisterMessageScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *RegisterScene::createScene(){
    return RegisterScene::create();
}
Layer* createCaseLayer();
static void problemLoading(const char *filename){
    printf("Error while loading:%s\n",filename);
}
bool RegisterScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView = Sprite::create("bk_register.png");
    bkView->setAnchorPoint(Vec2(0,0));
    bkView->setPosition(Vec2(0,0));
    bkView->setContentSize(Size(visibleSize.width,visibleSize.height));
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
    
    
    auto caseBtn=Button::create();
    caseBtn->loadTextures("register_case.png", "register_case.png");
    caseBtn->setPosition(Vec2(20, visibleSize.height-160));
    caseBtn->setAnchorPoint(Vec2(0,1));
    caseBtn->setScale(0.86);
//    caseBtn->setScale9Enabled(true);
//    caseBtn->setContentSize(Size(601, 168));
    caseBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
        Layer *layer= createCaseLayer();
            layer->setTag(100);
        this->addChild(layer);
            break;
        }
        default:
            break;
    }
    });
    this->addChild(caseBtn);
    
    auto SQcodeBtn=Button::create();
    SQcodeBtn->loadTextures("register_SQCode.png", "register_SQCode.png");
    SQcodeBtn->setPosition(Vec2(20, visibleSize.height-350));
    SQcodeBtn->setAnchorPoint(Vec2(0,1));
    SQcodeBtn->setScale(0.86);
    SQcodeBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    this->addChild(SQcodeBtn);

    auto writingBtn=Button::create();
    writingBtn->loadTextures("register_first_use.png", "register_first_use.png");
    writingBtn->setPosition(Vec2(20, visibleSize.height-540));
    writingBtn->setAnchorPoint(Vec2(0,1));
    writingBtn->setScale(0.86);
    writingBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto messageScene=RegisterMessageScene::create();
            Director::getInstance()->pushScene(messageScene);
        }
        default:
            break;
    }
    });
    this->addChild(writingBtn);
    return true;
}

Layer* RegisterScene::createCaseLayer(){
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
    auto contentV = Sprite::create("regitser_writing.png");
    contentV->setAnchorPoint(Vec2(0,1));
    contentV->setPosition(Vec2(57,visibleSize.height-220));
    contentV->setContentSize(Size(526,300));
    layer->addChild(contentV);
    
//必须写在textfield之前才能释放textfield响应者
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_register_delete.png", "btn_register_delete.png");
    deleteBtn->setPosition(Vec2(465, 240));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(100);
        default:
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_register_sure.png", "btn_register_sure.png");
    sureBtn->setPosition(Vec2(163, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto textFieldCase = TextField::create("在此填写","Arial",40);
    textFieldCase->setMaxLength(40);
    textFieldCase->setTouchSize(Size(400, 42));
    textFieldCase->setAnchorPoint(Vec2(0.5,0));
    textFieldCase->setPosition(Vec2(264,123));
    textFieldCase->setContentSize(Size(400,42));
    textFieldCase->setTextColor(Color4B::BLACK);
    textFieldCase->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textFieldCase->addEventListener(CC_CALLBACK_2(RegisterScene::eventCallBack, this));
    contentV->addChild(textFieldCase);

    return layer;
}

void RegisterScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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

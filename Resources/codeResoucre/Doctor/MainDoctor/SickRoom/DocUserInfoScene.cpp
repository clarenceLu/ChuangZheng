//
//  DocUserInfoScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "DocUserInfoScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *DocUserInfoScene::createScene(){
    return DocUserInfoScene::create();
}
bool DocUserInfoScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_doctor_userInfo.png");
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
    
    auto headImageBtn=Button::create();
    headImageBtn->loadTextures("HelloWorld.png", "HelloWorld.png");
    headImageBtn->setPosition(Vec2(52, 830));
    headImageBtn->setAnchorPoint(Vec2(0, 0));
    headImageBtn->setScale9Enabled(true);
    headImageBtn->setContentSize(Size(141, 141));
    headImageBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *headLayer= createAlbumLayer();
            headLayer->setTag(200);
            this->addChild(headLayer);
        }
        default:
            break;
    }
    });
    bkView->addChild(headImageBtn);

    
    auto userName = Label::createWithSystemFont("用户名：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(Point(233,886));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto textFieldUser = TextField::create("抵抗力","Arial",35);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(300, 50));
    textFieldUser->setPosition(Vec2(380,886));
    textFieldUser->setAnchorPoint(Vec2(0,0));
    textFieldUser->setContentSize(Size(300,50));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldUser->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(210, 880));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.6);
    bkView->addChild(lineV);
    
    auto sex = Label::createWithSystemFont("性别：","Arial",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    sex->setPosition(Point(233,822));
    sex->setTextColor(Color4B(91, 144, 229, 255));
    sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(sex);
    
    auto textFieldSex = TextField::create("女","Arial",35);
    textFieldSex->setMaxLength(40);
    textFieldSex->setTouchSize(Size(80, 50));
    textFieldSex->setPosition(Vec2(350,822));
    textFieldSex->setAnchorPoint(Vec2(0,0));
    textFieldSex->setContentSize(Size(80,50));
    textFieldSex->setTextColor(Color4B::BLACK);
    textFieldSex->setPlaceHolderColor(Color4B::GRAY);
    textFieldSex->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldSex->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldSex);
    
    auto age = Label::createWithSystemFont("性别：","Arial",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    age->setPosition(Point(412,822));
    age->setTextColor(Color4B(91, 144, 229, 255));
    age->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(age);
    
    auto textFieldAge = TextField::create("32","Arial",35);
    textFieldAge->setMaxLength(40);
    textFieldAge->setTouchSize(Size(120, 50));
    textFieldAge->setPosition(Vec2(530,822));
    textFieldAge->setAnchorPoint(Vec2(0,0));
    textFieldAge->setContentSize(Size(120,50));
    textFieldAge->setTextColor(Color4B::BLACK);
    textFieldAge->setPlaceHolderColor(Color4B::GRAY);
    textFieldAge->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldAge->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldAge);
    
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(210, 816));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setScaleX(0.6);
    bkView->addChild(lineV2);
    
    auto textfieldName=createBasicData(bkView, Vec2(59, 758), "真实姓名：", "张牧之");
    auto textfieldNum=createBasicData(bkView, Vec2(59, 688), "病案号：", "未填写");
    auto textfieldCase=createBasicData(bkView, Vec2(59, 618), "病历号：", "未填写");
    auto textfieldSponsor=createBasicData(bkView, Vec2(59, 548), "介绍人：", "未填写");
    auto textfieldRecommend=createBasicData(bkView, Vec2(59, 478), "推荐人：", "未填写");
    auto textfieldTel1=createBasicData(bkView, Vec2(59, 408), "电话：", "未填写");
    auto textfieldTel2=createBasicData(bkView, Vec2(59, 338), "电话2：", "未填写");
    auto textfieldTel3=createBasicData(bkView, Vec2(59, 268), "电话3：", "未填写");
    return true;
}

TextField*  DocUserInfoScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
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
    textFieldUser->addEventListener(CC_CALLBACK_2(DocUserInfoScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}



//上传头像
Layer* DocUserInfoScene::createAlbumLayer(){
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
    auto contentV = Sprite::create("update_album.png");
    contentV->setAnchorPoint(Vec2(0,1));
    contentV->setPosition(Vec2(57,visibleSize.height-300));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto cameraBtn=Button::create();
    cameraBtn->setScale9Enabled(true);
    cameraBtn->setPosition(Vec2(0, 88));
    cameraBtn->setAnchorPoint(Vec2(0,0));
    cameraBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    cameraBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(cameraBtn);
    
    auto albumBtn=Button::create();
    albumBtn->setScale9Enabled(true);
    albumBtn->setPosition(Vec2(0, 168));
    albumBtn->setAnchorPoint(Vec2(0,0));
    albumBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    albumBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(albumBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(111, 15));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->cocos2d::Node::setScale(0.87);
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(200);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    
    return layer;
}

void DocUserInfoScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
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


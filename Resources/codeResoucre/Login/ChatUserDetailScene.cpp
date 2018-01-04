//
//  ChatUserDetailScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/11.
//

#include "ChatUserDetailScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SelectStep3Scene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ChatUserDetailScene::createScene(){
    return ChatUserDetailScene::create();
}
bool ChatUserDetailScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_chat_userdetail.png");
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
    
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0, 30));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 950));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 255, 255));//设置背景颜色
    createScrollDetailView(scrollView);
    bkView->addChild(scrollView);
    return true;
};

void ChatUserDetailScene::createScrollDetailView(ScrollView* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("alpha.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, 950));
    superV->addChild(bkView);
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(244, 815));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
    headBtn->ignoreContentAdaptWithSize(true);
    headBtn->setScale9Enabled(true);
    headBtn->setContentSize(Size(151, 151));
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            log("点击上传头像");
            Layer *layer= createAlbumLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
    });

    createLabel(Vec2(0, 758), "真实姓名：", "张牧之", bkView);
    createLabel(Vec2(0, 678), "病历号：", "20171112082214", bkView);
    createLabel(Vec2(0, 598), "性别：", "女", bkView);
    createLabel(Vec2(0, 518), "年龄：", "32", bkView);
    float height= createLabel(Vec2(0, 438), "自述症状：", "头后仰上身麻无敌无敌无敌无敌无敌", bkView);

    auto imageLB = Label::createWithSystemFont("影像：","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    imageLB->setPosition(Point(56,400-height));
    imageLB->setTextColor(Color4B(91,144,230, 255));
    imageLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(imageLB);
    float currentHeight=0;
    for (int i=0; i<12; i++) {
        if (i==12-1) {
            auto imageBtn1=ImageView::create("btn_chat_userImage.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 320-height+10));
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 320-height-(int)((width-154)/(visibleSize.width-154))*150+10));
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->setScale(0.87);
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    auto updateLayer=createUpdateImageLayer();
                    this->addChild(updateLayer);
                }
            });
            currentHeight=975-(320-height-(int)((width-154)/(visibleSize.width-154))*150);
        }else{
            auto imageBtn1=ImageView::create("bk_headIV.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 320-height));
                //                 log("width:%d,height:%f i的值%d,屏幕宽度%f",154+150*(i%3),320-height-(int)(width/(int)visibleSize.width)*150,i,visibleSize.width);
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 320-height-(int)((width-154)/(visibleSize.width-154))*150));
                //                log("width:%d,height:%f i的值%d,总长度:%d",154+150*(i%3),320-height-(int)((width-154)/(visibleSize.width-154))*150,i,width);
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->ignoreContentAdaptWithSize(true);
            imageBtn1->setScale9Enabled(true);
            imageBtn1->setContentSize(Size(125, 125));
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    log("点击查看照片");
                }
            });
        }
    }
    superV->setInnerContainerSize(Size(visibleSize.width, currentHeight+30));
    
    bkView->setPosition(Vec2(0, currentHeight-960));
    
}

Layer* ChatUserDetailScene::createAlbumLayer(){
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
Layer* ChatUserDetailScene::createUpdateImageLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
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
    
    
    auto bkView=Sprite::create("bk_updateImageLayer.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    layer->addChild(bkView);
    
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
    
    auto updateBtn=Button::create();
    updateBtn->loadTextures("btn_updateImage.png", "btn_updateImage.png");
    updateBtn->setPosition(Vec2(visibleSize.width/2, 486));
    updateBtn->setScale(0.87);
    updateBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto step3SC=SelectStep3Scene::create();
            Director::getInstance()->pushScene(step3SC);
        }
    
        default:
            break;
    }
    });
    bkView->addChild(updateBtn);
    
    return layer;
    
}

float ChatUserDetailScene::createLabel(Vec2 point,string name1,string name2,Sprite* superV){
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
    
    return height;
}

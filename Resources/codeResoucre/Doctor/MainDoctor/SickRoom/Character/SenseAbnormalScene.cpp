//
//  SenseAbnormalScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/22.
//

#include "SenseAbnormalScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

Scene *SenseAbnormalScene::createScene(){
    return SenseAbnormalScene::create();
}
bool SenseAbnormalScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_SpineTenderness.png");
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
    
    imageV=Sprite::create("example.png");
    imageV->setPosition(Vec2(20, 20));
    imageV->setColor(Color3B::RED);
    imageV->setContentSize(Size(visibleSize.width-40, visibleSize.height-200));
    imageV->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(imageV);
    
    
//    auto  testBtn=Button::create();
//    testBtn->loadTextures("btn_register.png", "bg_input_passwd.png");
//    testBtn->setPosition(Vec2(20, 100));
//    testBtn->setAnchorPoint(Vec2(0, 0));
//    testBtn->setScale(0.87);
//    testBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
//        case ui::Widget::TouchEventType::BEGAN:
//            break;
//        case ui::Widget::TouchEventType::ENDED:
//
//        default:
//            break;
//    }
//    });
//    imageV->addChild(testBtn);
//
    

    
    mscale=1.0;
    
    //添加触控监听
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_2(SenseAbnormalScene::onTouchesBegan,this);
    listen->onTouchesMoved = CC_CALLBACK_2(SenseAbnormalScene::onTouchesMoved,this);
    listen->onTouchesEnded = CC_CALLBACK_2(SenseAbnormalScene::onTouchesEnded,this);
    listen->onTouchesCancelled = CC_CALLBACK_2(SenseAbnormalScene::onTouchesCancelled,this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
    
    return true;
}



//触摸事件开始，手指按下时
void SenseAbnormalScene::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches.at(0);
    //右指，从左往右的时候为扩大，从右往左的时候为缩放
    auto pos1 = touch->getLocation();
    auto pos2 = touch->getLocationInView();
    auto pos3 = Director::getInstance()->convertToUI(pos2);
    if (touches.size()>1) {
        auto touch2=touches.at(1);
        //左指，从左往右为缩放，从右往左为扩大
        auto pos4 = touch2->getLocation();
        auto pos5 = touch2->getLocationInView();
        auto pos6 = Director::getInstance()->convertToUI(pos5);
    distance=sqrt((pos6.x-pos3.x)*(pos6.x-pos3.x)+(pos6.y-pos3.y)*(pos6.y-pos3.y));//计算两个触摸点距离
    deltax = (pos3.x + pos6.x)/2 - this->imageV->getPositionX();     //得到两个触摸点中点和精灵锚点的差值
    deltay = (pos3.y + pos6.y)/2 - this->imageV->getPositionY();
    }else if (touches.size()==1){
        changePoint=pos3-imageV->getPosition();
        log("pos3:%f,%f  ;  imageV:%f,%f",pos3.x,pos3.y,imageV->getPosition().x,imageV->getPosition().y);
    }
    
}
//触摸移动事件，也就是手指在屏幕滑动的过程
void SenseAbnormalScene::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches.at(0);
    //右指，从左往右的时候为扩大，从右往左的时候为缩放
    auto pos1 = touch->getLocation();
    auto pos2 = touch->getLocationInView();
    auto pos3 = Director::getInstance()->convertToUI(pos2);
    log("pos1 x: %f, y: %f",pos1.x,pos1.y);
    log("pos2 x: %f, y: %f",pos2.x,pos2.y);
    log("pos3 x: %f, y: %f",pos3.x,pos3.y);
    log("touch size %ld",touches.size());
    if (touches.size()>1) {
        auto touch2=touches.at(1);
        //左指，从左往右为缩放，从右往左为扩大
        auto pos4 = touch2->getLocation();
        auto pos5 = touch2->getLocationInView();
        auto pos6 = Director::getInstance()->convertToUI(pos5);
        log("pos4 x: %f, y: %f",pos4.x,pos4.y);
        log("pos5 x: %f, y: %f",pos5.x,pos5.y);
        log("pos6 x: %f, y: %f",pos6.x,pos6.y);
        
//如果是双指移动
        double mdistance = sqrt((pos3.x-pos6.x)*(pos3.x-pos6.x)+(pos3.y-pos6.y)*(pos3.y-pos6.y));
        mscale = mdistance/distance * mscale;                      //   新的距离 / 老的距离  * 原来的缩放比例，即为新的缩放比例
        distance = mdistance;
        this->imageV->setScale(mscale);

        double x = (pos6.x+pos3.x)/2 - deltax;      //计算两触点中点与精灵锚点的差值
        double y = (pos6.y+pos3.y)/2 - deltay;
         imageV->setPosition(Vec2(x,y));                        //保持两触点中点与精灵锚点的差值不变
        deltax = (pos3.x+ pos6.x)/2 - imageV->getPositionX();       //计算新的偏移量
        deltay = (pos6.y + pos3.y)/2 - imageV->getPositionY();
    }else if (touches.size()==1){ //坐标转换
        double x = pos3.x - changePoint.x;
        double y = pos3.y- changePoint.y;
            imageV->setPosition(Vec2(x, y));                    //直接移动精灵x
    }
    
}
//触摸事件结束，也就是手指松开时
void SenseAbnormalScene::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    log("TouchTest onTouchesEnded");
}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断
void SenseAbnormalScene::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    log("TouchTest onTouchesCancelled");
}




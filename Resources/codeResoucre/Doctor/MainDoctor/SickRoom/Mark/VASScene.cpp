//
//  VASScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#include "VASScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *VASScene::createScene(){
    return VASScene::create();
}
bool VASScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_VAS.png");
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
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_group_leader_sure.png", "btn_group_leader_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("VAS sure");
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    auto rodSp=Sprite::create("VAS_rod.png");
    rodSp->setPosition(Vec2(35, 803));
    rodSp->setAnchorPoint(Vec2(0, 0));
    rodSp->setScale(0.87);
    bkView->addChild(rodSp);
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width, 680));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(0,100));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(VASScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(VASScene::selectedItemEventScrollView, this));
    bkView->addChild(lv);
   
    count=1;
    auto layout=createPainView(Vec2(0, 0), count);
      lv->insertCustomItem(layout,count-1);
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_VAS_add.png", "btn_VAS_add.png");
    addBtn->setPosition(Vec2(visibleSize.width/2, 30));
    addBtn->setAnchorPoint(Vec2(0.5, 0));
    addBtn->setScale(0.87);
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            count++;
           auto layout=createPainView(Vec2(0, 0), count);
            lv->pushBackCustomItem(layout);
        }
            
        default:
            break;
    }
    });
    this->addChild(addBtn);
    
    
    return true;
    
}
cocos2d::ui::Layout * VASScene::createPainView(Vec2 point,int i){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, 80));
    
    char str[10];
    sprintf(str,"部位%d",i);
    string title=str;
    auto partLB = Label::createWithSystemFont(title,"Arial",38,Size(110,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    partLB->setPosition(Point(50,10));
    partLB->setTextColor(Color4B(0, 0, 0, 220));
    partLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(partLB);
    
    auto partSp=Sprite::create("VAS_rect_long.png");
    partSp->setPosition(Vec2(160, 10));
    partSp->setAnchorPoint(Vec2(0, 0));
    partSp->setScale(0.87);
    layout->addChild(partSp);
    
    partField=TextField::create("填写部位","Arial",38);
    partField->setMaxLength(60);
    partField->setTouchSize(partSp->getContentSize()*0.87);
    partField->setAnchorPoint(Vec2(0,0));
    partField->setPosition(Vec2(10,10));
    partField->setContentSize(Size(partSp->getContentSize()*0.87));
    partField->setPlaceHolderColor(Color4B(91, 144, 229, 255));
    partField->setTextColor(Color4B(0, 0, 0, 220));
    partField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    partField->addEventListener(CC_CALLBACK_2(VASScene::eventCallBack, this));
    partSp->addChild(partField);
    
    auto painLB = Label::createWithSystemFont("疼痛程度","Arial",38,Size(160,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    painLB->setPosition(Point(340,10));
    painLB->setTextColor(Color4B(0, 0, 0, 220));
    painLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(painLB);
    
    auto painSp=Sprite::create("VAS_rect_short.png");
    painSp->setPosition(Vec2(510, 10));
    painSp->setAnchorPoint(Vec2(0, 0));
    painSp->setScale(0.87);
    layout->addChild(painSp);
    
    painField=TextField::create("数字","Arial",38);
    painField->setMaxLength(60);
    painField->setTouchSize(painSp->getContentSize()*0.87);
    painField->setAnchorPoint(Vec2(0,0));
    painField->setPosition(Vec2(10,10));
    painField->setContentSize(Size(painSp->getContentSize()*0.87));
    painField->setPlaceHolderColor(Color4B(91, 144, 229, 255));
    painField->setTextColor(Color4B(0, 0, 0, 220));
    painField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    painField->addEventListener(CC_CALLBACK_2(VASScene::eventCallBack, this));
    painSp->addChild(painField);
    return layout;
    
}



void VASScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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




void VASScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            int index=(int)listView->getCurSelectedIndex();
            break;
        }
        default:
            break;
    }
}
void VASScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
    switch (type) {
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM://滑动到底部
            CCLOG("SCROLL_TO_BOTTOM");
            break;
        case ui::ScrollView::EventType::SCROLL_TO_TOP://滑动到头部
            CCLOG("SCROLL_TO_TOP");
            break;
        default:
            break;
    }
}


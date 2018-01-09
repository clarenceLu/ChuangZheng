//
//  MuscleStrengthScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "MuscleStrengthScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NeckJOAScene.hpp"
#include "WaistJOAScene.hpp"
#include "ASIAScene.hpp"
#include "VASScene.hpp"
#include "NDIScene.hpp"
#include "OPLLScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MuscleStrengthScene::createScene(){
    return MuscleStrengthScene::create();
}
bool MuscleStrengthScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_mark.png");
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
    
    ListView* lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-200));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,50));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MuscleStrengthScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(MuscleStrengthScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layer1 = createMessageLayout(0,"握力","0");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(1,"屈腕","II");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(2,"伸腕","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(3,"屈肘","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(4,"伸肘","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createMessageLayout(5,"张臂","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createMessageLayout(6,"收臂","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createMessageLayout(7,"屈踇","");
    lv->insertCustomItem(layer8,7);
    auto layer9 = createMessageLayout(8,"伸踇","");
    lv->insertCustomItem(layer9,8);
    auto layer10 = createMessageLayout(9,"跖屈","");
    lv->insertCustomItem(layer10,9);
    auto layer11 = createMessageLayout(10,"背屈","");
    lv->insertCustomItem(layer11,10);
    auto layer12 = createMessageLayout(11,"屈膝","");
    lv->insertCustomItem(layer12,11);
    auto layer13 = createMessageLayout(12,"伸膝","");
    lv->insertCustomItem(layer13,12);
    auto layer14 = createMessageLayout(13,"屈髋","");
    lv->insertCustomItem(layer14,13);
    auto layer15 = createMessageLayout(14,"伸髋","");
    lv->insertCustomItem(layer15,14);
    auto layer16 = createMessageLayout(15,"分腿","");
    lv->insertCustomItem(layer16,15);
    auto layer17 = createMessageLayout(16,"并腿","");
    lv->insertCustomItem(layer17,16);
    
    return true;
    
}

Layout *MuscleStrengthScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",38,Size(visibleSize.width-300,0),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
        contentLB->setPosition(Point(visibleSize.width-110,15));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(1, 0));
        contentLB->setTag(i);
        labelDic.insert(i, contentLB);
        layout->addChild(contentLB);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(30, 0));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-100, 2.0));
    layout->addChild(lineV);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+70));
    
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, height+10));
    layout->addChild(judgeBtn);
    
    
    return layout;
}


Layer* MuscleStrengthScene::createSelectLayer(){
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
    
    auto contentV = Sprite::create("bk_strength_select.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,244));
    contentV->setContentSize(Size(508,681));
    layer->addChild(contentV);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(114, 15));
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
    
    auto fiveBtn=Button::create();
    fiveBtn->loadTextures("alpha.png", "alpha.png");
    fiveBtn->setTitleText("V");
    fiveBtn->setTitleColor(Color3B(40, 40, 40));
    fiveBtn->setTitleFontSize(45);
    fiveBtn->setPosition(Vec2(0, 83));
    fiveBtn->setAnchorPoint(Vec2(0,0));
    fiveBtn->setScale9Enabled(true);
    fiveBtn->setContentSize(Size(508, 83));
    fiveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
        
         Label* lb=labelDic.at(selectIndex);
            lb->setString("V");
             this->removeChildByTag(200);
        }
        default:
            break;
    }
    });
    contentV->addChild(fiveBtn);
    
    createSelectItem("IV", 83*2, contentV);
    createSelectItem("III", 83*3, contentV);
    createSelectItem("II", 83*4, contentV);
    createSelectItem("I", 83*5, contentV);
    createSelectItem("0", 83*6, contentV);
    
    return layer;
}

void MuscleStrengthScene::createSelectItem(string title,float Y,Sprite* contentV){
    auto fourBtn=Button::create();
    fourBtn->loadTextures("alpha.png", "alpha.png");
    fourBtn->setTitleText(title);
    fourBtn->setTitleColor(Color3B(40, 40, 40));
    fourBtn->setTitleFontSize(45);
    fourBtn->setPosition(Vec2(0, Y));
    fourBtn->setAnchorPoint(Vec2(0,0));
    fourBtn->setScale9Enabled(true);
    fourBtn->setContentSize(Size(508, 83));
    fourBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Button *btn=(Button *)sender;
            Label* lb=labelDic.at(selectIndex);
//            log("%d,%s",lb->getTag(),btn->getTitleText().c_str());
            lb->setString(btn->getTitleText());
            this->removeChildByTag(200);
        }
        default:
            break;
    }
    });
    contentV->addChild(fourBtn);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, Y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(508, 1.5));
    contentV->addChild(lineV);
    
}


void MuscleStrengthScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            int index=listView->getCurSelectedIndex();
            selectIndex=index;
          Layer *layer=createSelectLayer();
            layer->setTag(200);
            this->addChild(layer);
            break;
        }
        default:
            break;
    }
}
void MuscleStrengthScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

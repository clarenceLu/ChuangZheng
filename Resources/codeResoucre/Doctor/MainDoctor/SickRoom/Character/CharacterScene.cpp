//
//  CharacterScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "CharacterScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "AppearanceAbnormalScene.hpp"
#include "SpineTendernessScene.hpp"
#include "ActionAbnormalScene.hpp"
#include "SenseScene.hpp"
#include "DystoniaScene.hpp"
#include "MuscleStrengthScene.hpp"
#include "ReflectAbnormalScene.hpp"
#include "ReflectScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *CharacterScene::createScene(){
    return CharacterScene::create();
}
bool CharacterScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_character.png");
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
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-190));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,40));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(CharacterScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(CharacterScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layer1 = createMessageLayout(0,"外观异常","双手,双脚,双前臂,双脚,双大腿");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(0,"行动异常","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(0,"棘突压痛","上肢发达  双臂麻木   双大腿抽筋    左前方脊椎疼痛  脑袋晕");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(0,"感觉异常","上肢发达  双臂麻木   双大腿抽筋");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(0,"肌张力异常","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createMessageLayout(0,"肌力异常","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createMessageLayout(0,"生理反射异常","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createMessageLayout(0,"病理反射","");
    lv->insertCustomItem(layer8,7);
    
    return true;
    
}

Layout *CharacterScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-200,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        height=contentLB->getContentSize().height+10;
        contentLB->setPosition(Point(37,10));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        layout->addChild(contentLB);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height+10));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(30, 0));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-100, 1.5));
    layout->addChild(lineV);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+80));
    
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, height+20));
    layout->addChild(judgeBtn);
    
    
    return layout;
}


void CharacterScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            long index=listView->getCurSelectedIndex();
            if (index==0) {
                auto appearanceSC=AppearanceAbnormalScene::createScene();
                Director::getInstance()->pushScene(appearanceSC);
            }else if(index==2){
                auto spineSC=SpineTendernessScene::createScene();
                Director::getInstance()->pushScene(spineSC);
            }else if(index==1){
                auto actionSC=ActionAbnormalScene::createScene();
                Director::getInstance()->pushScene(actionSC);
            }else if(index==3){
                auto senseSC=SenseScene::createScene();
                Director::getInstance()->pushScene(senseSC);
            }else if(index==4){
                auto dystonialSC=DystoniaScene::createScene();
                Director::getInstance()->pushScene(dystonialSC);
            }else if(index==5){
                auto SC=MuscleStrengthScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==6){
                auto SC=ReflectAbnormalScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==7){
                auto SC=ReflectScene::createScene();
                Director::getInstance()->pushScene(SC);
            }
            
            break;
        }
        default:
            break;
    }
}
void CharacterScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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


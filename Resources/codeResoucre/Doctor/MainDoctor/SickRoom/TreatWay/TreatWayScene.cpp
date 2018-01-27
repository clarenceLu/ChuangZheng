//
//  TreatWayScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/11.
//

#include "TreatWayScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "MainScene.hpp"
#include <math.h>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *TreatWayScene::createScene(){
    return TreatWayScene::create();
}
bool TreatWayScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_recoverway.png");
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
    sureBtn->loadTextures("btn_step4_sure.png", "btn_step4_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-80, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
          Director::getInstance()->popToSceneStackLevel(4);
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width, 400));
     lv->setInnerContainerSize(Size(visibleSize.width, 400));
    lv->setAnchorPoint(Point(0,1));
    lv->setPosition(Point(0,visibleSize.height-150));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(TreatWayScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(TreatWayScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    Layout *layout1=createBlueView("C0-C2", 0);
    lv->insertCustomItem(layout1, 0);
    Layout *layout2=createBlueView("C3-C7", 1);
     lv->insertCustomItem(layout2, 1);
    Layout *layout3=createBlueView("T1-T6", 2);
     lv->insertCustomItem(layout3, 2);
    Layout *layout4=createBlueView("T7-T12", 3);
    lv->insertCustomItem(layout4, 3);
    Layout *layout5=createBlueView("L1-S1", 4);
    lv->insertCustomItem(layout5, 4);
    
    
    
    return true;
    
}

cocos2d::ui::Layout *TreatWayScene::createBlueView(string name,int tag){
     Size visibleSize=Director::getInstance()->getVisibleSize();
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    
    
    auto whiteView=createWhiteView(0, tag*3);
    layout->addChild(whiteView);
    
    
    layout->setContentSize(Size(visibleSize.width, 80));
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(20, 70));
    blueV->setAnchorPoint(Vec2(0, 1));
    blueV->setContentSize(Size(visibleSize.width-40, 60));
    blueV->setTag(tag);
    layout->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(400,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_appearance_down.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_appearance_up.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(TreatWayScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(Vec2(blueV->getContentSize().width-60,20));  //设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setTag(100+tag);
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    blueV->addChild(box);
    return layout;
}

Sprite *TreatWayScene::createWhiteView(int type,int tag){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    float currentHeight=0;
    switch (tag/3)
    {
        case 0:currentHeight=740;   break;
        case 1:currentHeight=860;   break;
        case 2:currentHeight=740;   break;
        case 3:currentHeight=740;   break;
        case 4:currentHeight=860;   break;
        default:
            break;
    }
    auto whiteView=Sprite::create("alpha.png");
    whiteView->setPosition(Vec2(0, 0));
    whiteView->setAnchorPoint(Vec2(0, 0));
    whiteView->setContentSize(Size(visibleSize.width, currentHeight));
    whiteView->setVisible(false);
    whiteViewDic.insert(tag/3, whiteView);
    createSelectBox(Vec2(110, currentHeight-50), "前路", tag, 70, whiteView);
    createSelectBox(Vec2(260, currentHeight-50), "后路", tag+1, 70, whiteView);
    createSelectBox(Vec2(410, currentHeight-50), "微创", tag+2, 70, whiteView);
    
    
//加入选择题的数据
    switch (tag/3)
    {
        case 0:{
        multLayer0 = LayerMultiplex::create();
      whiteView->addChild(multLayer0, 0);
    for (int i=0; i<3; i++) {
        auto layer = LayerColor::create(Color4B(246, 247, 248, 255));
        layer->setContentSize(Size(visibleSize.width-40, currentHeight-50));
        layer->setPosition(Point(20, 0));
        layer->setAnchorPoint(Vec2(0, 0));
        multLayer0->addLayer(layer);
        if (i!=2) {
      float height=createResection(i, tag/3, layer);
            createImplant(i, tag/3, layer, height-10);
        }else{createMiniOperationView(i, tag/3, layer);}
    }multLayer0->switchTo(0);
            break;
         }
        case 1:{
            multLayer1 = LayerMultiplex::create();
            whiteView->addChild(multLayer1, 0);
            for (int i=0; i<3; i++) {
                auto layer = LayerColor::create(Color4B(246, 247, 248, 255));
                layer->setContentSize(Size(visibleSize.width-40, currentHeight-50));
                layer->setPosition(Point(20, 0));
                layer->setAnchorPoint(Vec2(0, 0));
                multLayer1->addLayer(layer);
                if (i!=2) {
                    float height=createResection(i, tag/3, layer);
                    createImplant(i, tag/3, layer, height-10);
                }else{createMiniOperationView(i, tag/3, layer);}
            }multLayer1->switchTo(0);
            break;
        }
        case 2:{
            multLayer2 = LayerMultiplex::create();
            whiteView->addChild(multLayer2, 0);
            for (int i=0; i<3; i++) {
                auto layer = LayerColor::create(Color4B(246, 247, 248, 255));
                layer->setContentSize(Size(visibleSize.width-40, currentHeight-50));
                layer->setPosition(Point(20, 0));
                layer->setAnchorPoint(Vec2(0, 0));
                multLayer2->addLayer(layer);
                if (i!=2) {
                    float height=createResection(i, tag/3, layer);
                    createImplant(i, tag/3, layer, height-10);
                }else{createMiniOperationView(i, tag/3, layer);}
            }multLayer2->switchTo(0);
            break;
        }
        case 3:{
            multLayer3 = LayerMultiplex::create();
            whiteView->addChild(multLayer3, 0);
            for (int i=0; i<3; i++) {
                auto layer = LayerColor::create(Color4B(246, 247, 248, 255));
                layer->setContentSize(Size(visibleSize.width-40, currentHeight-50));
                layer->setPosition(Point(20, 0));
                layer->setAnchorPoint(Vec2(0, 0));
                multLayer3->addLayer(layer);
                if (i!=2) {//排除了微创这个情况
                    float height=createResection(i, tag/3, layer);
                    createImplant(i, tag/3, layer, height-10);
                }else{createMiniOperationView(i, tag/3, layer);}
            }multLayer3->switchTo(0);
            break;
        }
        case 4:{
            multLayer4 = LayerMultiplex::create();
            whiteView->addChild(multLayer4, 0);
            for (int i=0; i<3; i++) {
                auto layer = LayerColor::create(Color4B(246, 247, 248, 255));
                layer->setContentSize(Size(visibleSize.width-40, currentHeight-50));
                layer->setPosition(Point(20, 0));
                layer->setAnchorPoint(Vec2(0, 0));
                multLayer4->addLayer(layer);
                if (i!=2) {//排除了微创这个情况
                    float height=createResection(i, tag/3, layer);
                    createImplant(i, tag/3, layer, height-10);
                }else{createMiniOperationView(i, tag/3, layer);}
            }multLayer4->switchTo(0);
            break;
        }
        default:
            break;
    }
    
    return whiteView;
}
//切除
float TreatWayScene::createResection(int type,int tag,Layer *bkView){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto contentSize=bkView->getContentSize();
    if (tag==0) {
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*3));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "椎间盘C2/3", 1005, 200, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-280, 10), "齿状突", 1004, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "C2", 1003, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 70), "C1", 1002, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 70), "枕骨大孔", 1001, 160, whiteV);
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*3));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "C2椎板", 2003, 200, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-280, 10), "C1后弓", 2002, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "枕骨大孔", 2001, 150, whiteV);
        }
    }else if (tag==1){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*5));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
//C2/3  C3/4  C4/5  C5/6  C6/7  C7/T1
            auto userName = Label::createWithSystemFont("锥间盘","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,60));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "C7/T1", 1022, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 10), "C6/7", 1021, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 10), "C5/6", 1020, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "C4/5", 1019, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 70), "C3/4", 1018, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 70), "C2/3", 1017, 120, whiteV);
            auto title = Label::createWithSystemFont("锥体","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,180));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "C7", 1016, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "C6", 1015, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 190), "C5", 1014, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 190), "C4", 1013, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 190), "C3", 1012, 70, whiteV);
            
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*4));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //C2/3  C3/4  C4/5  C5/6  C6/7  C7/T1
            auto userName = Label::createWithSystemFont("半椎板","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,0));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "左", 2017, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 10), "右", 2016, 120, whiteV);
            auto title = Label::createWithSystemFont("锥板","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,120));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "C7", 2015, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 70), "C6", 2014, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "C5", 2013, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "C4", 2012, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "C3", 2011, 70, whiteV);
        }
    }else if(tag==2){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*5));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //C7/T1  T1/2  T2/3  T3/4  T4/5  T5/6  T6/7
            auto userName = Label::createWithSystemFont("锥间盘","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,60));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "T6/7", 1041, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 10), "T5/6", 1040, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 10), "T4/5", 1039, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "T3/4", 1038, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 70), "T2/3", 1037, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 70), "T1/2", 1036, 120, whiteV);
            auto title = Label::createWithSystemFont("锥体","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,180));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
//T1  T2  T3  T4  T5  T6
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "T5", 1035, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "T4", 1034, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "T1", 1033, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 190), "T3", 1032, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 190), "T2", 1031, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 190), "T1", 1030, 70, whiteV);
            
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*4));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //C2/3  C3/4  C4/5  C5/6  C6/7  C7/T1
            auto userName = Label::createWithSystemFont("半椎板","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,0));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "左", 2017, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 10), "右", 2016, 120, whiteV);
            auto title = Label::createWithSystemFont("锥板","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,120));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            //T1  T2  T3  T4  T5  T6  T7
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "T7", 2028, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 70), "T6", 2027, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 70), "T5", 2026, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-480, 70), "T4", 2025, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "T3", 2024, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "T2", 2023, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "T1", 2022, 70, whiteV);
        }
    }else if(tag==3){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*5));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //T6/7  T7/8  T8/9  T9/10  T10/T11  T11/12  T12/L1
            auto userName = Label::createWithSystemFont("锥间盘","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,60));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "T12/L1", 1058, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 10), "T11/12", 1057, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 10), "T10/T11", 1056, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "T9/10", 1055, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 70), "T8/9", 1054, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 70), "T7/8", 1053, 120, whiteV);
            auto title = Label::createWithSystemFont("锥体","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,180));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            //T7  T8  T9  T10  T11  T12
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "T12", 1052, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "T11", 1051, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "T10", 1050, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 190), "T9", 1049, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 190), "T8", 1048, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 190), "T7", 1047, 70, whiteV);
            
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*4));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            auto userName = Label::createWithSystemFont("半椎板","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,0));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "左", 2017, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 10), "右", 2016, 120, whiteV);
            auto title = Label::createWithSystemFont("锥板","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,120));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            //T7  T8  T9  T10  T11  T12
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "T12", 2028, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 70), "T11", 2027, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 70), "T10", 2026, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "T9", 2025, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "T8", 2024, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "T7", 2023, 70, whiteV);
        }
    }else if(tag==4){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*5));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //T12/L1  L1/2  L2/3  L3/4  L4/5  L5/S1
            auto userName = Label::createWithSystemFont("锥间盘","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,60));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "L5/S1", 1058, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 10), "L4/5", 1057, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 10), "T10/T11", 1056, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "L3/4", 1055, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 70), "L2/3", 1054, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 70), "L1/2", 1053, 120, whiteV);
            auto title = Label::createWithSystemFont("锥体","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,180));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            //L1  L2  L3  L4  L5 S1
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "S1", 1052, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "L5", 1051, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "L4", 1050, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 190), "L3", 1049, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 190), "L2", 1048, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 190), "L1", 1047, 70, whiteV);
            
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, contentSize.height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*6));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            auto userName = Label::createWithSystemFont("半椎板","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            userName->setPosition(Vec2(20,0));
            userName->setTextColor(Color4B(0,0,0, 255/3*2));
            userName->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(userName);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "左", 2017, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 10), "右", 2016, 120, whiteV);
            auto title = Label::createWithSystemFont("锥板","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title->setPosition(Vec2(20,120));
            title->setTextColor(Color4B(0,0,0, 255/3*2));
            title->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title);
            //T12  L1  L2  L3  L4  L5 S1
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "S1", 2028, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 70), "L5", 2027, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 70), "L4", 2026, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-480, 70), "L3", 2025, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 130), "L2", 2024, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 130), "L1", 2023, 70, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-340, 130), "T12", 2023, 70, whiteV);
            auto title2 = Label::createWithSystemFont("锥间盘","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
            title2->setPosition(Vec2(20,240));
            title2->setTextColor(Color4B(0,0,0, 255/3*2));
            title2->setAnchorPoint(Vec2(0, 0));
            whiteV->addChild(title2);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 190), "L5/S1", 1058, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 190), "L4/5", 1057, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 190), "T10/T11", 1056, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 250), "L3/4", 1055, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-210, 250), "L2/3", 1054, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-360, 250), "L1/2", 1053, 120, whiteV);
            
        }
    }
    
    auto greenV=Sprite::create("recover_rect_green.png");
    greenV->setPosition(Vec2(10, contentSize.height-10));
    greenV->setAnchorPoint(Vec2(0, 1));
    greenV->setContentSize(Size(contentSize.width-20, 60));
    greenV->setTag(tag);
    bkView->addChild(greenV);
    auto userName = Label::createWithSystemFont("切除","Arial",35,Size(400,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    greenV->addChild(userName);
    if (tag==0) {
    return  contentSize.height-10-60*3;
    }else if (tag==1||tag==2||tag==3){
        if (type==0) {
        return contentSize.height-10-60*5;}
        else if(type==1){
            return contentSize.height-10-60*4;}
    }else if (tag==4){
        if (type==0) {
            return contentSize.height-10-60*5;}
        else if(type==1){
            return contentSize.height-10-60*6;}
    }
    
    
    return 0;
}
//植入
void TreatWayScene::createImplant(int type,int tag,Layer *bkView,float height){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto contentSize=bkView->getContentSize();
    if (tag==0) {
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*7));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
//            齿状突螺钉；Cage，人工椎间盘，Zero-P，前路钢板；前路可吸收板
            createOtherSelectBox(Vec2(20, 310), "齿状突螺钉", 1006, whiteV);
            createOtherSelectBox(Vec2(20, 250), "Cage", 1007, whiteV);
            createOtherSelectBox(Vec2(20, 190), "人工椎间盘", 1008, whiteV);
            createOtherSelectBox(Vec2(20, 130), "Zero-P", 1009, whiteV);
            createOtherSelectBox(Vec2(20, 70), "前路钢板", 1010, whiteV);
            createOtherSelectBox(Vec2(20, 10), "前路可吸收板", 1011, whiteV);
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*8));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //            枕骨钢板+螺钉  C1侧块螺钉  C2椎弓根螺钉  钛缆  经关节螺钉  椎板钩  椎板螺钉
            createOtherSelectBox(Vec2(20, 370), "枕骨钢板+螺钉", 2004, whiteV);
            createOtherSelectBox(Vec2(20, 310), "C1侧块螺钉", 2005, whiteV);
            createOtherSelectBox(Vec2(20, 250), "C2椎弓根螺钉", 2006, whiteV);
            createOtherSelectBox(Vec2(20, 190), "钛缆", 2007, whiteV);
            createOtherSelectBox(Vec2(20, 130), "经关节螺钉", 2008, whiteV);
            createOtherSelectBox(Vec2(20, 70), "椎板钩", 2009, whiteV);
            createOtherSelectBox(Vec2(20, 10), "椎板螺钉", 2010, whiteV);
        }
    }  else if (tag==1) {
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*8));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //            Cage  人工椎间盘  Zero-P  MESH  髂骨块   前路钢板  前路可吸收板
            createOtherSelectBox(Vec2(20, 370), "Cage", 1023, whiteV);
            createOtherSelectBox(Vec2(20, 310), "人工椎间盘", 1024, whiteV);
            createOtherSelectBox(Vec2(20, 250), "Zero-P", 1025, whiteV);
            createOtherSelectBox(Vec2(20, 190), "MESH", 1026, whiteV);
            createOtherSelectBox(Vec2(20, 130), "髂骨块", 1027, whiteV);
            createOtherSelectBox(Vec2(20, 70), "前路钢板", 1028, whiteV);
            createOtherSelectBox(Vec2(20, 10), "前路可吸收板", 1029, whiteV);
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*5));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //           侧块螺钉  成型钢板  横连接  椎板钩
            createOtherSelectBox(Vec2(20, 190), "侧块螺钉", 2018, whiteV);
            createOtherSelectBox(Vec2(20, 130), "成型钢板", 2019, whiteV);
            createOtherSelectBox(Vec2(20, 70), "横连接", 2020, whiteV);
            createOtherSelectBox(Vec2(20, 10), "椎板钩", 2021, whiteV);
        }
    }else if(tag==2){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*6));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //            Cage   MESH 髂骨块   前路钢板  前路可吸收板
            createOtherSelectBox(Vec2(20, 250), "Cage", 1042, whiteV);
            createOtherSelectBox(Vec2(20, 190), "MESH", 1043, whiteV);
            createOtherSelectBox(Vec2(20, 130), "髂骨块", 1044, whiteV);
            createOtherSelectBox(Vec2(20, 70), "前路钢板", 1045, whiteV);
            createOtherSelectBox(Vec2(20, 10), "前路可吸收板", 1046, whiteV);
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*4));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //           椎弓根螺钉  横连接  椎板钩
            createOtherSelectBox(Vec2(20, 130), "成型钢板", 2029, whiteV);
            createOtherSelectBox(Vec2(20, 70), "横连接", 2030, whiteV);
            createOtherSelectBox(Vec2(20, 10), "椎板钩", 2031, whiteV);
        }
    }else if(tag==3){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*6));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //            Cage   MESH 髂骨块   前路钢板  前路可吸收板
            createOtherSelectBox(Vec2(20, 250), "Cage", 1042, whiteV);
            createOtherSelectBox(Vec2(20, 190), "MESH", 1043, whiteV);
            createOtherSelectBox(Vec2(20, 130), "髂骨块", 1044, whiteV);
            createOtherSelectBox(Vec2(20, 70), "前路钢板", 1045, whiteV);
            createOtherSelectBox(Vec2(20, 10), "前路可吸收板", 1046, whiteV);
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*4));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //           椎弓根螺钉  横连接  椎板钩
            createOtherSelectBox(Vec2(20, 130), "成型钢板", 2029, whiteV);
            createOtherSelectBox(Vec2(20, 70), "横连接", 2030, whiteV);
            createOtherSelectBox(Vec2(20, 10), "椎板钩", 2031, whiteV);
        }
    }else if(tag==4){
        if (type==0) {
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*7));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //            Cage   MESH 人工椎间盘  髂骨块 前路钢板  前路可吸收板
            createOtherSelectBox(Vec2(20, 310), "Cage", 1042, whiteV);
            createOtherSelectBox(Vec2(20, 250), "MESH", 1043, whiteV);
            createOtherSelectBox(Vec2(20, 190), "人工椎间盘", 1043, whiteV);
            createOtherSelectBox(Vec2(20, 130), "髂骨块", 1044, whiteV);
            createOtherSelectBox(Vec2(20, 70), "前路钢板", 1045, whiteV);
            createOtherSelectBox(Vec2(20, 10), "前路可吸收板", 1046, whiteV);
        }else if(type==1){
            auto whiteV=Sprite::create("bk_impress_rect_white.png");
            whiteV->setPosition(Vec2(10, height-10));
            whiteV->setAnchorPoint(Vec2(0, 1));
            whiteV->setContentSize(Size(contentSize.width-20, 60*5));
            whiteV->setTag(tag);
            bkView->addChild(whiteV);
            //           椎弓根螺钉  横连接  椎板钩  Cage
            createOtherSelectBox(Vec2(20, 190), "椎弓根螺钉", 2029, whiteV);
            createOtherSelectBox(Vec2(20, 130), "横连接", 2029, whiteV);
            createOtherSelectBox(Vec2(20, 70), "椎板钩", 2030, whiteV);
            createOtherSelectBox(Vec2(20, 10), "Cage", 2031, whiteV);
        }
    }
    
    auto greenV=Sprite::create("recover_rect_green.png");
    greenV->setPosition(Vec2(10, height-10));
    greenV->setAnchorPoint(Vec2(0, 1));
    greenV->setContentSize(Size(contentSize.width-20, 60));
    greenV->setTag(tag);
    bkView->addChild(greenV);
    auto userName = Label::createWithSystemFont("植入","Arial",35,Size(400,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    greenV->addChild(userName);
}



//微创
void TreatWayScene::createMiniOperationView(int type,int tag,Layer *bkView){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto contentSize=bkView->getContentSize();
//经皮
    auto whiteV=Sprite::create("bk_impress_rect_white.png");
    whiteV->setPosition(Vec2(10, contentSize.height-10));
    whiteV->setAnchorPoint(Vec2(0, 1));
    whiteV->setContentSize(Size(contentSize.width-20, 60*3));
    whiteV->setTag(tag);
    bkView->addChild(whiteV);
    auto title = Label::createWithSystemFont("选择","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
    title->setPosition(Vec2(20,60));
    title->setTextColor(Color4B(0,0,0, 255/3*2));
    title->setAnchorPoint(Vec2(0, 0));
    whiteV->addChild(title);
    //椎弓根螺钉  PKP  PVP
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "PVP", 1005, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-200, 10), "PKP", 1004, 120, whiteV);
            createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "椎弓根螺钉", 1001, 220, whiteV);
    auto greenV=Sprite::create("recover_rect_green.png");
    greenV->setPosition(Vec2(10, contentSize.height-10));
    greenV->setAnchorPoint(Vec2(0, 1));
    greenV->setContentSize(Size(contentSize.width-20, 60));
    bkView->addChild(greenV);
    auto userName = Label::createWithSystemFont("经皮","Arial",35,Size(400,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    greenV->addChild(userName);
    
//通道
    auto whiteV2=Sprite::create("bk_impress_rect_white.png");
    whiteV2->setPosition(Vec2(10, contentSize.height-20-60*3));
    whiteV2->setAnchorPoint(Vec2(0, 1));
    whiteV2->setContentSize(Size(contentSize.width-20, 60*3));
    whiteV2->setTag(tag);
    bkView->addChild(whiteV2);
    auto title2 = Label::createWithSystemFont("选择","Arial",35,Size(130,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
    title2->setPosition(Vec2(20,60));
    title2->setTextColor(Color4B(0,0,0, 255/3*2));
    title2->setAnchorPoint(Vec2(0, 0));
    whiteV2->addChild(title2);
    //MISTLIF       LLIF         髓核摘除    椎管减压
    createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "髓核摘除", 1005, 180, whiteV2);
    createSelectBox(Vec2(whiteV->getContentSize().width-330, 10), "椎管减压", 1004, 180, whiteV2);
    createSelectBox(Vec2(whiteV->getContentSize().width-60, 70), "LLIF", 1001, 120, whiteV2);
    createSelectBox(Vec2(whiteV->getContentSize().width-200, 70), "MISTLIF", 1001, 220, whiteV2);
    auto greenV2=Sprite::create("recover_rect_green.png");
    greenV2->setPosition(Vec2(10, contentSize.height-60*3-20));
    greenV2->setAnchorPoint(Vec2(0, 1));
    greenV2->setContentSize(Size(contentSize.width-20, 60));
    bkView->addChild(greenV2);
    auto userName2 = Label::createWithSystemFont("通道","Arial",35,Size(400,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName2->setPosition(Vec2(20,0));
    userName2->setTextColor(Color4B(255, 255, 255, 255));
    userName2->setAnchorPoint(Vec2(0, 0));
    greenV2->addChild(userName2);
    //椎间孔镜  椎间盘镜  胸腔镜
    auto whiteV3=Sprite::create("bk_impress_rect_white.png");
    whiteV3->setPosition(Vec2(10, contentSize.height-30-60*6));
    whiteV3->setAnchorPoint(Vec2(0, 1));
    whiteV3->setContentSize(Size(contentSize.width-20, 60*2));
    bkView->addChild(whiteV3);
    createSelectBox(Vec2(whiteV->getContentSize().width-60, 10), "胸腔镜", 1005, 180, whiteV3);
    createSelectBox(Vec2(whiteV->getContentSize().width-240, 10), "椎间盘镜", 1004, 180, whiteV3);
    if (tag==2||tag==3) {
        createSelectBox(Vec2(whiteV->getContentSize().width-440, 10), "椎间盘镜", 1004, 180, whiteV3);
    }
    auto greenV3=Sprite::create("recover_rect_green.png");
    greenV3->setPosition(Vec2(10, contentSize.height-60*6-30));
    greenV3->setAnchorPoint(Vec2(0, 1));
    greenV3->setContentSize(Size(contentSize.width-20, 60));
    bkView->addChild(greenV3);
    auto userName3 = Label::createWithSystemFont("内镜","Arial",35,Size(400,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName3->setPosition(Vec2(20,0));
    userName3->setTextColor(Color4B(255, 255, 255, 255));
    userName3->setAnchorPoint(Vec2(0, 0));
    greenV3->addChild(userName3);
    
    
}




void TreatWayScene::createSelectBox(Vec2 origin,string name,int tag,float width,Sprite*bkView){
    auto acceptLB= Label::createWithSystemFont(name,"Arial",32,Size(width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(origin);
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("btn_appearance_unsure.png","btn_appearance_sure.png");
    acceptBox->setPosition(Vec2(origin.x+5,origin.y));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setScale(0.9);
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(TreatWayScene::checkBoxCallback,this));
    bkView->addChild(acceptBox);
    if (tag==0||tag==3||tag==6||tag==9||tag==12) {
        acceptBox->setSelected(true);
    }
    boxDic.insert(tag, acceptBox);
}

void TreatWayScene::createOtherSelectBox(Vec2 origin,string name,int tag,Sprite*bkView){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto acceptLB= Label::createWithSystemFont(name,"Arial",32,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(origin);
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("btn_appearance_unsure.png","btn_appearance_sure.png");
    acceptBox->setPosition(Vec2(bkView->getContentSize().width-50,origin.y));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setScale(0.9);
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(TreatWayScene::checkBoxCallback,this));
    bkView->addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, origin.y-10));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(bkView->getContentSize().width,1.5));
    bkView->addChild(lineV);
}



void TreatWayScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    int tag= item->getTag();
    Layout*   layout=(Layout*)lv->getItem(tag-100);
    Sprite* blueV=(Sprite*)layout->getChildByTag(tag-100);
    log("index:%d,tag:%d",index,tag);
    
    float changeHeight=0;
    switch (tag-100)
    {
        case 0:changeHeight=740;   break;
        case 1:changeHeight=860;   break;
        case 2:changeHeight=740;   break;
        case 3:changeHeight=740;   break;
        case 4:changeHeight=860;   break;
        default:
            break;
    }
    Sprite*whiteV=whiteViewDic.at(tag-100);
    
    if (index==1) {
//展开
        layout->setContentSize(Size(visibleSize.width, layout->getContentSize().height+changeHeight));
        blueV->setPosition(Vec2(blueV->getPosition().x, layout->getContentSize().height-10));
        lv->setInnerContainerSize(Size(visibleSize.width, lv->getInnerContainerSize().height+changeHeight));
        if (lv->getContentSize().height+changeHeight<visibleSize.height-190) {
            lv->setContentSize(Size(visibleSize.width,  lv->getInnerContainerSize().height+changeHeight));
        }else{ lv->setContentSize(Size(visibleSize.width, visibleSize.height-190));}
        whiteV->setVisible(true);
    }else{
//收拢
         layout->setContentSize(Size(visibleSize.width, layout->getContentSize().height-changeHeight));
        blueV->setPosition(Vec2(blueV->getPosition().x, layout->getContentSize().height-10));
        if (lv->getInnerContainerSize().height-changeHeight<visibleSize.height-190) {
         lv->setContentSize(Size(visibleSize.width, lv->getInnerContainerSize().height-changeHeight));}
        lv->setInnerContainerSize(Size(visibleSize.width, lv->getInnerContainerSize().height-changeHeight));
        whiteV->setVisible(false);
    }
    onEnter();
}

void TreatWayScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
        {
            if (tag==0||tag==1||tag==2){             multLayer0->switchTo(tag);
                for(int i=0;i<3;i++){ CheckBox *box=boxDic.at(i);if(box->getTag()!=tag)box->setSelected(false);  }                  }
             if (tag==3||tag==4||tag==5){            multLayer1->switchTo(tag-3);
                 for(int i=3;i<6;i++){ CheckBox *box=boxDic.at(i);if(box->getTag()!=tag)box->setSelected(false);  }                  }
             if (tag==6||tag==7||tag==8){            multLayer2->switchTo(tag-6);
                 for(int i=6;i<9;i++){ CheckBox *box=boxDic.at(i);if(box->getTag()!=tag)box->setSelected(false);  }                  }
             if (tag==9||tag==10||tag==11){        multLayer3->switchTo(tag-9);
                 for(int i=9;i<12;i++){ CheckBox *box=boxDic.at(i);if(box->getTag()!=tag)box->setSelected(false);  }                  }
             if (tag==12||tag==13||tag==14){      multLayer4->switchTo(tag-12);
                 for(int i=12;i<15;i++){ CheckBox *box=boxDic.at(i);if(box->getTag()!=tag)box->setSelected(false);  }                  }
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED");
            break;
        default:
            break;
    }
}

void TreatWayScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            break;
        }
        default:
            break;
    }
}
void TreatWayScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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


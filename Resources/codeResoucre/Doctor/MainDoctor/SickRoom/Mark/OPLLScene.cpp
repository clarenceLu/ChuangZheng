//
//  OPLLScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/8.
//

#include "OPLLScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *OPLLScene::createScene(){
    return OPLLScene::create();
}
bool OPLLScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_OPLL.png");
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
            pushDataToNetWork();
            log("OPLL sure");
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    scrollV=createTableView(Vec2(0, visibleSize.height-170), Size(visibleSize.width, visibleSize.height-190));
    this->addChild(scrollV);
    return true;
}
ScrollView* OPLLScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setAnchorPoint(Vec2(0, 1));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    createScrollDetailView(scrollView);
    return scrollView;
}

void OPLLScene::createScrollDetailView(ScrollView* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("alpha.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height-190));
    superV->addChild(bkView);

    auto weightLB = Label::createWithSystemFont("体重","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    weightLB->setPosition(Point(56,visibleSize.height-240));
    weightLB->setTextColor(Color4B(91,144,230, 255));
    weightLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(weightLB);
    weightField=TextField::create("数值","Arial",35);
    weightField->setMaxLength(60);
    weightField->setTouchSize(Size(visibleSize.width-360,50));
    weightField->setAnchorPoint(Vec2(1,0));
    weightField->setPosition(Point(visibleSize.width-100,visibleSize.height-240));
    weightField->setContentSize(Size(visibleSize.width-360,50));
    weightField->setPlaceHolderColor(Color4B(91, 144, 229, 200));
    weightField->setTextColor(Color4B(0, 0, 0, 220));
    weightField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    weightField->addEventListener(CC_CALLBACK_2(OPLLScene::eventCallBack, this));
    textFieldDic.insert(0, weightField);
    bkView->addChild(weightField);
    auto weightLB2 = Label::createWithSystemFont("kg","Arial",35,Size(visibleSize.width-310,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    weightLB2->setPosition(Point(260,visibleSize.height-240));
    weightLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    weightLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(weightLB2);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(50, visibleSize.height-255));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV);
    
    auto timeLB = Label::createWithSystemFont("病程","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(56,visibleSize.height-330));
    timeLB->setTextColor(Color4B(91,144,230, 255));
    timeLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(timeLB);
    timeField=TextField::create("数值","Arial",35);
    timeField->setMaxLength(60);
    timeField->setTouchSize(Size(visibleSize.width-360,50));
    timeField->setAnchorPoint(Vec2(1,0));
    timeField->setPosition(Point(visibleSize.width-170,visibleSize.height-330));
    timeField->setContentSize(Size(visibleSize.width-360,50));
    timeField->setPlaceHolderColor(Color4B(91, 144, 229, 200));
    timeField->setTextColor(Color4B(0, 0, 0, 220));
    timeField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    timeField->addEventListener(CC_CALLBACK_2(OPLLScene::eventCallBack, this));
    textFieldDic.insert(1, timeField);
    bkView->addChild(timeField);
    auto timeLB2 = Label::createWithSystemFont("month","Arial",35,Size(visibleSize.width-310,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    timeLB2->setPosition(Point(260,visibleSize.height-330));
    timeLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    timeLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(timeLB2);
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(50, visibleSize.height-345));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV2);
    
    auto Sex = Label::createWithSystemFont("吸烟","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Sex->setPosition(Vec2(56, visibleSize.height-415));
    Sex->setTextColor(Color4B(91, 144, 229, 255));
    Sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Sex);
    auto lineV3=Sprite::create("userInfo_line.png");
    lineV3->setPosition(Vec2(50,visibleSize.height-430));
    lineV3->setAnchorPoint(Vec2(0, 0));
    lineV3->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV3);
    auto manCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    manCheckBox->setPosition(Vec2(380, visibleSize.height-415));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(0);
    manCheckBox->setTouchEnabled(true);
    boxDic.insert(0, manCheckBox);
    manCheckBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(manCheckBox);
    auto manLB= Label::createWithSystemFont("是","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    manLB->setPosition(Vec2(420, visibleSize.height-415));
    manLB->setTextColor(Color4B(91, 144, 229, 255));
    manLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(manLB);
    auto womanCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    womanCheckBox->setPosition(Vec2(500, visibleSize.height-415));
    womanCheckBox->setTag(1);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    womanCheckBox->setTouchEnabled(true);
    boxDic.insert(1, womanCheckBox);
    womanCheckBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
   bkView->addChild(womanCheckBox);
    auto womanLB= Label::createWithSystemFont("否","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    womanLB->setPosition(Vec2(540, visibleSize.height-415));
    womanLB->setTextColor(Color4B(91, 144, 229, 255));
    womanLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(womanLB);
  
//骨化类型
    auto greenV=Sprite::create("recover_rect_green.png");
    greenV->setPosition(Vec2(14, visibleSize.height-492));
    greenV->setAnchorPoint(Vec2(0, 0));
    greenV->setContentSize(Size(visibleSize.width-28, 62));
    bkView->addChild(greenV);
    auto skeletonLB= Label::createWithSystemFont("骨化类型","Arial",35,Size(200,62),TextHAlignment::LEFT,TextVAlignment::CENTER);
    skeletonLB->setPosition(Vec2(40, 0));
    skeletonLB->setTextColor(Color4B(255, 255, 255, 255));
    skeletonLB->setAnchorPoint(Vec2(0, 0));
    greenV->addChild(skeletonLB);

    
  //矢状位
    auto vectorLB = Label::createWithSystemFont("矢状位","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    vectorLB->setPosition(Point(56,visibleSize.height-545));
    vectorLB->setTextColor(Color4B(91,144,230, 255));
    vectorLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(vectorLB);
    
    auto limitLB= Label::createWithSystemFont("局限型","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    limitLB->setPosition(Vec2(56, visibleSize.height-595));
    limitLB->setTextColor(Color4B(0,0,0, 255/3*2));
    limitLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(limitLB);
    auto limitBox = CheckBox::create("select_circle.png","select_sure.png");
    limitBox->setPosition(Vec2(176, visibleSize.height-595));
    limitBox->setAnchorPoint(Vec2(0, 0));
    limitBox->setTag(2);
    limitBox->setTouchEnabled(true);
    boxDic.insert(2, limitBox);
    limitBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(limitBox);
    
    auto serialLB= Label::createWithSystemFont("连续型","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    serialLB->setPosition(Vec2(250, visibleSize.height-595));
    serialLB->setTextColor(Color4B(0,0,0, 255/3*2));
    serialLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(serialLB);
    auto serialBox = CheckBox::create("select_circle.png","select_sure.png");
    serialBox->setPosition(Vec2(370, visibleSize.height-595));
    serialBox->setAnchorPoint(Vec2(0, 0));
    serialBox->setTag(3);
    serialBox->setTouchEnabled(true);
    boxDic.insert(3, serialBox);
    serialBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(serialBox);
    
    auto mixLB= Label::createWithSystemFont("混合型","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    mixLB->setPosition(Vec2(430, visibleSize.height-595));
    mixLB->setTextColor(Color4B(0,0,0, 255/3*2));
    mixLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(mixLB);
    auto mixBox = CheckBox::create("select_circle.png","select_sure.png");
    mixBox->setPosition(Vec2(550, visibleSize.height-595));
    mixBox->setAnchorPoint(Vec2(0, 0));
    mixBox->setTag(4);
    mixBox->setTouchEnabled(true);
    boxDic.insert(4, mixBox);
    mixBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(mixBox);
    
    auto lineV4=Sprite::create("userInfo_line.png");
    lineV4->setPosition(Vec2(50,visibleSize.height-610));
    lineV4->setAnchorPoint(Vec2(0, 0));
    lineV4->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV4);
    
    
//横断面
    auto heightLB = Label::createWithSystemFont("横断面","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    heightLB->setPosition(Point(56,visibleSize.height-670));
    heightLB->setTextColor(Color4B(91,144,230, 255));
    heightLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(heightLB);
    auto occupyLB = Label::createWithSystemFont("占位率","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    occupyLB->setPosition(Point(330,visibleSize.height-670));
    occupyLB->setTextColor(Color4B(91,144,230, 255));
    occupyLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(occupyLB);
    occupyField=TextField::create("数值","Arial",35);
    occupyField->setMaxLength(60);
    occupyField->setTouchSize(Size(visibleSize.width-360,50));
    occupyField->setAnchorPoint(Vec2(1,0));
    occupyField->setPosition(Point(visibleSize.width-100,visibleSize.height-670));
    occupyField->setContentSize(Size(visibleSize.width-360,50));
    occupyField->setPlaceHolderColor(Color4B(91, 144, 229, 200));
    occupyField->setTextColor(Color4B(0, 0, 0, 220));
    occupyField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    occupyField->addEventListener(CC_CALLBACK_2(OPLLScene::eventCallBack, this));
    textFieldDic.insert(2, occupyField);
    bkView->addChild(occupyField);
    auto occupyLB2 = Label::createWithSystemFont("%","Arial",35,Size(90,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    occupyLB2->setPosition(Point(visibleSize.width-56,visibleSize.height-670));
    occupyLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    occupyLB2->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(occupyLB2);
    
    auto openLB= Label::createWithSystemFont("开口型","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    openLB->setPosition(Vec2(56, visibleSize.height-720));
    openLB->setTextColor(Color4B(0,0,0, 255/3*2));
    openLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(openLB);
    auto openBox = CheckBox::create("select_circle.png","select_sure.png");
    openBox->setPosition(Vec2(176, visibleSize.height-720));
    openBox->setAnchorPoint(Vec2(0, 0));
    openBox->setTag(5);
    openBox->setTouchEnabled(true);
    boxDic.insert(5, openBox);
    openBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(openBox);
    
    auto closeLB= Label::createWithSystemFont("闭口型","Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    closeLB->setPosition(Vec2(250, visibleSize.height-720));
    closeLB->setTextColor(Color4B(0,0,0, 255/3*2));
    closeLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(closeLB);
    auto closeBox = CheckBox::create("select_circle.png","select_sure.png");
    closeBox->setPosition(Vec2(370, visibleSize.height-720));
    closeBox->setAnchorPoint(Vec2(0, 0));
    closeBox->setTag(6);
    closeBox->setTouchEnabled(true);
    boxDic.insert(6, closeBox);
    closeBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(closeBox);
    auto lineV5=Sprite::create("userInfo_line.png");
    lineV5->setPosition(Vec2(50,visibleSize.height-735));
    lineV5->setAnchorPoint(Vec2(0, 0));
    lineV5->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV5);
    
//Cobb's角
    auto cobbLB = Label::createWithSystemFont("Cobb's角","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    cobbLB->setPosition(Point(56,visibleSize.height-785));
    cobbLB->setTextColor(Color4B(91,144,230, 255));
    cobbLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(cobbLB);
    cobbsField=TextField::create("数值","Arial",35);
    cobbsField->setMaxLength(60);
    cobbsField->setTouchSize(Size(visibleSize.width-360,50));
    cobbsField->setAnchorPoint(Vec2(1,0));
    cobbsField->setPosition(Point(visibleSize.width-100,visibleSize.height-785));
    cobbsField->setContentSize(Size(visibleSize.width-360,50));
    cobbsField->setPlaceHolderColor(Color4B(91, 144, 229, 200));
    cobbsField->setTextColor(Color4B(0, 0, 0, 220));
    cobbsField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    cobbsField->addEventListener(CC_CALLBACK_2(OPLLScene::eventCallBack, this));
    textFieldDic.insert(3, cobbsField);
    bkView->addChild(cobbsField);
    auto cobbLB2 = Label::createWithSystemFont("度","Arial",35,Size(visibleSize.width-310,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    cobbLB2->setPosition(Point(260,visibleSize.height-785));
    cobbLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    cobbLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(cobbLB2);
    auto lineV6=Sprite::create("userInfo_line.png");
    lineV6->setPosition(Vec2(50, visibleSize.height-800));
    lineV6->setAnchorPoint(Vec2(0, 0));
    lineV6->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV6);
    
//K-line
    auto klineLB = Label::createWithSystemFont("K-line","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    klineLB->setPosition(Point(56,visibleSize.height-850));
    klineLB->setTextColor(Color4B(91,144,230, 255));
    klineLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(klineLB);
    
    auto adjectiveLB= Label::createWithSystemFont("阳性","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    adjectiveLB->setPosition(Vec2(56, visibleSize.height-900));
    adjectiveLB->setTextColor(Color4B(0,0,0, 255/3*2));
    adjectiveLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(adjectiveLB);
    auto adjectiveBox = CheckBox::create("select_circle.png","select_sure.png");
    adjectiveBox->setPosition(Vec2(146, visibleSize.height-900));
    adjectiveBox->setAnchorPoint(Vec2(0, 0));
    adjectiveBox->setTag(7);
    adjectiveBox->setTouchEnabled(true);
    boxDic.insert(7, adjectiveBox);
    adjectiveBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(adjectiveBox);
    
    auto negativeLB= Label::createWithSystemFont("阴性","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    negativeLB->setPosition(Vec2(220, visibleSize.height-900));
    negativeLB->setTextColor(Color4B(0,0,0, 255/3*2));
    negativeLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(negativeLB);
    auto negativeBox = CheckBox::create("select_circle.png","select_sure.png");
    negativeBox->setPosition(Vec2(310, visibleSize.height-900));
    negativeBox->setAnchorPoint(Vec2(0, 0));
    negativeBox->setTag(8);
    negativeBox->setTouchEnabled(true);
    boxDic.insert(8, negativeBox);
    negativeBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(negativeBox);
    auto lineV7=Sprite::create("userInfo_line.png");
    lineV7->setPosition(Vec2(50,visibleSize.height-915));
    lineV7->setAnchorPoint(Vec2(0, 0));
    lineV7->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV7);
    
    
//并发症
    auto complicationLB = Label::createWithSystemFont("并发症","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    complicationLB->setPosition(Point(56,visibleSize.height-975));
    complicationLB->setTextColor(Color4B(91,144,230, 255));
    complicationLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(complicationLB);
    
    auto compLB1= Label::createWithSystemFont("脑脊液漏","Arial",35,Size(150,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    compLB1->setPosition(Vec2(56, visibleSize.height-1025));
    compLB1->setTextColor(Color4B(0,0,0, 255/3*2));
    compLB1->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(compLB1);
    auto compBox1 = CheckBox::create("select_circle.png","select_sure.png");
    compBox1->setPosition(Vec2(210, visibleSize.height-1025));
    compBox1->setAnchorPoint(Vec2(0, 0));
    compBox1->setTag(9);
    compBox1->setTouchEnabled(true);
    boxDic.insert(9, compBox1);
    compBox1->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(compBox1);
    
    auto compLB2= Label::createWithSystemFont("神经症状加重","Arial",35,Size(220,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    compLB2->setPosition(Vec2(280, visibleSize.height-1025));
    compLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    compLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(compLB2);
    auto compBox2 = CheckBox::create("select_circle.png","select_sure.png");
    compBox2->setPosition(Vec2(500, visibleSize.height-1025));
    compBox2->setAnchorPoint(Vec2(0, 0));
    compBox2->setTag(10);
    compBox2->setTouchEnabled(true);
    boxDic.insert(10, compBox2);
    compBox2->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(compBox2);
    
    auto compLB3= Label::createWithSystemFont("C5神经根麻痹","Arial",35,Size(220,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    compLB3->setPosition(Vec2(56, visibleSize.height-1075));
    compLB3->setTextColor(Color4B(0,0,0, 255/3*2));
    compLB3->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(compLB3);
    auto compBox3 = CheckBox::create("select_circle.png","select_sure.png");
    compBox3->setPosition(Vec2(280, visibleSize.height-1075));
    compBox3->setAnchorPoint(Vec2(0, 0));
    compBox3->setTag(11);
    compBox3->setTouchEnabled(true);
    boxDic.insert(11, compBox3);
    compBox3->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(compBox3);
    
    auto compLB4= Label::createWithSystemFont("骨化物进展","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    compLB4->setPosition(Vec2(330, visibleSize.height-1075));
    compLB4->setTextColor(Color4B(0,0,0, 255/3*2));
    compLB4->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(compLB4);
    auto compBox4 = CheckBox::create("select_circle.png","select_sure.png");
    compBox4->setPosition(Vec2(520, visibleSize.height-1075));
    compBox4->setAnchorPoint(Vec2(0, 0));
    compBox4->setTag(12);
    compBox4->setTouchEnabled(true);
    boxDic.insert(12, compBox4);
    compBox4->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(compBox4);
    
    auto lineV8=Sprite::create("userInfo_line.png");
    lineV8->setPosition(Vec2(50,visibleSize.height-1090));
    lineV8->setAnchorPoint(Vec2(0, 0));
    lineV8->setContentSize(Size(540, 2.5));
    bkView->addChild(lineV8);
   
    
    auto otherLB = Label::createWithSystemFont("其他","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    otherLB->setPosition(Point(56,visibleSize.height-1150));
    otherLB->setTextColor(Color4B(91,144,230, 255));
    otherLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(otherLB);
    otherField=TextField::create("点击填写","Arial",35);
    otherField->setMaxLength(60);
    otherField->setTouchSize(Size(visibleSize.width-360,50));
    otherField->setAnchorPoint(Vec2(1,0));
    otherField->setPosition(Point(visibleSize.width-100,visibleSize.height-1150));
    otherField->setContentSize(Size(visibleSize.width-360,50));
    otherField->setPlaceHolderColor(Color4B(91, 144, 229, 200));
    otherField->setTextColor(Color4B(0, 0, 0, 220));
    otherField->setTextHorizontalAlignment(TextHAlignment::CENTER);
    otherField->addEventListener(CC_CALLBACK_2(OPLLScene::eventCallBack, this));
    textFieldDic.insert(4, otherField);
    bkView->addChild(otherField);
    
 //风险平衡评价
    auto greenV2=Sprite::create("recover_rect_green.png");
    greenV2->setPosition(Vec2(14, visibleSize.height-1220));
    greenV2->setAnchorPoint(Vec2(0, 0));
    greenV2->setContentSize(Size(visibleSize.width-28, 62));
    bkView->addChild(greenV2);
    auto markLB= Label::createWithSystemFont("风险平衡评价(随访时填写)","Arial",35,Size(460,62),TextHAlignment::LEFT,TextVAlignment::CENTER);
    markLB->setPosition(Vec2(40, 0));
    markLB->setTextColor(Color4B(255, 255, 255, 255));
    markLB->setAnchorPoint(Vec2(0, 0));
    greenV2->addChild(markLB);
    
    auto recoverLB = Label::createWithSystemFont("A.对神经功能恢复是否满意","Arial",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recoverLB->setPosition(Point(56,visibleSize.height-1280));
    recoverLB->setTextColor(Color4B(91,144,230, 255));
    recoverLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(recoverLB);
    createSelectView(13, Vec2(0, visibleSize.height-1330), "患者:", bkView);
    createSelectView(16, Vec2(0, visibleSize.height-1390), "医生:", bkView);
    
    auto recoverLB2 = Label::createWithSystemFont("B.(患者)对颈部活动度/(医生)对生理曲度恢复是否满意","Arial",35,Size(500,100),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recoverLB2->setPosition(Point(56,visibleSize.height-1500));
    recoverLB2->setTextColor(Color4B(91,144,230, 255));
    recoverLB2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(recoverLB2);
    createSelectView(19, Vec2(0, visibleSize.height-1560), "患者:", bkView);
    createSelectView(22, Vec2(0, visibleSize.height-1620), "医生:", bkView);
    
    auto recoverLB3 = Label::createWithSystemFont("C. 对并发症是否接受","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recoverLB3->setPosition(Point(56,visibleSize.height-1680));
    recoverLB3->setTextColor(Color4B(91,144,230, 255));
    recoverLB3->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(recoverLB3);
    
    auto complication1 = Label::createWithSystemFont("脑脊液漏","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    complication1->setPosition(Point(56,visibleSize.height-1740));
    complication1->setTextColor(Color4B(91,144,230, 255));
    complication1->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(complication1);
    createSelectView(25, Vec2(0, visibleSize.height-1800), "患者:", bkView);
    createSelectView(28, Vec2(0, visibleSize.height-1860), "医生:", bkView);
    
    auto complication2 = Label::createWithSystemFont("神经症状加重","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    complication2->setPosition(Point(56,visibleSize.height-1920));
    complication2->setTextColor(Color4B(91,144,230, 255));
    complication2->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(complication2);
    createSelectView(31, Vec2(0, visibleSize.height-1980), "患者:", bkView);
    createSelectView(34, Vec2(0, visibleSize.height-2040), "医生:", bkView);
    
    auto complication3 = Label::createWithSystemFont("C5神经根麻痹","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    complication3->setPosition(Point(56,visibleSize.height-2100));
    complication3->setTextColor(Color4B(91,144,230, 255));
    complication3->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(complication3);
    createSelectView(37, Vec2(0, visibleSize.height-2160), "患者:", bkView);
    createSelectView(40, Vec2(0, visibleSize.height-2220), "医生:", bkView);
    
    auto complication4 = Label::createWithSystemFont("骨化物进展","Arial",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    complication4->setPosition(Point(56,visibleSize.height-2280));
    complication4->setTextColor(Color4B(91,144,230, 255));
    complication4->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(complication4);
    createSelectView(43, Vec2(0, visibleSize.height-2340), "患者:", bkView);
    createSelectView(46, Vec2(0, visibleSize.height-2400), "医生:", bkView);
    
    
    superV->setInnerContainerSize(Size(visibleSize.width, 2400-170));
    bkView->setPosition(Vec2(0, 2400-170-950));
    
    getDataToNetWork();
    
}

void OPLLScene::createSelectView(int tag,Vec2 point,string title,Sprite*bkView){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userLB= Label::createWithSystemFont(title,"Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userLB->setPosition(Vec2(56, point.y));
    userLB->setTextColor(Color4B(0,0,0, 255/3*2));
    userLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userLB);
    auto acceptLB= Label::createWithSystemFont("接受","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(Vec2(150, point.y));
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","select_sure.png");
    acceptBox->setPosition(Vec2(230, point.y));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    boxDic.insert(tag, acceptBox);
    acceptBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(acceptBox);
    
    auto refuseLB= Label::createWithSystemFont("拒绝","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    refuseLB->setPosition(Vec2(310, point.y));
    refuseLB->setTextColor(Color4B(0,0,0, 255/3*2));
    refuseLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(refuseLB);
    auto refuseBox = CheckBox::create("select_circle.png","select_sure.png");
    refuseBox->setPosition(Vec2(390, point.y));
    refuseBox->setAnchorPoint(Vec2(0, 0));
    refuseBox->setTag(tag+1);
    refuseBox->setTouchEnabled(true);
    boxDic.insert(tag+1, refuseBox);
    refuseBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(refuseBox);
    
    auto allLB= Label::createWithSystemFont("均可","Arial",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    allLB->setPosition(Vec2(460, point.y));
    allLB->setTextColor(Color4B(0,0,0, 255/3*2));
    allLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(allLB);
    auto allBox = CheckBox::create("select_circle.png","select_sure.png");
    allBox->setPosition(Vec2(540, point.y));
    allBox->setAnchorPoint(Vec2(0, 0));
    allBox->setTag(tag+2);
    allBox->setTouchEnabled(true);
    boxDic.insert(tag+2, allBox);
    allBox->addEventListener(CC_CALLBACK_2(OPLLScene::checkBoxCallback,this));
    bkView->addChild(allBox);
    
}


void OPLLScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    log("content %s",textField->getString().c_str());
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

void OPLLScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
{
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
             log("Box tag:%d,boxSize :%ld",tag,boxDic.size());
            if (tag>=0&&tag<2) {
                for (int i=0; i<2; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=2&&tag<5) {
                for (int i=2; i<5; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=5&&tag<7) {
                for (int i=5; i<7; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=7&&tag<9) {
                for (int i=7; i<9; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=13&&tag<16) {
                for (int i=13; i<16; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=16&&tag<19) {
                for (int i=16; i<19; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=19&&tag<22) {
                for (int i=19; i<22; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=13&&tag<16) {
                for (int i=13; i<16; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=22&&tag<25) {
                for (int i=22; i<25; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=25&&tag<28) {
                for (int i=25; i<28; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=28&&tag<31) {
                for (int i=28; i<31; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=31&&tag<34) {
                for (int i=31; i<34; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=34&&tag<37) {
                for (int i=34; i<37; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=37&&tag<40) {
                for (int i=37; i<40; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=40&&tag<43) {
                for (int i=40; i<43; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=43&&tag<46) {
                for (int i=43; i<46; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=46&&tag<49) {
                for (int i=46; i<49; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            
}
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");{
                
            }
            break;
        default:
            break;
    }
}

std::string OPLLScene::getJsonData(int type)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    if (type==0) {
        rapidjson::Value array(rapidjson::kArrayType);
        rapidjson::Value array2(rapidjson::kArrayType);
        rapidjson::Value array3(rapidjson::kArrayType);
        rapidjson::Value array4(rapidjson::kArrayType);
        rapidjson::Value array5(rapidjson::kArrayType);
        rapidjson::Value array6(rapidjson::kArrayType);
        rapidjson::Value array7(rapidjson::kArrayType);
        rapidjson::Value array8(rapidjson::kArrayType);
        rapidjson::Value array9(rapidjson::kArrayType);
        rapidjson::Value array10(rapidjson::kArrayType);
        rapidjson::Value array11(rapidjson::kArrayType);
        rapidjson::Value array12(rapidjson::kArrayType);
        rapidjson::Value array13(rapidjson::kArrayType);
        rapidjson::Value array14(rapidjson::kArrayType);
        rapidjson::Value array15(rapidjson::kArrayType);
        rapidjson::Value array16(rapidjson::kArrayType);
        rapidjson::Value array17(rapidjson::kArrayType);
        rapidjson::Value array18(rapidjson::kArrayType);
        array18.PushBack(rapidjson::Value(weightField->getString().c_str(), allocator),allocator);
        rapidjson::Value array19(rapidjson::kArrayType);
        array19.PushBack(rapidjson::Value(timeField->getString().c_str(), allocator),allocator);
        rapidjson::Value array20(rapidjson::kArrayType);
        array20.PushBack(rapidjson::Value(occupyField->getString().c_str(), allocator),allocator);
        rapidjson::Value array21(rapidjson::kArrayType);
        array21.PushBack(rapidjson::Value(cobbsField->getString().c_str(), allocator),allocator);
        rapidjson::Value array22(rapidjson::kArrayType);
        array22.PushBack(rapidjson::Value(otherField->getString().c_str(), allocator),allocator);
        document.AddMember("体重", array18, allocator);
        document.AddMember("病程", array19, allocator);
        document.AddMember("占位率", array20, allocator);
        document.AddMember("cobbs角", array21, allocator);
        document.AddMember("其他", array22, allocator);
        
        
        for (int i=0; i<boxDic.size(); i++) {
            CheckBox* box=(CheckBox*)boxDic.at(i);
            int tag=box->getTag();
            if (tag>=0&&tag<2) {
                if (box->getSelectedState()) {
                    array.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=2&&tag<5) {
                if (box->getSelectedState()) {
                    array2.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array2.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=5&&tag<7) {
                if (box->getSelectedState()) {
                    array3.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array3.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=7&&tag<9) {
                if (box->getSelectedState()) {
                    array4.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array4.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=13&&tag<16) {
                if (box->getSelectedState()) {
                    array5.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array5.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=16&&tag<19) {
                if (box->getSelectedState()) {
                    array6.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array6.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=19&&tag<22) {
                if (box->getSelectedState()) {
                    array7.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array7.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=13&&tag<16) {
                if (box->getSelectedState()) {
                    array8.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array8.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=22&&tag<25) {
                if (box->getSelectedState()) {
                    array9.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array9.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=25&&tag<28) {
                if (box->getSelectedState()) {
                    array10.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array10.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=28&&tag<31) {
                if (box->getSelectedState()) {
                    array11.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array11.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=31&&tag<34) {
                if (box->getSelectedState()) {
                    array12.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array12.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=34&&tag<37) {
                if (box->getSelectedState()) {
                    array13.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array13.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=37&&tag<40) {
                if (box->getSelectedState()) {
                    array14.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array14.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=40&&tag<43) {
                if (box->getSelectedState()) {
                    array15.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array15.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=43&&tag<46) {
                if (box->getSelectedState()) {
                    array16.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array16.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=46&&tag<49) {
                if (box->getSelectedState()) {
                    array17.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    array17.PushBack(rapidjson::Value(to_string(tag).c_str(), allocator),allocator);
                }
            }
            
            
        }
        document.AddMember("吸烟", array, allocator);
        document.AddMember("矢状位", array2, allocator);
        document.AddMember("横断面", array3, allocator);
        document.AddMember("K-line", array4, allocator);
        document.AddMember("并发症", array5, allocator);
        document.AddMember("神经功能恢复-患者", array6, allocator);
        document.AddMember("神经功能恢复-医生", array7, allocator);
        document.AddMember("颈部活动度-患者", array8, allocator);
        document.AddMember("生理曲度恢复-医生", array9, allocator);
        document.AddMember("并发脑脊液漏-患者", array10, allocator);
        document.AddMember("并发脑脊液漏-医生", array11, allocator);
        document.AddMember("并发神经症状加重-患者", array12, allocator);
        document.AddMember("并发神经症状加重-医生", array13, allocator);
        document.AddMember("并发C5神经根麻痹-患者", array14, allocator);
        document.AddMember("并发C5神经根麻痹-医生", array15, allocator);
        document.AddMember("并发骨化物进展-患者", array16, allocator);
        document.AddMember("并发骨化物进展-医生", array17, allocator);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void OPLLScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    string jsonData=getJsonData(0);
    sprintf(jsonStr,"%s",jsonData.c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"pf_OPLL",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(OPLLScene::onHttpRequestCompleted, this),url);
}

void OPLLScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    if(!response -> isSucceed()){
        log("response failed");
        log("error buffer: %s", response -> getErrorBuffer());
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    rapidjson::Document jsondata;
    
    jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (jsondata.HasParseError()) {
        
        return;
    }
    if(jsondata.HasMember("status")){
        if (jsondata["status"].GetInt()==0) {
            Director::getInstance()->popScene();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}
string OPLLScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 0:
            content="是";break;
        case 1:
            content="否";break;
        case 2:
            content="局限型";break;
        case 3:
            content="连续型";break;//神经根型颈椎病
        case 4:
            content="混合型";break;
        case 5:
            content="开口型";break;
        case 6:
            content="闭口型";break;
        case 7:
            content="阳性";break;
        case 8:
            content="阴性";break;
        case 9:
            content="脑脊液漏";break;
        case 10:
            content="神经症状加重";break;
        case 11:
            content="C5神经麻痹";break;
        case 12:
            content="骨化物进展";break;
        case 13:case 16:case 19:case 22:case 25:case 28:case 31:case 34:case 37:case 40:case 43:case 46:
            content="接受";break;
        case 14:case 17:case 20:case 23:case 26:case 29:case 32:case 35:case 38:case 41:case 44:case 47:
            content="拒绝";break;
        case 15:case 18:case 21:case 24:case 27:case 30:case 33:case 36:case 39:case 42:case 45:case 48:
            content="均可";break;
        default:
            break;
    }
    return content;
}


#pragma-网络数据
void OPLLScene::getDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getCaseById?caseId=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str());
    netManeger->postHttpRequest(memberUrl,CC_CALLBACK_2(OPLLScene::onHttpRequestCompleted2, this),nullptr);
}

void OPLLScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    if(!response -> isSucceed()){
        log("response failed");
        log("error buffer: %s", response -> getErrorBuffer());
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
     rapidjson::Document Jsondata;
    
    Jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (Jsondata.HasParseError()) {
        
        return;
    }
    if(Jsondata.HasMember("status")){
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        Jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
        
        
        if (Jsondata["status"].GetInt()==0) {
            const rapidjson::Value& val_form = Jsondata["data"];
            if(val_form.IsObject()){
                if (!val_form["pf_OPLL"].IsNull()) {
                    infoData.Parse<rapidjson::kParseDefaultFlags>(val_form["pf_OPLL"].GetString());
//刷新界面
                    updateForInfoData();
                }
                
            }}
    }
}

void OPLLScene::updateForInfoData(){
    if (infoData.IsObject()) {
        for (auto j=infoData.MemberBegin(); j!=infoData.MemberEnd(); ++j) {
            auto key = (j->name).GetString();
            if (strcmp(key, "体重")==0) {
                if (infoData[key].Size()) {
                    weightField->setString(infoData[key][0].GetString());}
            }else if (strcmp(key, "病程")==0) {
                if (infoData[key].Size()) {
                    timeField->setString(infoData[key][0].GetString());}
            }else if (strcmp(key, "占位率")==0) {
                if (infoData[key].Size()) {
                    occupyField->setString(infoData[key][0].GetString());}
            }else if (strcmp(key, "cobbs角")==0) {
                if (infoData[key].Size()) {
                    cobbsField->setString(infoData[key][0].GetString());}
            }else if (strcmp(key, "其他")==0) {
                if (infoData[key].Size()) {
                    otherField->setString(infoData[key][0].GetString());}
            }else if(infoData[key].Size()>1){
                int tag=atoi(infoData[key][infoData[key].Size()-1].GetString());
                log("tag:%d",tag);
                CheckBox* box=(CheckBox*)boxDic.at(tag);
                box->setSelected(true);
               //都是选择题
            }
        }

    }
}



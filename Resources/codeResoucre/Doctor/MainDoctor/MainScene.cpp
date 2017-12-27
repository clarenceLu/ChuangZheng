//
//  MainScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#include "MainScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MainScene::createScene(){
    return MainScene::create();
}

bool MainScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    
    boxVec = std::make_shared<Vector<CheckBox*>>();  //default constructor
    
    auto layer1=createSickRoomLayer();
    auto layer2=createOutPatientLayer();
    auto layer3=createCalendarLayer();
    auto layer4=createSickInfoLayer();
    multLayer = LayerMultiplex::create(layer1, layer2,layer3,layer4,nullptr);
    addChild(multLayer, 0);
    
    auto bottom=Sprite::create("bk_perfect_bottom.png");
    bottom->setPosition(Vec2(0, 0));
    bottom->setAnchorPoint(Vec2(0, 0));
    bottom->setContentSize(Size(visibleSize.width, 100));
    this->addChild(bottom);
    
    auto sickRoomBox = CheckBox::create("btn_case_unselect.png","btn_case_select.png");
    //设置CheckBox的位置
    sickRoomBox->setPosition(Vec2(50,10));
    sickRoomBox->setTag(0);
    sickRoomBox->setAnchorPoint(Vec2(0, 0));
    sickRoomBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickRoomBox->setTouchEnabled(true);
    sickRoomBox->setSelected(true);
    sickRoomBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickRoomBox);
    
    auto outPatientBox = CheckBox::create("btn_inform_unselect.png","btn_inform_select.png");
    //设置CheckBox的位置
    outPatientBox->setPosition(Vec2(200,10));
    outPatientBox->setTag(1);
    outPatientBox->setAnchorPoint(Vec2(0, 0));
    outPatientBox->setScale(0.87);
    //设置CheckBox是否可点击
    outPatientBox->setTouchEnabled(true);
    outPatientBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(outPatientBox);
    
    auto calendarBox = CheckBox::create("btn_dynamic_unselect.png","btn_dynamic_select.png");
    //设置CheckBox的位置
    calendarBox->setPosition(Vec2(340,10));
    calendarBox->setTag(2);
    calendarBox->setAnchorPoint(Vec2(0, 0));
    calendarBox->setScale(0.87);
    //设置CheckBox是否可点击
    calendarBox->setTouchEnabled(true);
    calendarBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(calendarBox);
    
    auto sickInfoBox = CheckBox::create("btn_user_unselect.png","btn_user_select.png");
    //设置CheckBox的位置
    sickInfoBox->setPosition(Vec2(520,10));
    sickInfoBox->setTag(3);
    sickInfoBox->setAnchorPoint(Vec2(0, 0));
    sickInfoBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickInfoBox->setTouchEnabled(true);
    sickInfoBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickInfoBox);
    return true;
}

//病床
Layer* MainScene::createSickRoomLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_sickRoom.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto tempBedBox=CheckBox::create("box_tempBed_unselect.png","box_tempBed_select.png");
    //设置CheckBox的位置
    tempBedBox->setPosition(Vec2(visibleSize.width/2,918));
    tempBedBox->setTag(5);
    tempBedBox->setAnchorPoint(Vec2(0, 0));
    tempBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    tempBedBox->setTouchEnabled(true);
    tempBedBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
   bkView->addChild(tempBedBox);
    boxVec->pushBack(tempBedBox);
    auto fixedBedBox=CheckBox::create("box_fixedBed_unselect.png","box_fixedBed_select.png");
    //设置CheckBox的位置
    fixedBedBox->setPosition(Vec2(0,918));
    fixedBedBox->setTag(6);
    fixedBedBox->setAnchorPoint(Vec2(0, 0));
    fixedBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    fixedBedBox->setTouchEnabled(true);
    fixedBedBox->setSelected(true);
    fixedBedBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(fixedBedBox);
    boxVec->pushBack(fixedBedBox);
    
    auto line1=Sprite::create("userInfo_line.png");
    line1->setPosition(Vec2(0, 915));
    line1->setAnchorPoint(Vec2(0, 0));
    line1->setScaleX(1.05);
    bkView->addChild(line1);
    
    auto job = Label::createWithSystemFont("上海医院松江分院外科楼6楼","Arial",35,Size(visibleSize.width-40,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
    job->setPosition(Vec2(20,850));
    job->setTextColor(Color4B(0, 0, 0, 255/2));
    job->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(job);
    
    auto line2=Sprite::create("userInfo_line.png");
    line2->setPosition(Vec2(0, 835));
    line2->setAnchorPoint(Vec2(0, 0));
    line2->setScaleX(1.05);
    bkView->addChild(line2);
    
    ScrollView *scrollV=createScrollV();
    bkView->addChild(scrollV);
    scrollV->setInnerContainerSize(Size(visibleSize.width, (int)(11/5)*155+20));//设置内容大小
    for (int i=0; i<11; i++) {
        Menu *menu=createRectButton(Vec2(27, scrollV->getInnerContainerSize().height-143), i);
        scrollV->addChild(menu);
    }
    return layer;
}

ScrollView* MainScene::createScrollV(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0,100));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 730));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    return scrollView;
}

Menu*   MainScene::createRectButton(Vec2 point,int i){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto menuItem  = MenuItemImage::create("bk_bed.png","bk_bed.png",CC_CALLBACK_1(MainScene::menuLoginCallback, this));
    menuItem->setAnchorPoint(Vec2(0,0));
    menuItem->setPosition(Vec2(0,0));
    menuItem->setTag(i+100);
    menuItem->setScale(0.87);
    auto button = Menu::create();
    button->setAnchorPoint(Vec2(0,0));
    button->setPosition(point);
    button->addChild(menuItem);
    Size imageSize=menuItem->getContentSize()*0.87;
    int width=point.x+(imageSize.width+46)*i+imageSize.width;
            if (width<visibleSize.width) {
                button->setPosition(Vec2(point.x+(imageSize.width+46)*i, point.y));
            }else{
                button->setPosition(Vec2(point.x+(imageSize.width+46)*(i%5),point.y-((int)((width-point.x)/((imageSize.width+46)*5))*(imageSize.height+31))));
            }
    char strtest[500] = {0};
    sprintf(strtest,"bedNum%d.png",i%4+1);
    string numStr=strtest;
    auto num=Sprite::create(numStr);
    num->setPosition(Vec2(3, 30));
    num->setAnchorPoint(Vec2(0, 0));
    num->setScale(1.2);
    auto numLB = Label::createWithSystemFont(CCString::createWithFormat("%d",i)->getCString(),"Arial",35,Size(num->getContentSize().width,num->getContentSize().width),TextHAlignment::CENTER,TextVAlignment::CENTER);
    numLB->setPosition(Vec2(0,0));
    numLB->setTextColor(Color4B(255, 255, 255, 255));
    numLB->setAnchorPoint(Vec2(0, 0));
    num->addChild(numLB);
    menuItem->addChild(num);
    return button;
}



//门诊
Layer* MainScene::createOutPatientLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_outpatient.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    return layer;
}
//日历
Layer* MainScene::createCalendarLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_usercase.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    return layer;
}
//我的
Layer* MainScene::createSickInfoLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_sickInfo.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    return layer;
}


//实现CheckBox回调函数
void MainScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if (tag==5||tag==6) {
//临时病床和固定病床
            for (int i=0; i<2; i++) {
                CheckBox *box=boxVec->at(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
        }else if(tag>=0&&tag<=4){
//底部切换按钮的高亮
            for (int i=0; i<4; i++) {
                if (i!=tag) {
                    CheckBox * checkBox=(CheckBox*)this->getChildByTag(i);
                    checkBox->setSelected(false);
                }
            }
        }
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            if (tag==5||tag==6) {
            }else if(tag>=0&&tag<=4){
                //切换页面
                multLayer->switchTo(tag);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            if (tag==5||tag==6) {
               item->setSelected(true);
            }
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

void MainScene::menuLoginCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    int tag= item->getTag();
    
}

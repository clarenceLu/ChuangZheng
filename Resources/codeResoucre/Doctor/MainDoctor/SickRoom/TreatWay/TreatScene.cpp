//
//  TreatScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#include "TreatScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "OperationScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *TreatScene::createScene(){
    return TreatScene::create();
}
bool TreatScene::init(){
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
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width, visibleSize.height-190));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(0,40));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(TreatScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(TreatScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, 80));
    auto titleLB = Label::createWithSystemFont("手术","Arial",38,Size(visibleSize.width-200,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(54,5));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, 20));
    layout->addChild(judgeBtn);
    lv->insertCustomItem(layout,0);
    
    auto layout2=Layout::create();
    layout2->setBackGroundImageScale9Enabled(true);
    layout2->setBackGroundImage("alpha.png");
    layout2->setTouchEnabled(true);
    layout2->setContentSize(Size(visibleSize.width, 230));
    
    auto textfieldName=createBasicData(layout2, Vec2(54, 170), "支架", "填写");
    textfieldName->setTag(10);
    auto textfieldMedicine=createBasicData(layout2, Vec2(54, 90), "药物", "填写");
    textfieldMedicine->setTag(11);
    auto textfieldObserve=createBasicData(layout2, Vec2(54, 10), "观察", "填写");
    textfieldObserve->setTag(12);
    lv->insertCustomItem(layout2,1);
    
#pragma-在这里需要加判断-如果数据
    Layout *layout1=createBlueView("C3-C7", 0);
    lv->insertCustomItem(layout1, 1);
    Layout *layout3=createBlueView("C0-C2", 1);
    lv->insertCustomItem(layout3, 1);
    return true;
    
}


TextField*  TreatScene::createBasicData(Layout* bkView,Vec2 point,string name1,string name2){
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
    textFieldUser->addEventListener(CC_CALLBACK_2(TreatScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}



cocos2d::ui::Layout *TreatScene::createBlueView(string name,int tag){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layoutDic.insert(tag, layout);
    
    auto whiteView=createWhiteView(0, tag);
    layout->addChild(whiteView);
    
    layout->setContentSize(Size(visibleSize.width, 80));
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(50, 70));
    blueV->setAnchorPoint(Vec2(0, 1));
    blueV->setContentSize(Size(visibleSize.width-100, 60));
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
                                                     CC_CALLBACK_1(TreatScene::menuLoginCallback,this),
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
Sprite *TreatScene::createWhiteView(int type,int tag){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto whiteView=Sprite::create("alpha.png");
    whiteView->setPosition(Vec2(0, 0));
    whiteView->setAnchorPoint(Vec2(0, 0));
    whiteView->setVisible(false);
    whiteViewDic.insert(tag, whiteView);
    float   height=createMessage(Vec2(0, 0), "植入", "Cage,前路钢板", whiteView);
    float   height2=createMessage(Vec2(0, height), "切除", "锥体:C1-C3", whiteView);
    float   height3=0;
    if (tag==1) {
    height3=createMessage(Vec2(0, height2), "前路", "", whiteView);
    }else{
        height3=createMessage(Vec2(0, height2), "前路", "我是传奇", whiteView);
    }
    whiteView->setContentSize(Size(visibleSize.width, height3));
    whiteView->setTag(ceil(height3));
    
    return whiteView;
}
float TreatScene::createMessage(Vec2 origin,string title,string content,Sprite*whiteV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    //Data
    float height=10;
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",32,Size(visibleSize.width-200,0),TextHAlignment::LEFT,TextVAlignment::CENTER);
        height=contentLB->getContentSize().height+10;
        contentLB->setPosition(Point(67,origin.y+10));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        whiteV->addChild(contentLB);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",32,Size(visibleSize.width-200,40),TextHAlignment::LEFT,TextVAlignment::CENTER);
    titleLB->setPosition(Point(67,height+origin.y));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    whiteV->addChild(titleLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(60, origin.y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-120, 1.5));
    whiteV->addChild(lineV);
    return height+origin.y+50;
}



void TreatScene::createSelectBox(Vec2 origin,string name,int tag,float width,Sprite*bkView){
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
    acceptBox->addEventListener(CC_CALLBACK_2(TreatScene::checkBoxCallback,this));
    bkView->addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
}


cocos2d::Layer* TreatScene::createPromptLayer(std::string content){
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
    auto contentV = Sprite::create("bk_group_leader_prompt.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(120, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            this->removeChildByTag(2001);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(2001);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto contentLB=Label::createWithSystemFont(content,"Arial",36,Size(contentV->getContentSize().width-40,120),TextHAlignment::CENTER,TextVAlignment::CENTER);
    contentLB->setPosition(Vec2(20,120));
    contentLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(contentLB);
    
    return layer;
}




void TreatScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED");
            break;
        default:
            break;
    }
}
void TreatScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
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
            if (tag==10) {
                log("%d",tag);
              Layer * layer=createPromptLayer("确认需要修改支架吗");
                layer->setTag(2001);
                this->addChild(layer);
            }if (tag==11) {
                log("%d",tag);
                Layer * layer=createPromptLayer("确认需要修改药物吗");
                layer->setTag(2001);
                this->addChild(layer);
            }if (tag==12) {
                log("%d",tag);
                Layer * layer=createPromptLayer("确认需要修改观察吗");
                layer->setTag(2001);
                this->addChild(layer);
            }
            CCLOG("DETACH_WITH_IME");
            
            break;
            
    }
    
}


void TreatScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            if(index==0){
                auto SC=OperationScene::createScene();
                Director::getInstance()->pushScene(SC);
            }
            break;
        }
        default:
            break;
    }
}
void TreatScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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


void TreatScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    int tag= item->getTag();
    
//    Layout*   layout=(Layout*)lv->getItem(tag-100);
    Layout*   layout=layoutDic.at(tag-100);
    Sprite* blueV=(Sprite*)layout->getChildByTag(tag-100);
    log("index:%d,tag:%d",index,tag);
    
    Sprite*whiteV=whiteViewDic.at(tag-100);
#pragma-用于获取到whiteV的height
    float changeHeight=whiteV->getTag();
    
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

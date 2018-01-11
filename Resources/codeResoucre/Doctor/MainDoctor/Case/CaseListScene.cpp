//
//  CaseDoctorScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#include "CaseListScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "CaseHistoryScene.hpp"
#include "AddHospitalCaseScene.hpp"
#include "AddVisitCaseScene.hpp"
#include "AddOutpatientCaseScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *CaseListScene::createScene(){
    return CaseListScene::create();
}
bool CaseListScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_case_list.png");
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
    
    auto searchBtn=Button::create();
    searchBtn->loadTextures("btn_search.png", "btn_search.png");
    searchBtn->setPosition(Vec2(visibleSize.width-130, visibleSize.height-85));
    searchBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            
        default:
            break;
    }
    });
    this->addChild(searchBtn);
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_caselist_add.png", "btn_caselist_add.png");
    addBtn->setPosition(Vec2(visibleSize.width-50, visibleSize.height-85));
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=addCaseLayer();
            layer->setTag(1000);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    this->addChild(addBtn);
    
    ListView* lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width, visibleSize.height-160));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(0,0));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(CaseListScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(CaseListScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    Layout *layout=creatLayout(lv,1);
    Layout *layout2=creatLayout(lv,2);
    lv->insertCustomItem(layout,0);
    lv->insertCustomItem(layout2, 1);
    return true;
}

//新建病例
Layer* CaseListScene::addCaseLayer(){
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
    auto contentV = Sprite::create("bk_addCase.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,352));
    contentV->setContentSize(Size(508, 428));
    layer->addChild(contentV);
    auto cancelBtn=Button::create();
    cancelBtn->loadTextures("btn_addCase_cancel.png", "btn_addCase_cancel.png");
    cancelBtn->setPosition(Vec2(120, 15));
    cancelBtn->setAnchorPoint(Vec2(0,0));
    cancelBtn->setScale(0.87);
    cancelBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(1000);
        }
            break;
        default:
            break;
    }
    });
    contentV->addChild(cancelBtn);
    
    //住院
    auto hospitalBtn=Button::create();
    hospitalBtn->loadTextures("alpha.png", "alpha.png");
    hospitalBtn->setPosition(Vec2(visibleSize.width/2, 478));
    hospitalBtn->setScale9Enabled(true);
    hospitalBtn->setContentSize(Size(508, 42));
    hospitalBtn->setTitleText("新建住院病历");
    hospitalBtn->setTitleColor(Color3B(40, 40, 40));
    hospitalBtn->setTitleFontSize(40);
    hospitalBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto hospitalCase=AddHospitalCaseScene::createScene();
            Director::getInstance()->pushScene(hospitalCase);
        }
        default:
            break;
    }
    });
    layer->addChild(hospitalBtn);
    
    //门诊
    auto outpatientBtn=Button::create();
    outpatientBtn->loadTextures("alpha.png", "alpha.png");
    outpatientBtn->setPosition(Vec2(visibleSize.width/2, 563));
    outpatientBtn->setScale9Enabled(true);
    outpatientBtn->setContentSize(Size(508, 42));
    outpatientBtn->setTitleText("新建门诊病历");
    outpatientBtn->setTitleColor(Color3B(40, 40, 40));
    outpatientBtn->setTitleFontSize(40);
    outpatientBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto outpatientCase=AddOutpatientCaseScene::createScene();
            Director::getInstance()->pushScene(outpatientCase);
        }
        default:
            break;
    }
    });
    layer->addChild(outpatientBtn);
    
    //随访
    auto visitBtn=Button::create();
    visitBtn->loadTextures("alpha.png", "alpha.png");
    visitBtn->setPosition(Vec2(visibleSize.width/2, 648));
    visitBtn->setScale9Enabled(true);
    visitBtn->setContentSize(Size(508, 42));
    visitBtn->setTitleText("新建随访病历");
    visitBtn->setTitleColor(Color3B(40, 40, 40));
    visitBtn->setTitleFontSize(40);
    visitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto visitCase=AddVisitCaseScene::createScene();
            Director::getInstance()->pushScene(visitCase);
        }
        default:
            break;
    }
    });
    layer->addChild(visitBtn);
    return layer;
    
}


void CaseListScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            auto historyScene=CaseHistoryScene::createScene();
            Director::getInstance()->pushScene(historyScene);
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}
void CaseListScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

Layout *CaseListScene::creatLayout(ListView*superV,int i){
     Size visibleSize=Director::getInstance()->getVisibleSize();
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    
    string content="头后仰上身麻无敌无敌无敌无敌无敌";
    auto nameLB2 = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-280,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    float height=nameLB2->getContentSize().height;
    nameLB2->setPosition(Point(250,10));
    nameLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    nameLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(nameLB2);
    
    auto nameLB = Label::createWithSystemFont("印象：","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(160,10-41+height));
    nameLB->setTextColor(Color4B(91,144,230, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(nameLB);
    
    auto caseLB = Label::createWithSystemFont("病案号：","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    caseLB->setPosition(Point(160,10-41+height+50));
    caseLB->setTextColor(Color4B(91,144,230, 255));
    caseLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(caseLB);
     string caseStr="210706";
auto caseLB2=Label::createWithSystemFont(caseStr,"Arial",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    caseLB2->setPosition(Point(280,10-41+height+50));
    caseLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    caseLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(caseLB2);
    
    auto recommendLB = Label::createWithSystemFont("推荐人:","fonts/Marker Felt.ttf",30,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recommendLB->setPosition(Point(420,10-41+height+50));
    recommendLB->setTextColor(Color4B(91,144,230, 255));
    recommendLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(recommendLB);
    auto recommendLB2 = Label::createWithSystemFont("周大伟","fonts/Marker Felt.ttf",30,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recommendLB2->setPosition(Point(520,10-41+height+50));
    recommendLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    recommendLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(recommendLB2);
    
    auto headIV=Sprite::create("bk_headIV.png");
    headIV->setPosition(Vec2(16, height-41+15));
    headIV->setAnchorPoint(Vec2(0, 0));
    headIV->setContentSize(Size(122,130));
    layout->addChild(headIV);
    
    auto introduceLB = Label::createWithSystemFont("介绍人:","fonts/Marker Felt.ttf",30,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    introduceLB->setPosition(Point(420,10-41+height+100));
    introduceLB->setTextColor(Color4B(91,144,230, 255));
    introduceLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(introduceLB);
    auto introduceLB2 = Label::createWithSystemFont("周大伟","fonts/Marker Felt.ttf",30,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    introduceLB2->setPosition(Point(520,10-41+height+100));
    introduceLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    introduceLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(introduceLB2);
    
    auto idLB= Label::createWithSystemFont("张牧之","fonts/Marker Felt.ttf",38,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    idLB->setPosition(Point(160,10-41+height+50+50));
    idLB->setTextColor(Color4B(0,0,0, 255/3*2));
    idLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(idLB);
    
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, 1));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width, 1.5));
    layout->addChild(lineV);
//必须执行一下允许点击
    layout->setTouchEnabled(true);
    
    layout->setContentSize(Size(visibleSize.width, height+130));
  
    return layout;
    
}

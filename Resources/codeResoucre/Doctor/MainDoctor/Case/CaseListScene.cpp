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
    
 /*   auto searchBtn=Button::create();
    searchBtn->loadTextures("btn_search.png", "btn_search.png");
    searchBtn->setPosition(Vec2(visibleSize.width-130, visibleSize.height-85));
    searchBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            
        default:
            break;
    }
    });
    this->addChild(searchBtn);  */
    
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
    
    lv = ListView::create();
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
    
    return true;
}

void CaseListScene::onEnter(){
    Scene::onEnter();
    auto visibleSize=Director::getInstance()->getVisibleSize();
    lv->removeAllChildren();
    for (int i=0; i<this->infoData["data"].Size(); i++) {
     Layout *layout=creatLayout(lv,i);
    lv->insertCustomItem(layout,i);
    }
  
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
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            int index=listView->getCurSelectedIndex();
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            infoData["data"][index].Accept(writer);
            CCLOG("%s", buffer.GetString());
            
            
            auto historyScene=(CaseHistoryScene*)CaseHistoryScene::createScene();
            historyScene->patientId=infoData["data"][index]["paitientId"].GetString();
            historyScene->caseId=infoData["data"][index]["id"].GetString();
            Director::getInstance()->pushScene(historyScene);
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
    rapidjson::Value& data = this->infoData["data"][i];
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    
    string content="暂时不明病情";
    if (data["remark"].IsNull()) {
    }else{
        content=data["remark"].GetString();
    }
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
     string caseStr="";
    if (data["caseNo"].IsNull()) {
    }else{
        caseStr=data["caseNo"].GetString();
    }
auto caseLB2=Label::createWithSystemFont(caseStr,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    caseLB2->setPosition(Point(280,10-41+height+50));
    caseLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    caseLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(caseLB2);
    
    auto recommendLB = Label::createWithSystemFont("推荐人:","fonts/Marker Felt.ttf",30,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recommendLB->setPosition(Point(480,10-41+height+50));
    recommendLB->setTextColor(Color4B(91,144,230, 255));
    recommendLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(recommendLB);
    auto recommendLB2 = Label::createWithSystemFont("无","fonts/Marker Felt.ttf",30,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    recommendLB2->setPosition(Point(580,10-41+height+50));
    recommendLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    recommendLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(recommendLB2);
    
    auto headIV=Sprite::create("bk_headIV.png");
    headIV->setPosition(Vec2(16, height-41+15));
    headIV->setAnchorPoint(Vec2(0, 0));
    headIV->setContentSize(Size(122,130));
    layout->addChild(headIV);
    
    auto introduceLB = Label::createWithSystemFont("介绍人:","fonts/Marker Felt.ttf",30,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    introduceLB->setPosition(Point(480,10-41+height+100));
    introduceLB->setTextColor(Color4B(91,144,230, 255));
    introduceLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(introduceLB);
    auto introduceLB2 = Label::createWithSystemFont("无","fonts/Marker Felt.ttf",30,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    introduceLB2->setPosition(Point(580,10-41+height+100));
    introduceLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    introduceLB2->setAnchorPoint(Vec2(0, 0));
    layout->addChild(introduceLB2);
    
    string nameStr="佚名";
    if (data["name"].IsNull()) {
    }else{
        nameStr=data["name"].GetString();
    }
    auto idLB= Label::createWithSystemFont(nameStr,"fonts/Marker Felt.ttf",38,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
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

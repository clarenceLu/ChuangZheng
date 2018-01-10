//
//  ImpressionScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#include "ImpressionScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ImpressionScene::createScene(){
    return ImpressionScene::create();
}
bool ImpressionScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_impression.png");
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
    lv->setContentSize(Size(visibleSize.width, visibleSize.height-160));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(0,0));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ImpressionScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(ImpressionScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layer1 = createItemLayout(0,0,4,"退变");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createItemLayout(0,1,7,"畸形");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createItemLayout(0,2,2,"感染");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createItemLayout(0,3,5,"外伤");
    lv->insertCustomItem(layer4,3);
    
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, 150));
    auto confirmBtn=Button::create();
    confirmBtn->loadTextures("btn_impression_sure.png", "btn_impression_sure.png");
    confirmBtn->setPosition(Vec2(185, 40));
    confirmBtn->setAnchorPoint(Vec2(0, 0));
    confirmBtn->setScale(0.87);
    confirmBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    layout->addChild(confirmBtn);
    lv->insertCustomItem(layout,4);
    
    
    return true;
    
}

Layout *ImpressionScene::createItemLayout(int tag,int type,int index,string name){  //index指白色框里有几行数据
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, 80+index*60));
    
    
    Sprite *whiteView=createWhiteView(type, tag, index);
    layout->addChild(whiteView);
    
    
    auto blueV=Sprite::create("bk_impress_rect_blue.png");
    blueV->setPosition(Vec2(20, 10+60*index));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-40, 60));
    layout->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",40,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    
    auto box = CheckBox::create("box_select_rect.png","box_select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(blueV->getContentSize().width-60,10));
    box->setScale(0.87);
    box->setTag(1000+type);
    box->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(ImpressionScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueV->addChild(box);
    boxDic.insert(1000+type, box);
    
    return layout;
}

Sprite* ImpressionScene::createWhiteView(int type,int tag,int index){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_impress_rect_white.png");
    bkView->setPosition(Vec2(20, 10));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width-40, 60*(index+1)));
//用于隐藏
//    bkView->setVisible(false);
    if (type>=0&&type<3) {
        auto locationLB = Label::createWithSystemFont("位置","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        locationLB->setPosition(Point(20,60*(index-1)+10));
        locationLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        locationLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(locationLB);
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY())), "腰椎", 2, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-250, locationLB->getPositionY())), "胸椎", 1, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-395, locationLB->getPositionY())), "颈椎", 0, 70,bkView);
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(0, locationLB->getPositionY()-10));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setContentSize(Size(visibleSize.width-40, 1.5));
        bkView->addChild(lineV);
    }else if (type==3){
        auto locationLB = Label::createWithSystemFont("位置","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        locationLB->setPosition(Point(20,60*(index-1)+10));
        locationLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        locationLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(locationLB);
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY())), "上颈椎", 0, 100,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-300, locationLB->getPositionY())), "下颈椎", 1, 100,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY()-60)), "颈椎", 0, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-300, locationLB->getPositionY()-60)), "颈椎", 0, 70,bkView);
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(0, locationLB->getPositionY()-70));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setContentSize(Size(visibleSize.width-40, 1.5));
        bkView->addChild(lineV);
    }
    if (type==0) {
        auto diagnoseLB = Label::createWithSystemFont("诊断","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        diagnoseLB->setPosition(Point(20,60*(index-2)+10));
        diagnoseLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        diagnoseLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(diagnoseLB);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB->getPositionY())), "神经根型颈椎病", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-380, diagnoseLB->getPositionY())), "颈型颈椎病", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB->getPositionY()-60)), "食管型颈椎病", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-360, diagnoseLB->getPositionY()-60)), "脊椎型颈椎病", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB->getPositionY()-120)), "交感型颈椎病", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-360, diagnoseLB->getPositionY()-120)), "后纵韧带骨化症", 2, 240,bkView);
    } else   if (type==1) {
        auto LB = Label::createWithSystemFont("形态","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB->setPosition(Point(20,60*(index-2)+10));
        LB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY())), "侧凸", 2, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-250, LB->getPositionY())), "前凸", 1, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-395, LB->getPositionY())), "后凸", 0, 70,bkView);
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(0, LB->getPositionY()-10));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setContentSize(Size(visibleSize.width-40, 1.5));
        bkView->addChild(lineV);
        
        auto LB2 = Label::createWithSystemFont("病因","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB2->setPosition(Point(20,60*(index-3)+10));
        LB2->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB2->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB2);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY())), "神经纤维瘤性", 2, 220,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-380, LB2->getPositionY())), "特发性", 2, 160,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-60)), "先天性", 2, 110,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-260, LB2->getPositionY()-60)), "综合症型", 1, 180,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-450, LB2->getPositionY()-60)), "退变性", 0, 110,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-120)), "休门氏病", 2, 180,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-360, LB2->getPositionY()-120)), "强直性脊柱炎", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-180)), "创伤性", 2, 160,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-260, LB2->getPositionY()-180)), "神经肌源性", 2, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-240)), "脊柱结核或肿瘤", 2, 240,bkView);
    }else if (type==2) {
        auto LB = Label::createWithSystemFont("性质","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB->setPosition(Point(20,60*(index-2)+10));
        LB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY())), "SSI", 0, 90,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-270, LB->getPositionY())), "结核", 0, 90,bkView);
    }else if (type==3){
        auto LB = Label::createWithSystemFont("性质","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB->setPosition(Point(20,60*(index-3)+10));
        LB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY())), "脊柱损伤", 0, 180,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-300, LB->getPositionY())), "脊髓损伤", 0, 180,bkView);
         createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY()-60)), "创伤性椎间盘突出", 0, 260,bkView);
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(0, LB->getPositionY()-70));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setContentSize(Size(visibleSize.width-40, 1.5));
        bkView->addChild(lineV);
        
        auto locationLB = Label::createWithSystemFont("范围","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        locationLB->setPosition(Point(20,60*(index-5)+10));
        locationLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        locationLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(locationLB);
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY())), "后柱", 2, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-250, locationLB->getPositionY())), "中柱", 1, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-395, locationLB->getPositionY())), "前柱", 0, 70,bkView);
        
    }
    
    return bkView;
}

void ImpressionScene::createSelectBox(Vec2 origin,string name,int tag,float width,Sprite*bkView){
    auto acceptLB= Label::createWithSystemFont(name,"Arial",32,Size(width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    acceptLB->setPosition(origin);
    acceptLB->setTextColor(Color4B(0,0,0, 255/3*2));
    acceptLB->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(acceptLB);
    auto acceptBox = CheckBox::create("select_circle.png","btn_appearance_sure.png");
    acceptBox->setPosition(Vec2(origin.x+5,origin.y));
    acceptBox->setAnchorPoint(Vec2(0, 0));
    acceptBox->setScale(0.9);
    acceptBox->setTag(tag);
    acceptBox->setTouchEnabled(true);
    acceptBox->addEventListener(CC_CALLBACK_2(ImpressionScene::checkBoxCallback,this));
    bkView->addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
}


void ImpressionScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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


void ImpressionScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
void ImpressionScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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

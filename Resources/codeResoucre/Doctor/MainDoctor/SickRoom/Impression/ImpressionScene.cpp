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
#include "NetWrokMangerData.hpp"
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
        case ui::Widget::TouchEventType::ENDED:{
            pushDataToNetWork();
            Director::getInstance()->popScene();
        }
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
    box->setSelected(true);
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
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY())), "腰椎", type*100+2, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-250, locationLB->getPositionY())), "胸椎", type*100+1, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-395, locationLB->getPositionY())), "颈椎", type*100+0, 70,bkView);
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
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY())), "上颈椎", 301, 100,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-300, locationLB->getPositionY())), "下颈椎", 300, 100,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY()-60)), "腰椎", 303, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-300, locationLB->getPositionY()-60)), "胸椎", 302, 70,bkView);
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(0, locationLB->getPositionY()-70));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setContentSize(Size(visibleSize.width-40, 1.5));
        bkView->addChild(lineV);
    }
    if (type==0) {
        
        
        auto layer3 = LayerColor::create(Color4B(246, 247, 248, 255));
        layer3->setContentSize(Size(visibleSize.width-40, 180));
        layer3->setPosition(Point(0, 0));
        layer3->setAnchorPoint(Vec2(0, 0));
        auto backV3=Sprite::create("bk_impress_rect_white.png");
        backV3->setPosition(Vec2(0, 0));
        backV3->setAnchorPoint(Vec2(0, 0));
        backV3->setContentSize(layer3->getContentSize());
        layer3->addChild(backV3);
        auto diagnoseLB3 = Label::createWithSystemFont("诊断","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        diagnoseLB3->setPosition(Point(20,60*(index-2)+10));
        diagnoseLB3->setTextColor(Color4B(0, 0, 0, 255/3*2));
        diagnoseLB3->setAnchorPoint(Vec2(0, 0));
        backV3->addChild(diagnoseLB3);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB3->getPositionY())), "腰椎间盘突出症", 11, 240,backV3);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB3->getPositionY()-60)), "腰椎滑脱", 12, 240,backV3);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB3->getPositionY()-120)), "腰椎管狭窄症", 13, 240,backV3);
        
        auto layer2 = LayerColor::create(Color4B(246, 247, 248, 255));
        layer2->setContentSize(Size(visibleSize.width-40, 180));
        layer2->setPosition(Point(0, 0));
        layer2->setAnchorPoint(Vec2(0, 0));
        auto backV2=Sprite::create("bk_impress_rect_white.png");
        backV2->setPosition(Vec2(0, 0));
        backV2->setAnchorPoint(Vec2(0, 0));
        backV2->setContentSize(layer2->getContentSize());
        layer2->addChild(backV2);
        auto diagnoseLB2 = Label::createWithSystemFont("诊断","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        diagnoseLB2->setPosition(Point(20,60*(index-2)+10));
        diagnoseLB2->setTextColor(Color4B(0, 0, 0, 255/3*2));
        diagnoseLB2->setAnchorPoint(Vec2(0, 0));
        backV2->addChild(diagnoseLB2);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB2->getPositionY())), "胸椎间盘突出症", 9, 240,backV2);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB2->getPositionY()-60)), "黄韧带骨化症", 10, 240,backV2);
        
        auto layer1 = LayerColor::create(Color4B(246, 247, 248, 255));
        layer1->setContentSize(Size(visibleSize.width-40, 180));
        layer1->setPosition(Point(0, 0));
        layer1->setAnchorPoint(Vec2(0, 0));
        auto backV1=Sprite::create("bk_impress_rect_white.png");
        backV1->setPosition(Vec2(0, 0));
        backV1->setAnchorPoint(Vec2(0, 0));
        backV1->setContentSize(layer1->getContentSize());
        layer1->addChild(backV1);
        auto diagnoseLB = Label::createWithSystemFont("诊断","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        diagnoseLB->setPosition(Point(20,60*(index-2)+10));
        diagnoseLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        diagnoseLB->setAnchorPoint(Vec2(0, 0));
        backV1->addChild(diagnoseLB);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB->getPositionY())), "神经根型颈椎病", 4, 240,backV1);
        createSelectBox(Vec2(Point(visibleSize.width-380, diagnoseLB->getPositionY())), "颈型颈椎病", 3, 240,backV1);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB->getPositionY()-60)), "食管型颈椎病", 6, 240,backV1);
        createSelectBox(Vec2(Point(visibleSize.width-360, diagnoseLB->getPositionY()-60)), "脊椎型颈椎病", 5, 240,backV1);
        createSelectBox(Vec2(Point(visibleSize.width-105, diagnoseLB->getPositionY()-120)), "交感型颈椎病", 8, 240,backV1);
        createSelectBox(Vec2(Point(visibleSize.width-360, diagnoseLB->getPositionY()-120)), "后纵韧带骨化症", 7, 240,backV1);
        
        multLayer = LayerMultiplex::create(layer1,layer2,layer3,nullptr);
        bkView->addChild(multLayer, 0);
        multLayer->switchTo(0);
        
    } else   if (type==1) {
        auto LB = Label::createWithSystemFont("形态","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB->setPosition(Point(20,60*(index-2)+10));
        LB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY())), "侧凸", 105, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-250, LB->getPositionY())), "前凸", 104, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-395, LB->getPositionY())), "后凸", 103, 70,bkView);
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
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY())), "神经纤维瘤性", 107, 220,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-380, LB2->getPositionY())), "特发性", 106, 160,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-60)), "先天性", 110, 110,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-260, LB2->getPositionY()-60)), "综合症型", 109, 180,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-450, LB2->getPositionY()-60)), "退变性", 108, 110,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-120)), "休门氏病", 112, 180,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-360, LB2->getPositionY()-120)), "强直性脊柱炎", 111, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-180)), "创伤性", 114, 160,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-260, LB2->getPositionY()-180)), "神经肌源性", 113, 240,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB2->getPositionY()-240)), "脊柱结核或肿瘤", 115, 240,bkView);
    }else if (type==2) {
        auto LB = Label::createWithSystemFont("性质","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB->setPosition(Point(20,60*(index-2)+10));
        LB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY())), "SSI", 204, 90,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-270, LB->getPositionY())), "结核", 203, 90,bkView);
    }else if (type==3){
        auto LB = Label::createWithSystemFont("性质","Arial",32,Size(120,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        LB->setPosition(Point(20,60*(index-3)+10));
        LB->setTextColor(Color4B(0, 0, 0, 255/3*2));
        LB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(LB);
        createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY())), "脊柱损伤", 305, 180,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-300, LB->getPositionY())), "脊髓损伤", 304, 180,bkView);
         createSelectBox(Vec2(Point(visibleSize.width-105, LB->getPositionY()-60)), "创伤性椎间盘突出", 306, 260,bkView);
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
        createSelectBox(Vec2(Point(visibleSize.width-105, locationLB->getPositionY())), "后柱", 309, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-250, locationLB->getPositionY())), "中柱", 308, 70,bkView);
        createSelectBox(Vec2(Point(visibleSize.width-395, locationLB->getPositionY())), "前柱", 307, 70,bkView);
        
    }
    
    return bkView;
}

void ImpressionScene::createSelectBox(Vec2 origin,string name,int tag,float width,Sprite*bkView){
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
    acceptBox->addEventListener(CC_CALLBACK_2(ImpressionScene::checkBoxCallback,this));
    bkView->addChild(acceptBox);
    boxDic.insert(tag, acceptBox);
}


void ImpressionScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    log("tag :%d",tag);
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
if (tag>=0&&tag<=2) {
            for (int i=0; i<3; i++) {
                CheckBox *box=boxDic.at(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
    multLayer->switchTo(tag);
}
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            if (tag>=1000) {
                item->setSelected(true);
            }
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

std::string ImpressionScene::getJsonData(int type)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
if (type==0) {
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value array2(rapidjson::kArrayType);
    rapidjson::Value array3(rapidjson::kArrayType);
    for (int i=3; i<9; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
            array.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=9; i<11; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
            array2.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=11; i<14; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
           array3.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    document.AddMember("胸椎", array, allocator);
    document.AddMember("腰椎", array2, allocator);
    document.AddMember("颈椎", array3, allocator);
} else   if (type==1) {
        rapidjson::Value array(rapidjson::kArrayType);
        rapidjson::Value array2(rapidjson::kArrayType);
        rapidjson::Value array3(rapidjson::kArrayType);
    for (int i=100; i<103; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
           array.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=103; i<106; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
           array2.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=106; i<116; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
            array3.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
        document.AddMember("位置", array, allocator);
        document.AddMember("形态", array2, allocator);
        document.AddMember("病因", array3, allocator);
}else   if (type==2) {
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value array2(rapidjson::kArrayType);
    for (int i=200; i<203; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
          array.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=203; i<205; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
          array2.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    document.AddMember("位置", array, allocator);
    document.AddMember("性质", array2, allocator);
}else   if (type==3) {
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value array2(rapidjson::kArrayType);
    rapidjson::Value array3(rapidjson::kArrayType);
    for (int i=300; i<304; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
           array.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=304; i<307; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
          array2.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    for (int i=307; i<310; i++) {
        CheckBox*currentBox=boxDic.at(i);
        if (currentBox->getSelectedState()) {
           array3.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
        }
    }
    document.AddMember("位置", array, allocator);
    document.AddMember("性质", array2, allocator);
    document.AddMember("范围", array3, allocator);
}
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void ImpressionScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
     char jsonStr[1000]={0};
    sprintf(jsonStr,"%s;%s;%s;%s",getJsonData(0).c_str(),getJsonData(1).c_str(),getJsonData(2).c_str(),getJsonData(3).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"yx_tb;yx_jx;yx_gr;yx_ws",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(ImpressionScene::onHttpRequestCompleted, this),url);
    
    
//        string memberURL="http://czapi.looper.pro/web/getCaseById?caseId=109";
//        netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(ImpressionScene::onHttpRequestCompleted, this),nullptr);
    
}

void ImpressionScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}




string ImpressionScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 0:   case 100:     case 200:
            content="颈椎";
            break;
        case 1:   case 101:     case 201:
            content="胸椎";
            break;
        case 2:   case 102:     case 202:
            content="腰椎";
            break;
        case 3:
            content="颈型颈椎病";break;//神经根型颈椎病
        case 4:
            content="神经根型颈椎病";break;
        case 5:
            content="脊椎型颈椎病";break;
        case 6:
            content="食管型颈椎病";break;
        case 7:
            content="后纵韧带骨化症";break;
        case 8:
            content="交感型颈椎病";break;
        case 9:
            content="胸椎间盘突出症";break;
        case 10:
            content="黄韧带骨化症";break;
        case 11:
            content="腰椎间盘突出症";break;
        case 12:
            content="腰椎滑脱";break;
        case 13:
            content="腰椎管狭窄症";break;
        case 103:
            content="后凸";break;
        case 104:
            content="前凸";break;
        case 105:
            content="侧凸";break;
        case 106:
            content="特发性";break;
        case 107:
            content="神经纤维瘤性";break;
        case 108:
            content="退变性";break;
        case 109:
            content="综合症型";break;
        case 110:
            content="先天性";break;
        case 111:
            content="强直性脊柱炎";break;
        case 112:
            content="休门氏病";break;
        case 113:
            content="神经肌源性";break;
        case 114:
            content="创伤性";break;
        case 115:
            content="脊柱结核或肿瘤";break;
        case 203:
            content="结核";break;
        case 204:
            content="SSI";break;
        case 300:
            content="下颈椎";break;
        case 301:
            content="上颈椎";break;
        case 302:
            content="胸椎";break;
        case 303:
            content="腰椎";break;
        case 304:
            content="脊髓损伤";break;
        case 305:
            content="脊柱损伤";break;
        case 306:
            content="创伤性椎间盘突出";break;
        case 307:
            content="前柱";break;
        case 308:
            content="中柱";break;
        case 309:
            content="后柱";break;
            
            
        default:
            break;
    }
    return content;
}

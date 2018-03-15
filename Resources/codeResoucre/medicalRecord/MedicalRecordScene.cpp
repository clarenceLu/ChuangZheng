//
//  MedicalRecordScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/14.
//

#include "MedicalRecordScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MedicalRecordScene::createScene(){
    return MedicalRecordScene::create();
}
bool MedicalRecordScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_medicalRecord.png");
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
    bkView->addChild(backBtn);
    
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, 830));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,150));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MedicalRecordScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(MedicalRecordScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    
    auto layer1 = createLabel(0,"责任医生：","");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createLabel(1,"印象：","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createLabel(2,"症状","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createLabel(3,"体征","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createLabel(4,"影像","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createLabel(5,"评分","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createLabel(6,"治疗方式","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createLabel(7,"备注","多喝水");
    lv->insertCustomItem(layer8,7);
    
    return true;
}

void MedicalRecordScene::onEnter(){
    Scene::onEnter();
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    infoData.Accept(writer);
    CCLOG("%s", buffer.GetString());
    if (!infoData.IsNull()) {
        {
            const rapidjson::Value& val_form = infoData["data"];
            if(val_form.IsObject()){
                string content="";
                if (!val_form["yx_tb"].IsNull()) {
                    log("   yx_tb: %s", val_form["yx_tb"].GetString());
                    impressData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_tb"].GetString());
                    content=searchContentForInfoData(content, "退变（",impressData);        //遍历数据
                }
                if (!val_form["yx_jx"].IsNull()) {
                    formationData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_jx"].GetString());
                    content=searchContentForInfoData(content, "畸形（",formationData);
                }
                if (!val_form["yx_gr"].IsNull()) {
                    infectData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_gr"].GetString());
                    content=searchContentForInfoData(content, "感染（",infectData);
                }
                if (!val_form["yx_ws"].IsNull()) {
                    injuryData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_ws"].GetString());
                    content=searchContentForInfoData(content, "外伤（",injuryData);
                }
                lv->removeChildByTag(1);
                auto layer2 = createLabel(1,"印象：","");
                lv->insertCustomItem(layer2,1);
                
                string symptomContent="";
                if (!val_form["zz"].IsNull()) {
                    symptomData.Parse<rapidjson::kParseDefaultFlags>(val_form["zz"].GetString());
                    symptomContent=searchContentForInfoData(symptomContent, "主体（",symptomData);
                }
                lv->removeChildByTag(2);
                auto layer3 = createLabel(2,"症状","");
                lv->insertCustomItem(layer3,2);
            }
        }
    }
}

Layout* MedicalRecordScene::createLabel(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    
    float height=10;
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-150,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        height=contentLB->getContentSize().height+10;
        contentLB->setPosition(Point(37,10));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        layout->addChild(contentLB);
    }
    if (i==4) {
        //影像
   /*     ScrollView *imageScrol=createImageScroll(Vec2(35, 10), Size(visibleSize.width-150, 80));
        height=imageScrol->getContentSize().height+10;
        layout->addChild(imageScrol);    */
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
    
    return layout;
}

void MedicalRecordScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            break;
        }
        default:
            break;
    }
}
void MedicalRecordScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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


void MedicalRecordScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
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

std::string MedicalRecordScene::searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data){
    content.append(title);
    
    if (data.IsObject()) {
        for (auto j=data.MemberBegin(); j!=data.MemberEnd(); ++j) {
            auto key = (j->name).GetString();
            if (data[key].Size()) {
                content.append(key);
                content.append(":");
            }
            log("key:%s", key);
            for(auto i = 0; i < data[key].Size(); ++i){
                content.append(data[key][i].GetString());
                if (i==data[key].Size()-1&&j==data.MemberEnd()-1) {}else{content.append(" ");}
                log("%s", data[key][i].GetString());
            }
        }
    }else if(data.IsArray()){
        for(auto i = 0; i < data.Size(); ++i){
            content.append(data[i].GetString());
            content.append(" ");
            log("%s", data[i].GetString());
        }
    }
    content.append("）");
    log("%s",content.c_str());
    return content;
}


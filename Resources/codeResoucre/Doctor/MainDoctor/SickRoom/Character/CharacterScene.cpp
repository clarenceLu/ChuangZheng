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
#include "NetWrokMangerData.hpp"
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
    
    lv = ListView::create();
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
    return true;
    
}

void CharacterScene::onEnter()
{
    Scene::onEnter();
    lv->removeAllItems();
    auto layer1 = createMessageLayout(0,"外观异常","");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(1,"行动异常","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(2,"棘突压痛","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(3,"感觉异常","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(4,"肌张力异常","");
    lv->insertCustomItem(layer5,4);
    auto layer6 = createMessageLayout(5,"肌力异常","");
    lv->insertCustomItem(layer6,5);
    auto layer7 = createMessageLayout(6,"生理反射异常","");
    lv->insertCustomItem(layer7,6);
    auto layer8 = createMessageLayout(7,"病理反射","");
    lv->insertCustomItem(layer8,7);
    pushDataToNetWork();
}



Layout *CharacterScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTag(i);
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



#pragma-网络数据
void CharacterScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getCaseById?caseId=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str());
    netManeger->postHttpRequest(memberUrl,CC_CALLBACK_2(CharacterScene::onHttpRequestCompleted, this),nullptr);
}

void CharacterScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    // rapidjson::Document Jsondata;
    
    this->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
        
        
        if (this->infoData["status"].GetInt()==0) {
                const rapidjson::Value& val_form = infoData["data"];
                if(val_form.IsObject()){
                    string spineContent="";//感觉异常
                    if (!val_form["tz_jtyt"].IsNull()) {
                        senseData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_jtyt"].GetString());
                        spineContent=searchContentForInfoData(spineContent, "棘突：",senseData);
                    }
                    lv->removeChildByTag(2);
                    auto layer3 = createMessageLayout(2,"棘突压痛",spineContent);
                    lv->insertCustomItem(layer3,2);
                    
                    string senseContent="";//感觉异常
                    if (!val_form["tz_gjyc_gj"].IsNull()) {
                        senseData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_gjyc_gj"].GetString());
                        senseContent=searchContentForInfoData(senseContent, "",senseData);
                    }
                    lv->removeChildByTag(3);
                    auto layer4 = createMessageLayout(3,"感觉异常",senseContent);
                    lv->insertCustomItem(layer4,3);
                    
                    string symptomContent="";//行动异常
                    if (!val_form["tz_xdyc"].IsNull()) {
                        actionData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_xdyc"].GetString());
                        symptomContent=searchContentForInfoData(symptomContent, "感觉：",actionData);
                    }
                    lv->removeChildByTag(1);
                    auto layer2 = createMessageLayout(1,"行动异常",symptomContent);
                    lv->insertCustomItem(layer2,1);
                    
                    string dystoniaContent="";//肌张力异常
                    if(!val_form["tz_jzlyc_sz"].IsNull()){
                       dystoniaUpData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_jzlyc_sz"].GetString());
                        dystoniaContent=searchContentForInfoData(dystoniaContent, "上肢：", dystoniaUpData);
                    }dystoniaContent.append(" ");
                    if(!val_form["tz_jzlyc_xz"].IsNull()){
                        dystoniaDownData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_jzlyc_xz"].GetString());
                        dystoniaContent=searchContentForInfoData(dystoniaContent, "下肢：", dystoniaDownData);
                    }
                    lv->removeChildByTag(4);
                    auto layer5 = createMessageLayout(4,"肌张力异常",dystoniaContent);
                    lv->insertCustomItem(layer5,4);
                    
                    string appearanceContent="";   //"tz_wgyc;tz_wgyc_bdc;tz_wgyc_ws;tz_wgyc_gb_bz;tz_wgyc_gb_fq;tz_wgyc_gb_cw"
                    if(!val_form["tz_wgyc"].IsNull()){//外观异常
                        appearanceData1.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_wgyc"].GetString());
                        appearanceContent=searchContentForInfoData(appearanceContent, "外观：", appearanceData1);
                        appearanceContent.append(" ");
                    }
                    if(!val_form["tz_wgyc_bdc"].IsNull()){
                        appearanceData2.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_wgyc_bdc"].GetString());
                        appearanceContent=searchContentForInfoData(appearanceContent, "两侧不对称：", appearanceData2);
                        appearanceContent.append(" ");
                    }
                    if(!val_form["tz_wgyc_ws"].IsNull()){
                        appearanceData3.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_wgyc_ws"].GetString());
                        appearanceContent=searchContentForInfoData(appearanceContent, "肌肉萎缩：", appearanceData3);
                        appearanceContent.append(" ");
                    }
                    if(!val_form["tz_wgyc_gb_bz"].IsNull()){
                        appearanceData4.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_wgyc_gb_bz"].GetString());
                        appearanceContent=searchContentForInfoData(appearanceContent, "曲度变直：", appearanceData4);
                        appearanceContent.append(" ");
                    }
                    if(!val_form["tz_wgyc_gb_fq"].IsNull()){
                        appearanceData5.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_wgyc_gb_fq"].GetString());
                        appearanceContent=searchContentForInfoData(appearanceContent, "曲度反曲：", appearanceData5);
                        appearanceContent.append(" ");
                    }
                    if(!val_form["tz_wgyc_gb_cw"].IsNull()){
                        appearanceData6.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_wgyc_gb_cw"].GetString());
                        appearanceContent=searchContentForInfoData(appearanceContent, "曲度侧弯：", appearanceData6);
                        appearanceContent.append(" ");
                    }
                    lv->removeChildByTag(0);
                    auto layer1 = createMessageLayout(0,"外观异常",appearanceContent);
                    lv->insertCustomItem(layer1,0);
                    
                    string reflectAbnormalContent="";   //tz_slyc_he;tz_slyc_hs;tz_slyc_jgm;tz_slyc_fb;tz_slyc_tg;tz_slyc_gm;tz_slyc_qt;tz_slyc_gj
                    if(!val_form["tz_slyc_he"].IsNull()){//生理反射异常
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_he"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "肱二肌：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_hs"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_hs"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "肱三肌：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_jgm"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_jgm"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "桡骨膜：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_fb"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_fb"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "腹壁：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_tg"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_tg"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "提睾：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_gm"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_gm"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "肛门：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_qt"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_qt"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "膝跳：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    if(!val_form["tz_slyc_gj"].IsNull()){
                        reflectAbnormalData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_slyc_gj"].GetString());
                        reflectAbnormalContent=searchContentForInfoData(reflectAbnormalContent, "跟腱：", reflectAbnormalData);
                        reflectAbnormalContent.append(" ");
                    }
                    lv->removeChildByTag(6);
                    auto layer7 = createMessageLayout(6,"生理反射异常",reflectAbnormalContent);
                    lv->insertCustomItem(layer7,6);
                    
                    string reflectContent="";//病历反射异常 tz_ycfs_Hoffman;tz_ycfs_hzl;tz_ycfs_Babinski
                    if(!val_form["tz_ycfs_Hoffman"].IsNull()){
                        reflectData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_ycfs_Hoffman"].GetString());
                        reflectContent=searchContentForInfoData(reflectContent, "Hoffman症阳性：", reflectData);
                        reflectContent.append(" ");
                    }
                    if(!val_form["tz_ycfs_hzl"].IsNull()){
                        reflectData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_ycfs_hzl"].GetString());
                        reflectContent=searchContentForInfoData(reflectContent, "踝阵挛阳性：", reflectData);
                        reflectContent.append(" ");
                    }
                    if(!val_form["tz_ycfs_Babinski"].IsNull()){
                        reflectData.Parse<rapidjson::kParseDefaultFlags>(val_form["tz_ycfs_Babinski"].GetString());
                        reflectContent=searchContentForInfoData(reflectContent, "Babinski症阳性：", reflectData);
                    }
                    lv->removeChildByTag(7);
                    auto layer8 = createMessageLayout(7,"病理反射",reflectContent);
                    lv->insertCustomItem(layer8,7);
                    
                }
        }
        
    }
}

std::string CharacterScene::searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data){
    if (data.IsObject()) {
        content.append(title);
        for (auto j=data.MemberBegin(); j!=data.MemberEnd(); ++j) {
            auto key = (j->name).GetString();
            if (data[key].Size()) {
                content.append(key);
                content.append(":");
//仅修改棘突异常
                if (strcmp(title.c_str(), "棘突：")==0) {
                    content.append("（");
                }
            }
            log("key:%s", key);
            for(auto i = 0; i < data[key].Size(); ++i){
                content.append(data[key][i].GetString());
                if (i==data[key].Size()-1&&j==data.MemberEnd()-1) {}else{
                    content.append(" ");}
//仅修改棘突异常
                if (i==data[key].Size()-1) {
                    if (strcmp(title.c_str(), "棘突：")==0) {
                        content.append("）");
                    }
                }
                
                log("%s", data[key][i].GetString());
            }
        }
        content.append(";");
    }else if(data.IsArray()){
        if (data.Size()>0) {
            content.append(title);
        }
        for(auto i = 0; i < data.Size(); ++i){
            content.append(data[i].GetString());
            content.append(" ");
            log("%s", data[i].GetString());
        }
        if (data.Size()>0) {
            content.append(";");
        }
    }
    log("content：%s",content.c_str());
    return content;
}


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
#include "NetWrokMangerData.hpp"
#include "TreatWayScene.hpp"
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
    
    pushDataToNetWork();
    
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
    layout->setTag(tag);
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
    
    const rapidjson::Value& data = infoData["data"];
    float   height3=0;
    float   height=0;
    float   height2=0;
    float   height4=0;
    float   height5=0;
    float   height6=0;
    float   height7=0;
    float   height8=0;
    float   height9=0;
     float   height10=0;
    
    if (tag==0) {   //C0-2
        if(data.IsObject()){
//微创
            string content5="";
            if (!data["zlc0c2_wc_nj"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_wc_nj"].GetString());
                content5=searchContentForInfoData(content5, "",contentData);
            }
            if (strcmp(content5.c_str(), "")!=0) {
                height7=createMessage(Vec2(0, 0), "内镜：", content5, whiteView);
            }
            string content6="";
            if (!data["zlc0c2_wc_jp"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_wc_jp"].GetString());
                content6=searchContentForInfoData(content6, "",contentData);
            }
            if (strcmp(content6.c_str(), "")!=0) {
                height8=createMessage(Vec2(0, height7), "经皮选择：", content6, whiteView);
            }else{height8=height7;}
            string content7="";
            if (!data["zlc0c2_wc_td"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_wc_td"].GetString());
                content7=searchContentForInfoData(content7, "",contentData);
            }
            if (strcmp(content7.c_str(), "")!=0) {
                height10=createMessage(Vec2(0, height8), "通道选择：", content7, whiteView);
            }else{height10=height8;}
            if (height10!=0) {
                height9=createMessage(Vec2(0, height10), "微创", "", whiteView);
            }else{height9=height10;}
//后路
            string content3="";
            if (!data["zlc0c2_hl_zr"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_hl_zr"].GetString());
                content3=searchContentForInfoData(content3, "",contentData);
            }
            if (strcmp(content3.c_str(), "")!=0) {
                height4=createMessage(Vec2(0, height9), "植入", content3, whiteView);
            }
            string content4="";
            if (!data["zlc0c2_hl_qc"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_hl_qc"].GetString());
                content4=searchContentForInfoData(content4, "",contentData);
            }
            if (strcmp(content4.c_str(), "")!=0) {
                height5=createMessage(Vec2(0, height4), "切除", content4, whiteView);
            }else{height5=height4;}
            if (height5!=height9) {
                height6=createMessage(Vec2(0, height5), "后路", "", whiteView);
            }else{height6=height5;}
//前路
            string content2="";
            if (!data["zlc0c2_ql_zr"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_ql_zr"].GetString());
                content2=searchContentForInfoData(content2, "",contentData);
            }
            if (strcmp(content2.c_str(), "")!=0) {
        height=createMessage(Vec2(0, height6), "植入", content2, whiteView);
            }else{height=height6;}
            string content1="";
            if (!data["zlc0c2_ql_qc"].IsNull()) {
                rapidjson::Document contentData;
                contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc0c2_ql_qc"].GetString());
                content1=searchContentForInfoData(content1, "锥体：",contentData);
            }
             if (strcmp(content1.c_str(), "")!=0) {
         height2=createMessage(Vec2(0, height), "切除", content1, whiteView);
             }else{height2=height;}
            if (height2!=height6) {
        height3=createMessage(Vec2(0, height2), "前路", "", whiteView);
             }else{height3=height2;}
            
        }
}else if(tag==1){//C3-7
    if(data.IsObject()){
//微创
        string content5="";
        if (!data["zlc3c7_wc_nj"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_wc_nj"].GetString());
            content5=searchContentForInfoData(content5, "",contentData);
        }
        if (strcmp(content5.c_str(), "")!=0) {
            height7=createMessage(Vec2(0, 0), "内镜：", content5, whiteView);
        }
        string content6="";
        if (!data["zlc3c7_wc_jp"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_wc_jp"].GetString());
            content6=searchContentForInfoData(content6, "",contentData);
        }
        if (strcmp(content6.c_str(), "")!=0) {
            height8=createMessage(Vec2(0, height7), "经皮选择：", content6, whiteView);
        }else{height8=height7;}
        string content7="";
        if (!data["zlc3c7_wc_td"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_wc_td"].GetString());
            content7=searchContentForInfoData(content7, "",contentData);
        }
        if (strcmp(content7.c_str(), "")!=0) {
            height10=createMessage(Vec2(0, height8), "通道选择：", content7, whiteView);
        }else{height10=height8;}
        if (height10!=0) {
            height9=createMessage(Vec2(0, height10), "微创", "", whiteView);
        }else{height9=height10;}
//后路
        string content3="";
        if (!data["zlc3c7_hl_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_hl_zr"].GetString());
            content3=searchContentForInfoData(content3, "",contentData);
        }
        if (strcmp(content3.c_str(), "")!=0) {
            height4=createMessage(Vec2(0, height9), "植入", content3, whiteView);
        }
        string content4="";
        rapidjson::Document contentData2;
        if (!data["zlc3c7_hl_qc_zt"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_hl_qc_zt"].GetString());
            content4=searchContentForInfoData(content4, "椎板：",contentData2);
        }
        if (!data["zlc3c7_hl_qc_bzb"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_hl_qc_bzb"].GetString());
            content4=searchContentForInfoData(content4, "半椎板：",contentData2);
        }
        if (strcmp(content4.c_str(), "")!=0) {
            height5=createMessage(Vec2(0, height4), "切除", content4, whiteView);
        }else{height5=height4;}
        if (height5!=height9) {
            height6=createMessage(Vec2(0, height5), "后路", "", whiteView);
        }else{height6=height5;}
//前路
        string content2="";
        if (!data["zlc3c7_ql_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_ql_zr"].GetString());
            content2=searchContentForInfoData(content2, "",contentData);
        }
        if (strcmp(content2.c_str(), "")!=0) {
            height=createMessage(Vec2(0, height6), "植入", content2, whiteView);
        }else{height=height6;}
        string content1="";
        rapidjson::Document contentData;
        if (!data["zlc3c7_ql_qc_zt"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_ql_qc_zt"].GetString());
            content1=searchContentForInfoData(content1, "锥体：",contentData);}
        if (!data["zlc3c7_ql_qc_zjp"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlc3c7_ql_qc_zjp"].GetString());
            content1=searchContentForInfoData(content1, "锥间盘：",contentData);}
        if (strcmp(content1.c_str(), "")!=0) {
            height2=createMessage(Vec2(0, height), "切除", content1, whiteView);
        }else{height2=height;}
        if (height2!=height6) {
            height3=createMessage(Vec2(0, height2), "前路", "", whiteView);
        }else{height3=height2;}
    }
}else if(tag==2){//t1-6
    if(data.IsObject()){
//微创
        string content5="";
        if (!data["zlt1t6_wc_nj"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_wc_nj"].GetString());
            content5=searchContentForInfoData(content5, "",contentData);
        }
        if (strcmp(content5.c_str(), "")!=0) {
            height7=createMessage(Vec2(0, 0), "内镜：", content5, whiteView);
        }
        string content6="";
        if (!data["zlt1t6_wc_jp"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_wc_jp"].GetString());
            content6=searchContentForInfoData(content6, "",contentData);
        }
        if (strcmp(content6.c_str(), "")!=0) {
            height8=createMessage(Vec2(0, height7), "经皮选择：", content6, whiteView);
        }else{height8=height7;}
        string content7="";
        if (!data["zlt1t6_wc_td"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_wc_td"].GetString());
            content7=searchContentForInfoData(content7, "",contentData);
        }
        if (strcmp(content7.c_str(), "")!=0) {
            height10=createMessage(Vec2(0, height8), "通道选择：", content7, whiteView);
        }else{height10=height8;}
        if (height10!=0) {
            height9=createMessage(Vec2(0, height10), "微创", "", whiteView);
        }else{height9=height10;}
//后路
        string content3="";
        if (!data["zlt1t6_ql_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_ql_zr"].GetString());
            content3=searchContentForInfoData(content3, "",contentData);
        }
        if (strcmp(content3.c_str(), "")!=0) {
            height4=createMessage(Vec2(0, height9), "植入", content3, whiteView);
        }
        string content4="";
        rapidjson::Document contentData2;
        if (!data["zlt1t6_hl_qc_zt"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_hl_qc_zt"].GetString());
            content4=searchContentForInfoData(content4, "椎板：",contentData2);
        }
        if (!data["zlt1t6_hl_qc_bzb"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_hl_qc_bzb"].GetString());
            content4=searchContentForInfoData(content4, "半椎板：",contentData2);
        }
        if (strcmp(content4.c_str(), "")!=0) {
            height5=createMessage(Vec2(0, height4), "切除", content4, whiteView);
        }else{height5=height4;}
        if (height5!=height9) {
            height6=createMessage(Vec2(0, height5), "后路", "", whiteView);
        }else{height6=height5;}
//前路
        string content2="";
        if (!data["zlt1t6_ql_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_ql_zr"].GetString());
            content2=searchContentForInfoData(content2, "",contentData);
        }
        if (strcmp(content2.c_str(), "")!=0) {
            height=createMessage(Vec2(0, height6), "植入", content2, whiteView);
        }else{height=height6;}
        string content1="";
        rapidjson::Document contentData;
        if (!data["zlt1t6_ql_qc_zt"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_ql_qc_zt"].GetString());
            content1=searchContentForInfoData(content1, "锥体：",contentData);}
        if (!data["zlt1t6_ql_qc_zjp"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt1t6_ql_qc_zjp"].GetString());
            content1=searchContentForInfoData(content1, "锥间盘：",contentData);}
        if (strcmp(content1.c_str(), "")!=0) {
            height2=createMessage(Vec2(0, height), "切除", content1, whiteView);
        }else{height2=height;}
        if (height2!=height6) {
            height3=createMessage(Vec2(0, height2), "前路", "", whiteView);
        }else{height3=height2;}
    }
}else if(tag==3){//t7-12
    if(data.IsObject()){
        //微创
        string content5="";
        if (!data["zlt7t12_wc_nj"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_wc_nj"].GetString());
            content5=searchContentForInfoData(content5, "",contentData);
        }
        if (strcmp(content5.c_str(), "")!=0) {
            height7=createMessage(Vec2(0, 0), "内镜：", content5, whiteView);
        }
        string content6="";
        if (!data["zlt7t12_wc_jp"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_wc_jp"].GetString());
            content6=searchContentForInfoData(content6, "",contentData);
        }
        if (strcmp(content6.c_str(), "")!=0) {
            height8=createMessage(Vec2(0, height7), "经皮选择：", content6, whiteView);
        }else{height8=height7;}
        string content7="";
        if (!data["zlt7t12_wc_td"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_wc_td"].GetString());
            content7=searchContentForInfoData(content7, "",contentData);
        }
        if (strcmp(content7.c_str(), "")!=0) {
            height10=createMessage(Vec2(0, height8), "通道选择：", content7, whiteView);
        }else{height10=height8;}
        if (height10!=0) {
            height9=createMessage(Vec2(0, height10), "微创", "", whiteView);
        }else{height9=height10;}
//后路
        string content3="";
        if (!data["zlt7t12_hl_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_hl_zr"].GetString());
            content3=searchContentForInfoData(content3, "",contentData);
        }
        if (strcmp(content3.c_str(), "")!=0) {
            height4=createMessage(Vec2(0, height9), "植入", content3, whiteView);
        }
        string content4="";
        rapidjson::Document contentData2;
        if (!data["zlt7t12_hl_qc_zt"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_hl_qc_zt"].GetString());
            content4=searchContentForInfoData(content4, "椎板：",contentData2);
        }
        if (!data["zlt7t12_hl_qc_bzb"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_hl_qc_bzb"].GetString());
            content4=searchContentForInfoData(content4, "半椎板：",contentData2);
        }
        if (strcmp(content4.c_str(), "")!=0) {
            height5=createMessage(Vec2(0, height4), "切除", content4, whiteView);
        }else{height5=height4;}
        if (height5!=height9) {
            height6=createMessage(Vec2(0, height5), "后路", "", whiteView);
        }else{height6=height5;}
//前路
        string content2="";
        if (!data["zlt7t12_ql_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_ql_zr"].GetString());
            content2=searchContentForInfoData(content2, "",contentData);
        }
        if (strcmp(content2.c_str(), "")!=0) {
            height=createMessage(Vec2(0, height6), "植入", content2, whiteView);
        }else{height=height6;}
        string content1="";
        rapidjson::Document contentData;
        if (!data["zlt7t12_ql_qc_zt"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_ql_qc_zt"].GetString());
            content1=searchContentForInfoData(content1, "锥体：",contentData);}
        if (!data["zlt7t12_ql_qc_zjp"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zlt7t12_ql_qc_zjp"].GetString());
            content1=searchContentForInfoData(content1, "锥间盘：",contentData);}
        if (strcmp(content1.c_str(), "")!=0) {
            height2=createMessage(Vec2(0, height), "切除", content1, whiteView);
        }else{height2=height;}
        if (height2!=height6) {
            height3=createMessage(Vec2(0, height2), "前路", "", whiteView);
        }else{height3=height2;}
    }
}else if(tag==4){//L1-s1
    if(data.IsObject()){
//微创
        string content5="";
        if (!data["zll1s1_wc_nj"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_wc_nj"].GetString());
            content5=searchContentForInfoData(content5, "",contentData);
        }
        if (strcmp(content5.c_str(), "")!=0) {
            height7=createMessage(Vec2(0, 0), "内镜：", content5, whiteView);
        }
        string content6="";
        if (!data["zll1s1_wc_jp"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_wc_jp"].GetString());
            content6=searchContentForInfoData(content6, "",contentData);
        }
        if (strcmp(content6.c_str(), "")!=0) {
            height8=createMessage(Vec2(0, height7), "经皮选择：", content6, whiteView);
        }else{height8=height7;}
        string content7="";
        if (!data["zll1s1_wc_td"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_wc_td"].GetString());
            content7=searchContentForInfoData(content7, "",contentData);
        }
        if (strcmp(content7.c_str(), "")!=0) {
            height10=createMessage(Vec2(0, height8), "通道选择：", content7, whiteView);
        }else{height10=height8;}
        if (height10!=0) {
            height9=createMessage(Vec2(0, height10), "微创", "", whiteView);
        }else{height9=height10;}
//后路
        string content3="";
        if (!data["zll1s1_hl_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_hl_zr"].GetString());
            content3=searchContentForInfoData(content3, "",contentData);
        }
        if (strcmp(content3.c_str(), "")!=0) {
            height4=createMessage(Vec2(0, height9), "植入", content3, whiteView);
        }
        string content4="";
        rapidjson::Document contentData2;
        if (!data["zll1s1_hl_qc_zb"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_hl_qc_zb"].GetString());
            content4=searchContentForInfoData(content4, "椎板：",contentData2);
        }
        if (!data["zll1s1_hl_qc_zjp"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_hl_qc_zjp"].GetString());
            content4=searchContentForInfoData(content4, "椎间盘：",contentData2);
        }
        if (!data["zll1s1_hl_qc_bzb"].IsNull()) {
            contentData2.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_hl_qc_bzb"].GetString());
            content4=searchContentForInfoData(content4, "半椎板：",contentData2);
        }
        if (strcmp(content4.c_str(), "")!=0) {
            height5=createMessage(Vec2(0, height4), "切除", content4, whiteView);
        }else{height5=height4;}
        if (height5!=height9) {
            height6=createMessage(Vec2(0, height5), "后路", "", whiteView);
        }else{height6=height5;}
        //前路
        string content2="";
        if (!data["zll1s1_ql_zr"].IsNull()) {
            rapidjson::Document contentData;
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_ql_zr"].GetString());
            content2=searchContentForInfoData(content2, "",contentData);
        }
        if (strcmp(content2.c_str(), "")!=0) {
            height=createMessage(Vec2(0, height6), "植入", content2, whiteView);
        }else{height=height6;}
        string content1="";
        rapidjson::Document contentData;
        if (!data["zll1s1_ql_qc_zt"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_ql_qc_zt"].GetString());
            content1=searchContentForInfoData(content1, "锥体：",contentData);}
        if (!data["zll1s1_ql_qc_zjp"].IsNull()) {
            contentData.Parse<rapidjson::kParseDefaultFlags>(data["zll1s1_ql_qc_zjp"].GetString());
            content1=searchContentForInfoData(content1, "锥间盘：",contentData);}
        if (strcmp(content1.c_str(), "")!=0) {
            height2=createMessage(Vec2(0, height), "切除", content1, whiteView);
        }else{height2=height;}
        if (height2!=height6) {
            height3=createMessage(Vec2(0, height2), "前路", "", whiteView);
        }else{height3=height2;}
    }
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


cocos2d::Layer* TreatScene::createPromptLayer(std::string content,int index){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    currentTextFieldTag=index;
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
            string titleStr="";
            if (currentTextFieldTag==10) {
                titleStr="zl_zj";//支架
            }else if(currentTextFieldTag==11){
                titleStr="zl_yw";//药物
            }else{
                titleStr="zl_gc";//观察
            }
            string contentStr="";
            auto textField=(TextField*)textFieldDic.at(currentTextFieldTag);
            if (textField->getStringLength()) {
                contentStr=textField->getString();
            }
            pushTextFieldToNetWork(titleStr,contentStr);
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
        case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
            CCLOG("ATTACH_WITH_IME");
            break;
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            
            CCLOG("DELETE_BACKWARD");
            break;
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            if (tag==10) {
                log("%d",tag);
              Layer * layer=createPromptLayer("确认需要修改支架吗",10);
                layer->setTag(2001);
                this->addChild(layer);
            }if (tag==11) {
                log("%d",tag);
                Layer * layer=createPromptLayer("确认需要修改药物吗",11);
                layer->setTag(2001);
                this->addChild(layer);
            }if (tag==12) {
                log("%d",tag);
                Layer * layer=createPromptLayer("确认需要修改观察吗",12);
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
//                auto SC=OperationScene::createScene();
                auto SC=TreatWayScene::createScene();
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


#pragma-网络数据
void TreatScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getCaseById?caseId=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str());
    netManeger->postHttpRequest(memberUrl,CC_CALLBACK_2(TreatScene::onHttpRequestCompleted, this),nullptr);
}

void TreatScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
             const rapidjson::Value& data = infoData["data"];
//layout
            auto layout2=Layout::create();
            layout2->setBackGroundImageScale9Enabled(true);
            layout2->setBackGroundImage("alpha.png");
            layout2->setTouchEnabled(true);
            layout2->setContentSize(Size(visibleSize.width, 230));
            auto textfieldName=createBasicData(layout2, Vec2(54, 170), "支架", "填写");
            if (!data["zl_zj"].IsNull()) {
                textfieldName->setString(data["zl_zj"].GetString());
            }
            textfieldName->setTag(10);
            textFieldDic.insert(10, textfieldName);
            auto textfieldMedicine=createBasicData(layout2, Vec2(54, 90), "药物", "填写");
            if (!data["zl_yw"].IsNull()) {
                textfieldMedicine->setString(data["zl_yw"].GetString());
            }
            textfieldMedicine->setTag(11);
            textFieldDic.insert(11, textfieldMedicine);
            auto textfieldObserve=createBasicData(layout2, Vec2(54, 10), "观察", "填写");
            if (!data["zl_gc"].IsNull()) {
                textfieldObserve->setString(data["zl_gc"].GetString());
            }
            textfieldObserve->setTag(12);
            textFieldDic.insert(12, textfieldObserve);
            lv->insertCustomItem(layout2,1);
            
            
            Layout *layout6=createBlueView("L1-S1", 4);
            lv->insertCustomItem(layout6, 1);
            Layout *layout5=createBlueView("T7-T12", 3);
            lv->insertCustomItem(layout5, 1);
            Layout *layout4=createBlueView("T1-T6", 2);
            lv->insertCustomItem(layout4, 1);
            Layout *layout1=createBlueView("C3-C7", 1);
            lv->insertCustomItem(layout1, 1);
            Layout *layout3=createBlueView("C0-C2", 0);
            lv->insertCustomItem(layout3, 1);
        }
    }
}


void TreatScene::pushTextFieldToNetWork(std::string title,std::string content){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),title.c_str(),content.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(TreatScene::onHttpRequestCompleted2, this),url);
}

void TreatScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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
    }
}



std::string TreatScene::searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data){
        if (data.IsObject()) {
            content.append(title);
            for (auto j=data.MemberBegin(); j!=data.MemberEnd(); ++j) {
                auto key = (j->name).GetString();
                if (data[key].Size()) {
                    content.append(key);
                    content.append(":");
                }
                log("key:%s", key);
                for(auto i = 0; i < data[key].Size(); ++i){
                    content.append(data[key][i].GetString());
                    if (i==data[key].Size()-1&&j==data.MemberEnd()-1) {}else{
                        content.append(" ");}
                    
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


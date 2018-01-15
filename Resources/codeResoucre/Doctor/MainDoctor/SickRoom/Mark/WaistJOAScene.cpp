//
//  WaistJOAScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#include "WaistJOAScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *WaistJOAScene::createScene(){
    return WaistJOAScene::create();
}
bool WaistJOAScene::init(){
    if (!Scene::init()) {
        return false;
    }
#pragma-ValueVector加入数据
    createData();
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_waist_JOA.png");
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
            log("NeckJOA sure");
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    scrollV=createTableView(Vec2(0, visibleSize.height-170), Size(visibleSize.width, visibleSize.height-200));
    this->addChild(scrollV);
    return true;
}
ScrollView* WaistJOAScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setAnchorPoint(Vec2(0, 1));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    moveView=Sprite::create("alpha.png");
    moveView->setAnchorPoint(Vec2(0, 1));
    moveView->setContentSize(visibleSize);
    scrollView->addChild(moveView);
    
//    auto titleLB = Label::createWithSystemFont("主观症状（9分）","Arial",40,Size(visibleSize.width-100,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
//    titleLB->setPosition(Point(40,visibleSize.height));
//    titleLB->setTextColor(Color4B(91, 144, 229, 255));
//    titleLB->setAnchorPoint(Vec2(0, 1));
//    moveView->addChild(titleLB);
    
    float pointY1 =createPopUpView(Vec2(40, visibleSize.height-10), moveView, "下腰背痛(主观)",0,1);
    float pointY3 =createPopUpView(Vec2(40, pointY1+60*4), moveView, "腿痛兼/或麻刺痛(主观)",4,1);
    float pointY4 =createPopUpView(Vec2(40, pointY3+60*4), moveView, "步态(主观)",8,1);
    float pointY5 =createPopUpView(Vec2(40, pointY4+60*4), moveView, "直腿抬高(加强)试验(临床)",12,1);
    float pointY6 =createPopUpView(Vec2(40, pointY5+60*3), moveView, "感觉障碍(临床)",15,1);
     float pointY7 =createPopUpView(Vec2(40, pointY6+60*3), moveView, "运动障碍(临床)",18,1);
     float pointY8 =createPopUpView(Vec2(40, pointY7+60*3), moveView, "平卧翻身(日常ADL)",21,1);
     float pointY9 =createPopUpView(Vec2(40, pointY8+60*3), moveView, "站立(大约1小时)(日常ADL)",24,1);
     float pointY10 =createPopUpView(Vec2(40, pointY9+60*3), moveView, "洗漱(日常ADL)",27,1);
     float pointY11 =createPopUpView(Vec2(40, pointY10+60*3), moveView, "前屈(日常ADL)",30,1);
     float pointY12=createPopUpView(Vec2(40, pointY11+60*3), moveView, "坐位(日常ADL)",33,1);
     float pointY13=createPopUpView(Vec2(40, pointY12+60*3), moveView, "举重物(日常ADL)",36,1);
     float pointY14=createPopUpView(Vec2(40, pointY13+60*3), moveView, "行走(日常ADL)",39,1);
    float pointY2 =createPopUpView(Vec2(40, pointY14+60*3), moveView, "膀胱功能(-6-0分)",42,1);
    
#warning -在这里设置没有用，因为当innerSize<contentSize，以contentSize为准
    if (visibleSize.height>visibleSize.height-20-pointY2) {
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height-20-pointY2));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY2));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }else{
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY2));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }
    log("%f,%f",scrollView->getInnerContainerSize().height,visibleSize.height-20-pointY2);
    return scrollView;
}


float WaistJOAScene::createPopUpView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
#pragma-ValueMap取值
    ValueVector vect=map1.at(name).asValueVector();
    long index=vect.size();
    
    auto wholeV=Sprite::create("alpha.png");
    wholeV->setPosition(Vec2(0,0));
    wholeV->setAnchorPoint(Vec2(0, 0));
    wholeV->setContentSize(Size(visibleSize.width, point.y));
    wholeV->setTag(200+tag);
    bkView->addChild(wholeV);
#pragma-Map<int, Sprite*> wholeDic加入字典
    wholeDic.insert(tag, wholeV);
    
    auto whiteV=Sprite::create("usercase_whiterect.png");
    whiteV->setPosition(Vec2(point.x, point.y-60*(index+1)));
    whiteV->setAnchorPoint(Vec2(0, 0));
    whiteV->setContentSize(Size(visibleSize.width-80, 60*(index+1)));
    whiteV->setTag(tag+200);
    whiteV->setVisible(false);
    wholeV->addChild(whiteV);
#pragma-ValueVector取值
    for (int i=0; i<index; i++) {
        auto whiteStr= vect.at(i).asString();
        creatBlueLabelView(Vec2(0,60*i), whiteV,whiteStr,tag+i,type);
    }
    
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(point.x, point.y-60));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-80, 60));
    wholeV->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(500,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    
    
    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_appearance_down.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_appearance_up.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(WaistJOAScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(Vec2(blueV->getContentSize().width-60,20));  //设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setTag(100+tag);
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    blueV->addChild(box);
    
    return point.y-(index+1)*60-20;
    
}

float WaistJOAScene::creatBlueLabelView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",25,Size(500,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(point.x+20, point.y));
    userName->setTextColor(Color4B(0, 0, 0, 255/2));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    if (type==1) {
        auto box = CheckBox::create("btn_appearance_unsure.png","btn_appearance_sure.png");
        //设置CheckBox的位置
        box->setPosition(Vec2(bkView->getContentSize().width-60,point.y+10));
        box->setScale(0.87);
        box->setTag(tag);
        box->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box->setTouchEnabled(true);
        box->addEventListener(CC_CALLBACK_2(WaistJOAScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box);
        boxDic.insert(tag, box);
    }else if (type==2){
        auto box = CheckBox::create("btn_group_leader_delete.png","btn_group_leader_delete.png");
        //设置CheckBox的位置
        box->setPosition(Vec2(bkView->getContentSize().width-50,point.y+20));
        box->setScale(0.87);
        box->setTag(tag);
        box->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box->setTouchEnabled(true);
        box->addEventListener(CC_CALLBACK_2(WaistJOAScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box);
    }
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, point.y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.89);
    bkView->addChild(lineV);
    return point.y-20;
}




void WaistJOAScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    int tag= item->getTag();
    if (index==1) {
#pragma-Map<int, Sprite*> wholeDic取值
        auto wholeV = (Sprite*)wholeDic.at(tag-100);
        auto whiteV=(Sprite*)wholeV->getChildByTag(tag+100);
        whiteV->setVisible(true);
        //判断是否需要移动下方的sprite
        std::vector<int> mapKeyVec;
        mapKeyVec = wholeDic.keys();
        sort(mapKeyVec.begin(), mapKeyVec.end());
        for(int nextTag : mapKeyVec)
        {
            //                    log("%d",nextTag);
            if (nextTag>tag-100) {
                auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y-whiteV->getContentSize().height+60));
            }
        }
        //                log("原先的%f",scrollV->getInnerContainerSize().height);
        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height+whiteV->getContentSize().height-60));
        log("现在的%f",scrollV->getInnerContainerSize().height);
        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
        scrollV->setInnerContainerPosition(Vec2(0, 60-whiteV->getContentSize().height));
        log("%f",scrollV->getInnerContainerPosition().y);
        if (scrollV->getInnerContainerSize().height<visibleSize.height-190) {
            //用于调整scrollView的contentOffset
            scrollV->setContentSize(Size(visibleSize.width, scrollV->getInnerContainerSize().height));
        }else{
            scrollV->setContentSize(Size(visibleSize.width, visibleSize.height-190));
        }
    }else if (index==0){
        auto wholeV = (Sprite*)wholeDic.at(tag-100);
        auto whiteV=wholeV->getChildByTag(tag+100);
        whiteV->setVisible(false);
        //判断是否需要移动下方的sprite
        std::vector<int> mapKeyVec;
        mapKeyVec = wholeDic.keys();
        sort(mapKeyVec.begin(), mapKeyVec.end());
        for(int nextTag : mapKeyVec)
        {
            log("%d",nextTag);
            if (nextTag>tag-100) {
                auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y+whiteV->getContentSize().height-60));
            }
        }
        scrollV->setContentSize(Size(visibleSize.width, scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
        //用于调整scrollView的contentOffset
        
    }
    
}

//实现CheckBox回调函数
void WaistJOAScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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
            if (tag>=0&&tag<4) {
                for (int i=0; i<4; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=4&&tag<8) {
                for (int i=4; i<8; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=8&&tag<12) {
                for (int i=8; i<12; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=12&&tag<15) {
                for (int i=12; i<15; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=15&&tag<18) {
                for (int i=15; i<18; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=18&&tag<21) {
                for (int i=18; i<21; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=21&&tag<24) {
                for (int i=21; i<24; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=24&&tag<27) {
                for (int i=24; i<27; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=27&&tag<30) {
                for (int i=27; i<30; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=30&&tag<33) {
                for (int i=30; i<33; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=33&&tag<36) {
                for (int i=33; i<36; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=36&&tag<39) {
                for (int i=36; i<39; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=39&&tag<42) {
                for (int i=39; i<42; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=42&&tag<45) {
                for (int i=42; i<45; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
        {
        }
            break;
        default:
            break;
    }
}

void  WaistJOAScene::createData(){
    ValueVector vector1;
    vector1.push_back(Value("3分：无任何疼痛"));
    vector1.push_back(Value("2分：偶尔轻微疼痛"));
    vector1.push_back(Value("1分：频发的轻微疼痛或偶发严重疼痛"));
    vector1.push_back(Value("0分：频发或持续的严重疼痛"));
    string key1 = "下腰背痛(主观)";
    ValueVector vector2;
    vector2.push_back(Value("3分：无任何疼痛"));
    vector2.push_back(Value("2分：偶尔轻微疼痛"));
    vector2.push_back(Value("1分：频发的轻微疼痛或偶发严重疼痛"));
    vector2.push_back(Value("0分：频发或持续的严重疼痛"));
    string key2 = "腿痛兼/或麻刺痛(主观)";
    ValueVector vector3;
    vector3.push_back(Value("3分：正常"));
    vector3.push_back(Value("2分：即使感肌肉无力，也可步行超过500米"));
    vector3.push_back(Value("1分：步行小于500米，即出现腿痛，刺痛，无力"));
    vector3.push_back(Value("0分：步行小于100米，即出现腿痛，刺痛，无力"));
    string key3 = "步态(主观)";
    ValueVector vector4;
    vector4.push_back(Value("2分：正常"));
    vector4.push_back(Value("1分：30度-70度"));
    vector4.push_back(Value("0分：<30度"));
    string key4 = "直腿抬高(加强)试验(临床)";
    ValueVector vector5;
    vector5.push_back(Value("2分：正常"));
    vector5.push_back(Value("1分：轻度障碍"));
    vector5.push_back(Value("0分：明显障碍"));
    string key5 = "感觉障碍(临床)";
    ValueVector vector6;
    vector6.push_back(Value("2分：正常(肌力5级)"));
    vector6.push_back(Value("1分：轻度无力(肌力4级)"));
    vector6.push_back(Value("0分：明显无力(肌力0-3级)"));
    string key6 = "运动障碍(临床)";
    ValueVector vector7;
    vector7.push_back(Value("2分：正常"));
    vector7.push_back(Value("1分：轻度受限"));
    vector7.push_back(Value("0分：明显受限"));
    string key7 = "平卧翻身(日常ADL)";
    ValueVector vector8;
    vector8.push_back(Value("2分：正常"));
    vector8.push_back(Value("1分：轻度受限"));
    vector8.push_back(Value("0分：明显受限"));
    string key8 = "站立(大约1小时)(日常ADL)";
    ValueVector vector9;
    vector9.push_back(Value("2分：正常"));
    vector9.push_back(Value("1分：轻度受限"));
    vector9.push_back(Value("0分：明显受限"));
    string key9 = "洗漱(日常ADL)";
    ValueVector vector10;
    vector10.push_back(Value("2分：正常"));
    vector10.push_back(Value("1分：轻度受限"));
    vector10.push_back(Value("0分：明显受限"));
    string key10 = "前屈(日常ADL)";
    ValueVector vector11;
    vector11.push_back(Value("2分：正常"));
    vector11.push_back(Value("1分：轻度受限"));
    vector11.push_back(Value("0分：明显受限"));
    string key11 = "坐位(日常ADL)";
    ValueVector vector12;
    vector12.push_back(Value("2分：正常"));
    vector12.push_back(Value("1分：轻度受限"));
    vector12.push_back(Value("0分：明显受限"));
    string key12 = "举重物(日常ADL)";
    ValueVector vector13;
    vector13.push_back(Value("2分：正常"));
    vector13.push_back(Value("1分：轻度受限"));
    vector13.push_back(Value("0分：明显受限"));
    string key13 = "行走(日常ADL)";
    ValueVector vector14;
    vector14.push_back(Value("0分：正常"));
    vector14.push_back(Value("-3分：轻度受限"));
    vector14.push_back(Value("-6分：明显受限（尿失留，尿失禁）"));
    string key14 = "膀胱功能(-6-0分)";
    
#pragma-ValueMap加入数据
    map1[key1] = Value(vector1).asValueVector();
    map1[key2]=Value(vector2).asValueVector();
    map1[key3]=Value(vector3).asValueVector();
    map1[key4]=Value(vector4).asValueVector();
    map1[key5]=Value(vector5).asValueVector();
    map1[key6]=Value(vector6).asValueVector();
    map1[key7]=Value(vector7).asValueVector();
    map1[key8]=Value(vector8).asValueVector();
    map1[key9]=Value(vector9).asValueVector();
    map1[key10]=Value(vector10).asValueVector();
    map1[key11]=Value(vector11).asValueVector();
    map1[key12]=Value(vector12).asValueVector();
    map1[key13]=Value(vector13).asValueVector();
    map1[key14]=Value(vector14).asValueVector();
}

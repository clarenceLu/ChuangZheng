//
//  VisitCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#include "VisitCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "MarkScene.hpp"
#include "DocUserInfoScene.hpp"
#include "ImpressionScene.hpp"
#include "TreatScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *VisitCaseScene::createScene(){
    return VisitCaseScene::create();
}
bool VisitCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_visit_case.png");
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
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(VisitCaseScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(VisitCaseScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    
    auto layer1 = createMessageLayout(0,"张牧之   男  60       856","");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(1,"印象","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(2,"影像","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(3,"评分","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(4,"治疗方式","");
    lv->insertCustomItem(layer5,4);
  
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    auto textFieldTop=Sprite::create("textfield_top.png");
    textFieldTop->setPosition(Vec2(0,0));
    textFieldTop->setContentSize(Size(visibleSize.width-40, 30));
    textFieldTop->setAnchorPoint(Vec2(0, 0));
    layout->addChild(textFieldTop);
    auto titleLB = Label::createWithSystemFont("说明","Arial",38,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,10+textFieldTop->getContentSize().height));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    layout->setContentSize(Size(visibleSize.width, textFieldTop->getContentSize().height+70));
    lv->insertCustomItem(layout,5);
    
    auto layout2 = Layout::create();
    layout2->setBackGroundImageScale9Enabled(true);
    layout2->setBackGroundImage("textfield_center.png");
    layout2->setTouchEnabled(true);
    auto textFieldContent= TextField::create("一百字以内","Arial",35);
    textFieldContent->setMaxLength(240);
    //用于多行输入
    textFieldContent->ignoreContentAdaptWithSize(false);
    textFieldContent->setTouchSize(Size(visibleSize.width-80,300));
    textFieldContent->setPosition(Vec2(20,0));
    textFieldContent->setAnchorPoint(Vec2(0,0));
    textFieldContent->setContentSize(Size(visibleSize.width-80,300));
    textFieldContent->setTextColor(Color4B::BLACK);
    textFieldContent->setPlaceHolderColor(Color4B::GRAY);
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->setTag(110);
    textFieldContent->addEventListener(CC_CALLBACK_2(VisitCaseScene::eventCallBack, this));
    layout2->addChild(textFieldContent);
     layout2->setContentSize(Size(visibleSize.width-40, 300));
    lv->insertCustomItem(layout2,6);
    
    auto layout3 = Layout::create();
    layout3->setBackGroundImageScale9Enabled(true);
    layout3->setBackGroundImage("alpha.png");
    layout3->setTouchEnabled(true);
    auto textFieldBottom=Sprite::create("textfield_bottom.png");
    textFieldBottom->setPosition(Vec2(0, 0));
    textFieldBottom->setAnchorPoint(Vec2(0, 0));
    textFieldBottom->setContentSize(Size(visibleSize.width-40, 30));
    layout3->addChild(textFieldBottom);
    layout3->setContentSize(Size(visibleSize.width, textFieldBottom->getContentSize().height));
    lv->insertCustomItem(layout3,7);
    
    
    return true;
}
void VisitCaseScene::createTextFieldView(Layout* contentV){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto textFieldBottom=Sprite::create("textfield_bottom.png");
    textFieldBottom->setPosition(Vec2(23, 0));
    textFieldBottom->setAnchorPoint(Vec2(0, 0));
    textFieldBottom->setScale(0.87);
    contentV->addChild(textFieldBottom);
}


Layout *VisitCaseScene::createMessageLayout(int i,string title,string content){
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
    if (i==2) {
        //影像
        ScrollView *imageScrol=createImageScroll(Vec2(35, 10), Size(visibleSize.width-150, 80));
        height=imageScrol->getContentSize().height+10;
        layout->addChild(imageScrol);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-150,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height));
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
    layout->setContentSize(Size(visibleSize.width, height+70));
    
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, height+10));
    layout->addChild(judgeBtn);
    
    
    return layout;
}


ScrollView* VisitCaseScene::createImageScroll(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);//方向
    scrollView->setScrollBarEnabled(false);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    for (int i=0; i<10; i++) {
#pragma-修改影像的图片
        auto imageV1=Sprite::create("HelloWorld.png");
        imageV1->setPosition(Vec2((visibleSize.height+20)*i, 0));
        imageV1->setAnchorPoint(Vec2(0, 0));
        imageV1->setContentSize(Size(visibleSize.height, visibleSize.height));
        scrollView->addChild(imageV1);
    }
    scrollView->setInnerContainerSize(Size((visibleSize.height+20)*10, visibleSize.height));
    
    return scrollView;
}

void VisitCaseScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
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
            if (index==3) {//评分
                auto markSC=MarkScene::createScene();
                Director::getInstance()->pushScene(markSC);
            }else if(index==0){
                auto SC=DocUserInfoScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==1){
                auto SC=ImpressionScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==4){
                auto SC=TreatScene::createScene();
                Director::getInstance()->pushScene(SC);
            }
            
            break;
        }
        default:
            break;
    }
}
void VisitCaseScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
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
void VisitCaseScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    TextField*textField=(TextField*)pSender;
    string  text=textField->getString();
    Size size=calculateFontSize(text.c_str());
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:{
            CCLOG("INSERT_TEXT");
            if (size.height>=300) {
#pragma-调整输入框的高度
            Layout*  layout=(Layout*)lv->getItem(6);
                layout->setContentSize(Size(visibleSize.width-40, size.height));
               textField->setContentSize(Size(visibleSize.width-80,size.height));
                onEnter();
            }
        }
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("DETACH_WITH_IME");
            
            break;
    }
}
Size VisitCaseScene::calculateFontSize(const char *str )
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    std::string tempString = str;
    log("tempString = %s",tempString.c_str());
    size_t computeCount = tempString.size();       //如果字符串很长每次抽取100个字符来计算size；
    Size size = Size(0,0);
    for (int i = 0; i<computeCount ;)  
    {
        std::string substring =  tempString.substr(i,1);
        if ((substring.c_str()[0] & 0x80 )!=0) //是汉字
        {
            substring = tempString.substr(i , 3);
            i += 3;
        }
        else
        {
            i++;
        }
        //CCLog("subString  = %s ",substring.c_str());
        auto tempLabel = LabelTTF::create(substring.c_str(),"",25);
        tempLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
        Size tmpLsize = tempLabel->getContentSize();
        size.width+=tmpLsize.width;
    }
    
    float fHeight= 0;
    float chartWidth=visibleSize.width-80;
    if( size.width > chartWidth)//大于容器的宽度
    {
        fHeight = (size.width / 200 );//计算需要多少行
    }
    int nHeight =  ceil(fHeight);
    
    if (nHeight == 0)
    {
        nHeight = 1;
    }
    
    Size labelSize ;
    if (size.width < chartWidth)
    {
        labelSize = Size(size.width,nHeight*32);//计算容器的Size
    }
    else
    {
        labelSize = Size(chartWidth,nHeight*28);
    }
    
    //CCLog("labelSize = (%f, %f)",labelSize.width ,labelSize.height);
    //CCLog("fHeight = %f  nHeight = %d " ,fHeight ,nHeight);
    return labelSize;
}

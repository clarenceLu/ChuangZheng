//
//  SelectCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/3.
//

#include "SelectCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "UserCaseScene.hpp"
#include "json/rapidjson.h"
#include "json/document.h"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *SelectCaseScene::createScene(){
    return SelectCaseScene::create();
}
bool SelectCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    getJsonData("selfBuildCase.json",_VecData);
    auto bkView=Sprite::create("bk_selectCase.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    this->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-90));
    backBtn->setScale(0.87);
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto scrollV=createScrollV();
    this->addChild(scrollV,2);
    Size scrollSize=scrollV->getInnerContainerSize();
#pragma -第一个选择框
    auto blueView1=Sprite::create("select_blue_rect.png");
    blueView1->setPosition(20,scrollSize.height-10);
    blueView1->setAnchorPoint(Vec2(0, 1));
    blueView1->cocos2d::Node::setScale(0.86);
    scrollV->addChild(blueView1);
    auto title1LB = Label::createWithSystemFont("手脚、胳膊、腿：","fonts/Marker Felt.ttf",45,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    title1LB->setPosition(Point(20,320));
    title1LB->setAnchorPoint(Vec2(0, 1));
    blueView1->addChild(title1LB);
    
    auto caseCheckBox1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    caseCheckBox1->setPosition(Vec2(20,20));
    caseCheckBox1->setTag(0);
    caseCheckBox1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    caseCheckBox1->setTouchEnabled(true);
    caseCheckBox1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueView1->addChild(caseCheckBox1);
    auto content1LB = Label::createWithSystemFont("不舒服，怎么动、放什么姿势都难受","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    content1LB->setPosition(Vec2(80,10));
    content1LB->setTextColor(Color4B(77, 77, 77, 255));
    content1LB->setAnchorPoint(Vec2(0, 0));
    blueView1->addChild(content1LB);
    
    
    auto caseCheckBox2 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    caseCheckBox2->setPosition(Vec2(20,80));
    caseCheckBox2->setTag(1);
    caseCheckBox2->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    caseCheckBox2->setTouchEnabled(true);
    caseCheckBox2->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueView1->addChild(caseCheckBox2);
    auto content2LB = Label::createWithSystemFont("僵硬，活动不灵活","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    content2LB->setPosition(Vec2(80,70));
    content2LB->setTextColor(Color4B(77, 77, 77, 255));
    content2LB->setAnchorPoint(Vec2(0, 0));
    blueView1->addChild(content2LB);
    
    auto caseCheckBox3 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    caseCheckBox3->setPosition(Vec2(20,140));
    caseCheckBox3->setTag(2);
    caseCheckBox3->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    caseCheckBox3->setTouchEnabled(true);
    caseCheckBox3->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueView1->addChild(caseCheckBox3);
    auto content3LB = Label::createWithSystemFont("会没力气","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    content3LB->setPosition(Vec2(80,130));
    content3LB->setTextColor(Color4B(77, 77, 77, 255));
    content3LB->setAnchorPoint(Vec2(0, 0));
    blueView1->addChild(content3LB);
    
    auto caseCheckBox4 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    caseCheckBox4->setPosition(Vec2(20,200));
    caseCheckBox4->setTag(3);
    caseCheckBox4->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    caseCheckBox4->setTouchEnabled(true);
    caseCheckBox4->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueView1->addChild(caseCheckBox4);
    auto content4LB = Label::createWithSystemFont("会麻","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    content4LB->setPosition(Vec2(80,190));
    content4LB->setTextColor(Color4B(77, 77, 77, 255));
    content4LB->setAnchorPoint(Vec2(0, 0));
    blueView1->addChild(content4LB);
    
#pragma -第二个选择框
    auto whiteView1=Sprite::create("select_white_rect.png");
    whiteView1->setPosition(20,scrollSize.height-320);
    whiteView1->setAnchorPoint(Vec2(0, 1));
    whiteView1->cocos2d::Node::setScale(0.86);
    scrollV->addChild(whiteView1);
    auto w1_content1 = Label::createWithSystemFont("肩膀、后背疼","fonts/Marker Felt.ttf",35,Size(220,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w1_content1->setPosition(Point(20,15));
    w1_content1->setTextColor(Color4B(79, 79, 79, 255));
    w1_content1->setAnchorPoint(Vec2(0, 0));
    whiteView1->addChild(w1_content1);
    auto w1_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w1_box1->setPosition(Vec2(240,20));
    w1_box1->setTag(10);
    w1_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w1_box1->setTouchEnabled(true);
    w1_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView1->addChild(w1_box1);
    auto w1_content2 = Label::createWithSystemFont("胳膊疼","fonts/Marker Felt.ttf",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w1_content2->setPosition(Point(20,65));
    w1_content2->setTextColor(Color4B(79, 79, 79, 255));
    w1_content2->setAnchorPoint(Vec2(0, 0));
    whiteView1->addChild(w1_content2);
    auto w1_box2 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w1_box2->setPosition(Vec2(140,75));
    w1_box2->setTag(11);
    w1_box2->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w1_box2->setTouchEnabled(true);
    w1_box2->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView1->addChild(w1_box2);
    auto w1_content3 = Label::createWithSystemFont("腿疼","fonts/Marker Felt.ttf",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w1_content3->setPosition(Point(200,65));
    w1_content3->setTextColor(Color4B(79, 79, 79, 255));
    w1_content3->setAnchorPoint(Vec2(0, 0));
    whiteView1->addChild(w1_content3);
    auto w1_box3 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w1_box3->setPosition(Vec2(280,75));
    w1_box3->setTag(12);
    w1_box3->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w1_box3->setTouchEnabled(true);
    w1_box3->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView1->addChild(w1_box3);
    auto w1_content4 = Label::createWithSystemFont("腰疼","fonts/Marker Felt.ttf",35,Size(90,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w1_content4->setPosition(Point(350,65));
    w1_content4->setTextColor(Color4B(79, 79, 79, 255));
    w1_content4->setAnchorPoint(Vec2(0, 0));
    whiteView1->addChild(w1_content4);
    auto w1_box4 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w1_box4->setPosition(Vec2(430,75));
    w1_box4->setTag(13);
    w1_box4->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w1_box4->setTouchEnabled(true);
    w1_box4->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView1->addChild(w1_box4);
    auto w1_content5 = Label::createWithSystemFont("脖子疼","fonts/Marker Felt.ttf",35,Size(120,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w1_content5->setPosition(Point(490,65));
    w1_content5->setTextColor(Color4B(79, 79, 79, 255));
    w1_content5->setAnchorPoint(Vec2(0, 0));
    whiteView1->addChild(w1_content5);
    auto w1_box5 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w1_box5->setPosition(Vec2(610,75));
    w1_box5->setTag(14);
    w1_box5->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w1_box5->setTouchEnabled(true);
    w1_box5->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView1->addChild(w1_box5);
    
#pragma -第三个选择框
    auto whiteView2=Sprite::create("select_white_rect.png");
    whiteView2->setPosition(20,scrollSize.height-460);
    whiteView2->setAnchorPoint(Vec2(0, 1));
    whiteView2->cocos2d::Node::setScale(0.86);
    whiteView2->setContentSize(Size(blueView1->getContentSize().width, 420));
    scrollV->addChild(whiteView2);
    auto blue2View=Sprite::create("usercase_bluerect.png");
    blue2View->setPosition(20,scrollSize.height-460);
    blue2View->setAnchorPoint(Vec2(0, 1));
    blue2View->cocos2d::Node::setScale(0.86);
    blue2View->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(blue2View);
    auto title2LB = Label::createWithSystemFont("您的疼痛最符合以下哪种说法：","fonts/Marker Felt.ttf",45,Size(blueView1->getContentSize().width-40,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    title2LB->setPosition(Point(20,70));
    title2LB->setAnchorPoint(Vec2(0, 1));
    blue2View->addChild(title2LB);
    
    auto w2_Box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w2_Box1->setPosition(Vec2(20,20));
    w2_Box1->setTag(20);
    w2_Box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w2_Box1->setTouchEnabled(true);
    w2_Box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView2->addChild(w2_Box1);
    auto w2_content1LB = Label::createWithSystemFont("以上都不是","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w2_content1LB->setPosition(Vec2(80,10));
    w2_content1LB->setTextColor(Color4B(77, 77, 77, 255));
    w2_content1LB->setAnchorPoint(Vec2(0, 0));
    whiteView2->addChild(w2_content1LB);
    
    
    auto w2_Box2 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w2_Box2->setPosition(Vec2(20,80));
    w2_Box2->setTag(21);
    w2_Box2->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w2_Box2->setTouchEnabled(true);
    w2_Box2->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView2->addChild(w2_Box2);
    auto w2_content2LB = Label::createWithSystemFont("有一点最疼，自己能找到那个位置","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w2_content2LB->setPosition(Vec2(80,70));
    w2_content2LB->setTextColor(Color4B(77, 77, 77, 255));
    w2_content2LB->setAnchorPoint(Vec2(0, 0));
    whiteView2->addChild(w2_content2LB);
    
    auto w2_Box3 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w2_Box3->setPosition(Vec2(20,140));
    w2_Box3->setTag(22);
    w2_Box3->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w2_Box3->setTouchEnabled(true);
    w2_Box3->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView2->addChild(w2_Box3);
    auto w2_content3LB = Label::createWithSystemFont("有一片地方都疼，不敢碰，一碰更疼","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w2_content3LB->setPosition(Vec2(80,130));
    w2_content3LB->setTextColor(Color4B(77, 77, 77, 255));
    w2_content3LB->setAnchorPoint(Vec2(0, 0));
    whiteView2->addChild(w2_content3LB);
    
    auto w2_Box4 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w2_Box4->setPosition(Vec2(20,200));
    w2_Box4->setTag(23);
    w2_Box4->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w2_Box4->setTouchEnabled(true);
    w2_Box4->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView2->addChild(w2_Box4);
    auto w2_content4LB = Label::createWithSystemFont("有一片地方都疼，敲一敲会舒服点","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w2_content4LB->setPosition(Vec2(80,190));
    w2_content4LB->setTextColor(Color4B(77, 77, 77, 255));
    w2_content4LB->setAnchorPoint(Vec2(0, 0));
    whiteView2->addChild(w2_content4LB);
    
    auto w2_Box5 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w2_Box5->setPosition(Vec2(20,260));
    w2_Box5->setTag(24);
    w2_Box5->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w2_Box5->setTouchEnabled(true);
    w2_Box5->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView2->addChild(w2_Box5);
    auto w2_content5LB = Label::createWithSystemFont("疼起来就像过电，一条线疼下去","fonts/Marker Felt.ttf",35,Size(580,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w2_content5LB->setPosition(Vec2(80,250));
    w2_content5LB->setTextColor(Color4B(77, 77, 77, 255));
    w2_content5LB->setAnchorPoint(Vec2(0, 0));
    whiteView2->addChild(w2_content5LB);
    
#pragma-第四个选择框
    auto whiteView3=Sprite::create("select_white_rect.png");
    whiteView3->setPosition(20,scrollSize.height-840);
    whiteView3->setAnchorPoint(Vec2(0, 1));
    whiteView3->cocos2d::Node::setScale(0.86);
    whiteView3->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(whiteView3);
    
    auto w3_content1 = Label::createWithSystemFont("腿疼、腰疼走不远","fonts/Marker Felt.ttf",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w3_content1->setPosition(Point(20,15));
    w3_content1->setTextColor(Color4B(79, 79, 79, 255));
    w3_content1->setAnchorPoint(Vec2(0, 0));
    whiteView3->addChild(w3_content1);
    auto w3_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w3_box1->setPosition(Vec2(320,20));
    w3_box1->setTag(30);
    w3_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w3_box1->setTouchEnabled(true);
    w3_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView3->addChild(w3_box1);
    
#pragma-第五个选择框
    auto whiteView4=Sprite::create("select_white_rect.png");
    whiteView4->setPosition(20,scrollSize.height-940);
    whiteView4->setAnchorPoint(Vec2(0, 1));
    whiteView4->cocos2d::Node::setScale(0.86);
    whiteView4->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(whiteView4);
    
    auto w4_content1 = Label::createWithSystemFont("走个              米就要休息，休息一下能再走","fonts/Marker Felt.ttf",35,Size(blueView1->getContentSize().width-40,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w4_content1->setPosition(Point(20,15));
    w4_content1->setTextColor(Color4B(79, 79, 79, 255));
    w4_content1->setAnchorPoint(Vec2(0, 0));
    whiteView4->addChild(w4_content1);
    auto meterBtn=Button::create();
    meterBtn->loadTextures("select_line.png", "select_line.png");
    meterBtn->setTitleText("5000+");
    meterBtn->setTitleFontSize(40);
    meterBtn->setTitleColor(Color3B(178, 238, 94));
    meterBtn->setPosition(Vec2(95, 10));
    meterBtn->setAnchorPoint(Vec2(0, 0));
    meterBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
#pragma -在这里选择能走多少路
        }
        default:
            break;
    }
    });
    whiteView4->addChild(meterBtn);
#pragma-第六个选择框
    auto whiteView5=Sprite::create("select_white_rect.png");
    whiteView5->setPosition(20,scrollSize.height-1040);
    whiteView5->setAnchorPoint(Vec2(0, 1));
    whiteView5->cocos2d::Node::setScale(0.86);
    whiteView5->setContentSize(Size(blueView1->getContentSize().width, 130));
    scrollV->addChild(whiteView5);
    
    auto w5_content1 = Label::createWithSystemFont("腿软、使不上力气；或者腿抬不起来；或者脚踩在地上像踩在棉花堆上","fonts/Marker Felt.ttf",35,Size(blueView1->getContentSize().width-40,100),TextHAlignment::LEFT,TextVAlignment::CENTER);
    w5_content1->setPosition(Point(20,15));
    w5_content1->setMaxLineWidth(20);
    w5_content1->setTextColor(Color4B(79, 79, 79, 255));
    w5_content1->setAnchorPoint(Vec2(0, 0));
    whiteView5->addChild(w5_content1);
    auto w5_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w5_box1->setPosition(Vec2(500,20));
    w5_box1->setTag(50);
    w5_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w5_box1->setTouchEnabled(true);
    w5_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView5->addChild(w5_box1);
    
#pragma-第七个选择框
    auto whiteView6=Sprite::create("select_white_rect.png");
    whiteView6->setPosition(20,scrollSize.height-1180);
    whiteView6->setAnchorPoint(Vec2(0, 1));
    whiteView6->cocos2d::Node::setScale(0.86);
    whiteView6->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(whiteView6);
    
    auto w6_content1 = Label::createWithSystemFont("胸上、腰上感觉像扎了一个带子","fonts/Marker Felt.ttf",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w6_content1->setPosition(Point(20,15));
    w6_content1->setTextColor(Color4B(79, 79, 79, 255));
    w6_content1->setAnchorPoint(Vec2(0, 0));
    whiteView6->addChild(w6_content1);
    auto w6_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w6_box1->setPosition(Vec2(520,20));
    w6_box1->setTag(60);
    w6_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w6_box1->setTouchEnabled(true);
    w6_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView6->addChild(w6_box1);
#pragma-第八个选择框
    auto whiteView7=Sprite::create("select_white_rect.png");
    whiteView7->setPosition(20,scrollSize.height-1180);
    whiteView7->setAnchorPoint(Vec2(0, 1));
    whiteView7->cocos2d::Node::setScale(0.86);
    whiteView7->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(whiteView7);
    
    auto w7_content1 = Label::createWithSystemFont("胸上、腰上感觉像扎了一个带子","fonts/Marker Felt.ttf",35,Size(500,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w7_content1->setPosition(Point(80,15));
    w7_content1->setTextColor(Color4B(79, 79, 79, 255));
    w7_content1->setAnchorPoint(Vec2(0, 0));
    whiteView7->addChild(w7_content1);
    auto w7_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w7_box1->setPosition(Vec2(20,20));
    w7_box1->setTag(70);
    w7_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w7_box1->setTouchEnabled(true);
    w7_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView7->addChild(w7_box1);
    
#pragma-第九个选择框
    auto whiteView8=Sprite::create("select_white_rect.png");
    whiteView8->setPosition(20,scrollSize.height-1280);
    whiteView8->setAnchorPoint(Vec2(0, 1));
    whiteView8->cocos2d::Node::setScale(0.86);
    whiteView8->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(whiteView8);
    
    auto w8_content1 = Label::createWithSystemFont("勃起困难","fonts/Marker Felt.ttf",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w8_content1->setPosition(Point(20,15));
    w8_content1->setTextColor(Color4B(79, 79, 79, 255));
    w8_content1->setAnchorPoint(Vec2(0, 0));
    whiteView8->addChild(w8_content1);
    auto w8_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w8_box1->setPosition(Vec2(180,20));
    w8_box1->setTag(60);
    w8_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w8_box1->setTouchEnabled(true);
    w8_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView8->addChild(w8_box1);
    
#pragma-第十个选择框
    auto whiteView9=Sprite::create("select_white_rect.png");
    whiteView9->setPosition(20,scrollSize.height-1380);
    whiteView9->setAnchorPoint(Vec2(0, 1));
    whiteView9->cocos2d::Node::setScale(0.86);
    whiteView9->setContentSize(Size(blueView1->getContentSize().width, 90));
    scrollV->addChild(whiteView9);
    
    auto w9_content1 = Label::createWithSystemFont("心慌、恶心、头晕","fonts/Marker Felt.ttf",35,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    w9_content1->setPosition(Point(20,15));
    w9_content1->setTextColor(Color4B(79, 79, 79, 255));
    w9_content1->setAnchorPoint(Vec2(0, 0));
    whiteView9->addChild(w9_content1);
    auto w9_box1 = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    w9_box1->setPosition(Vec2(320,20));
    w9_box1->setTag(60);
    w9_box1->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    w9_box1->setTouchEnabled(true);
    w9_box1->addEventListener(CC_CALLBACK_2(SelectCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    whiteView9->addChild(w9_box1);
    
    
    return true;
}
//实现CheckBox回调函数
void SelectCaseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {

    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

ScrollView* SelectCaseScene::createScrollV(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0,0));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(false);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height-150));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
     scrollView->setInnerContainerSize(Size(visibleSize.width, 1550));//设置内容大小
    return scrollView;
    
}

#pragma -Json         (读取本地的json)
void SelectCaseScene::getJsonData(std::string filename, std::vector<data> &vec)
{
    rapidjson::Document doc;
    ssize_t size = 0;
    unsigned char *pBytes = NULL;
    do {
        pBytes = cocos2d::FileUtils::getInstance()->getFileData("selfBuildCase.json", "r", &size);
        CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
        std::string load_str((const char*)pBytes, size);
        CC_SAFE_DELETE_ARRAY(pBytes);
        doc.Parse<0>(load_str.c_str());
        CC_BREAK_IF(doc.HasParseError());
//        CC_BREAK_IF(!doc.IsArray());
        const rapidjson::Value &p = doc;
        if (p.HasMember("selfBuildCase"))
        {
            rapidjson::Value& object = doc["selfBuildCase"]["step1"];
            data mydata;
//            for (rapidjson::SizeType i = 0; i < object.Size(); i++)
//            {
//                const rapidjson::Value &p = object[i];
//                if (p.HasMember("title"))
//                {
//                    mydata.title = p["title"].GetString();
//                }
//                if (p.HasMember("content"))
//                {
//                    mydata.content = p["content"].GetArray();
//                }
//                vec.push_back(mydata);              //将获得的数据放入容器中
//            }
        }
    }while (0);
    
}



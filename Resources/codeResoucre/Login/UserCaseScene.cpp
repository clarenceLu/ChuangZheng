//
//  UserCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#include "UserCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "PerfectCaseScene.hpp"
#include "ChatScene.hpp"
#include "LoginScene.h"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *UserCaseScene::createScene(){
    return UserCaseScene::create();
}
LayerMultiplex *multLayer;

bool UserCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    
    auto layer1=createCaseLayer();
    auto layer2=createInformLayer();
    auto layer3=createDynamicLayer();
    auto layer4=createUserInfoLayer();
    multLayer = LayerMultiplex::create(layer1, layer2,layer3,layer4,nullptr);
    addChild(multLayer, 0);
    
    auto bottom=Sprite::create("bk_perfect_bottom.png");
    bottom->setPosition(Vec2(0, 0));
    bottom->setAnchorPoint(Vec2(0, 0));
    bottom->setContentSize(Size(visibleSize.width, 100));
    this->addChild(bottom);
    
    auto caseCheckBox = CheckBox::create("btn_case_unselect.png","btn_case_select.png");
    //设置CheckBox的位置
    caseCheckBox->setPosition(Vec2(50,10));
    caseCheckBox->setTag(0);
    caseCheckBox->setAnchorPoint(Vec2(0, 0));
    caseCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    caseCheckBox->setTouchEnabled(true);
    caseCheckBox->setSelected(true);
    caseCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(caseCheckBox);
    
    auto informCheckBox = CheckBox::create("btn_inform_unselect.png","btn_inform_select.png");
    //设置CheckBox的位置
    informCheckBox->setPosition(Vec2(200,10));
    informCheckBox->setTag(1);
    informCheckBox->setAnchorPoint(Vec2(0, 0));
    informCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    informCheckBox->setTouchEnabled(true);
    informCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(informCheckBox);
    
    auto dynamicCheckBox = CheckBox::create("btn_dynamic_unselect.png","btn_dynamic_select.png");
    //设置CheckBox的位置
    dynamicCheckBox->setPosition(Vec2(340,10));
    dynamicCheckBox->setTag(2);
    dynamicCheckBox->setAnchorPoint(Vec2(0, 0));
    dynamicCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    dynamicCheckBox->setTouchEnabled(true);
    dynamicCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(dynamicCheckBox);
    
    auto userCheckBox = CheckBox::create("btn_user_unselect.png","btn_user_select.png");
    //设置CheckBox的位置
    userCheckBox->setPosition(Vec2(520,10));
    userCheckBox->setTag(3);
    userCheckBox->setAnchorPoint(Vec2(0, 0));
    userCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    userCheckBox->setTouchEnabled(true);
    userCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(userCheckBox);
    return true;
}

//通知
Layer* UserCaseScene::createInformLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(origin.x, origin.y));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_notification.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto notificationHospitalBtn=Button::create();
    notificationHospitalBtn->loadTextures("btn_notification_hospital.png", "btn_notification_hospital.png");
    notificationHospitalBtn->setPosition(Vec2(20, visibleSize.height-170));
    notificationHospitalBtn->setAnchorPoint(Vec2(0, 1));
    notificationHospitalBtn->setScale(0.85);
    notificationHospitalBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
        {
            auto sprite = Sprite::create("notification_none.png");
                sprite->setPosition(Vec2(130, 520));
                sprite->setAnchorPoint(Vec2(0, 0));
                setOpacity(30);
                this->addChild(sprite, 0);
                 sprite->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            break;
    }
    }
    });
    layer->addChild(notificationHospitalBtn);
    
    auto chatBtn=Button::create();
    chatBtn->loadTextures("btn_notification_chat.png", "btn_notification_chat.png");
    chatBtn->setPosition(Vec2(20, visibleSize.height-300));
    chatBtn->setAnchorPoint(Vec2(0, 1));
    chatBtn->setScale(0.85);
    chatBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
#pragma-聊天界面
            auto chatSC=ChatScene::createScene();
            Director::getInstance()->pushScene(chatSC);
            
        }
        default:
            break;
    }
    });
    layer->addChild(chatBtn);
    
    auto informBtn=Button::create();
    informBtn->loadTextures("btn_notification_info.png", "btn_notification_info.png");
    informBtn->setPosition(Vec2(20, visibleSize.height-430));
    informBtn->setAnchorPoint(Vec2(0, 1));
    informBtn->setScale(0.85);
    informBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *informLayer=createNotificationInformLayer();
            informLayer->setTag(1000);
            this->addChild(informLayer);
        }
        default:
            break;
    }
    });
    layer->addChild(informBtn);
    
    
    return layer;
}
//复诊说明
Layer* UserCaseScene::createNotificationInformLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(origin.x, origin.y));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    
    auto bkView=Sprite::create("bk_notification_info.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1000);
        default:
            break;
    }
    });
    layer->addChild(backBtn);
    return layer;
}
//病例
Layer* UserCaseScene::createCaseLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_usercase.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_usercase_add.png", "btn_usercase_add.png");
    addBtn->setPosition(Vec2(560, visibleSize.height-90));
    addBtn->setScale(0.95);
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:  {
            auto perfectScene= PerfectCaseScene::create();
            Director::getInstance()->pushScene(perfectScene);
        }
            
        default:
            break;
    }
    });
    layer->addChild(addBtn);
    
    auto blueBK=Sprite::create("usercase_bluerect.png");
    blueBK->setPosition(Vec2(20, visibleSize.height-270));
    blueBK->setAnchorPoint(Vec2(0, 0));
    blueBK->setScale(0.87);
    layer->addChild(blueBK);
    
    auto label = Label::createWithSystemFont("张三丰","fonts/Marker Felt.ttf",45,Size(160,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    label->setPosition(Point(20,28));
    label->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(label);
    
    auto sexLB = Label::createWithSystemFont("男","fonts/Marker Felt.ttf",45,Size(60,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    sexLB->setPosition(Point(200,28));
    sexLB->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(sexLB);
    
    auto ageLB = Label::createWithSystemFont("32岁","Arial",45,Size(120,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    ageLB->setPosition(Point(280,28));
    ageLB->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(ageLB);
    
    auto numLB = Label::createWithSystemFont("330681199404058945","Arial",40,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    numLB->setPosition(Point(400,30));
    numLB->setAnchorPoint(Vec2(0, 0));
    blueBK->addChild(numLB);
    
    auto detailBtn=Button::create();
    detailBtn->loadTextures("usercase_detail.png", "usercase_detail.png");
    detailBtn->setPosition(Vec2(20, visibleSize.height-370));
    detailBtn->setAnchorPoint(Vec2(0, 0));
    detailBtn->setScale(0.87);
    detailBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    layer->addChild(detailBtn);
    
    auto detailLB = Label::createWithSystemFont("住院","fonts/Marker Felt.ttf",40,Size(120,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    detailLB->setPosition(Point(20,10));
    detailLB->setTextColor(Color4B::BLACK);
    detailLB->setAnchorPoint(Vec2(0, 0));
    detailBtn->addChild(detailLB);
    
    auto timeLB = Label::createWithSystemFont("2017-04-05","Arial",40,Size(visibleSize.width-280,60),TextHAlignment::CENTER,TextVAlignment::TOP);
    timeLB->setPosition(Point(140,10));
    timeLB->setTextColor(Color4B::BLACK);
    timeLB->setAnchorPoint(Vec2(0, 0));
    detailBtn->addChild(timeLB);
    
    
    
    auto selfBtn=Button::create();
    selfBtn->loadTextures("usercase_detail.png", "usercase_detail.png");
    selfBtn->setPosition(Vec2(20, visibleSize.height-470));
    selfBtn->setAnchorPoint(Vec2(0, 0));
    selfBtn->setScale(0.87);
    selfBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto perfectScene= PerfectCaseScene::create();
            Director::getInstance()->pushScene(perfectScene);
        }
        default:
            break;
    }
    });
    layer->addChild(selfBtn);
    
    auto selfLB = Label::createWithSystemFont("自述","fonts/Marker Felt.ttf",40,Size(120,60),TextHAlignment::LEFT,TextVAlignment::TOP);
    selfLB->setPosition(Point(20,10));
    selfLB->setTextColor(Color4B::BLACK);
    selfLB->setAnchorPoint(Vec2(0, 0));
    selfBtn->addChild(selfLB);
    
    auto selfTime = Label::createWithSystemFont("2017-04-05","Arial",40,Size(visibleSize.width-280,60),TextHAlignment::CENTER,TextVAlignment::TOP);
    selfTime->setPosition(Point(140,10));
    selfTime->setTextColor(Color4B::BLACK);
    selfTime->setAnchorPoint(Vec2(0, 0));
    selfBtn->addChild(selfTime);
    
    return layer;
}

//长征动态
Layer* UserCaseScene::createDynamicLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(origin.x, origin.y));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_dynamic.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    layer->addChild(bkView);
    
    auto scrollV=createTableView(Vec2(0, 100), Size(visibleSize.width, 890));
    bkView->addChild(scrollV);
    
    return layer;
}

ScrollView* UserCaseScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    scrollView->setInnerContainerSize(Size(visibleSize.width, 220*10));//设置内容大小
    for (int i=0; i<10; i++) {
        auto layer1 = createMessageBtn(i,scrollView->getInnerContainerSize());
        scrollView->addChild(layer1);
    }
    
    return scrollView;
}

Button* UserCaseScene::createMessageBtn(int i, Size  innerSize){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto layer=Button::create();
    layer->loadTextures("bk_dynamic_tableView.png", "bk_dynamic_tableView.png");
    layer->setPosition(Point(10,innerSize.height-220*(i+1)+10));
    layer->setAnchorPoint(Vec2(0, 0));
    layer->setScale(0.87);
    layer->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
 log("点击跳转页面");
        }
        default:
            break;
    }
    });
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(20, 20));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
    headBtn->ignoreContentAdaptWithSize(true);
    headBtn->setScale9Enabled(true);
    headBtn->setContentSize(Size(130, 130));
    headBtn->setTag(i);
    layer->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            log("点击上传头像");
        }
    });
    
    auto nameLB = Label::createWithSystemFont("热烈祝贺乾隆--荣获先进党支部！陈书记获院优秀共产党员称号！大家激情澎湃","fonts/Marker Felt.ttf",35,Size(layer->getContentSize().width-190,130),TextHAlignment::LEFT,TextVAlignment::TOP);
    nameLB->setPosition(Point(170,20));
    nameLB->setTextColor(Color4B(0, 0, 0, 255/2));
    nameLB->setAnchorPoint(Vec2(0, 0));
    layer->addChild(nameLB);
    
    
    return layer;
}




//个人资料
Layer* UserCaseScene::createUserInfoLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
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
    
    
    auto bkView=Sprite::create("bk_userInfo.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    layer->addChild(bkView);
    
    auto codeBtn=Button::create();
    codeBtn->loadTextures("btn_userInfo_code.png", "btn_userInfo_code.png");
    codeBtn->setPosition(Vec2(visibleSize.width-80, visibleSize.height-90));
    codeBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto codeLayer=createCodeLayer();
            codeLayer->setTag(201);
            this->addChild(codeLayer);
        }
        default:
            break;
    }
    });
    bkView->addChild(codeBtn);
    
    auto headImageBtn=Button::create();
    headImageBtn->loadTextures("HelloWorld.png", "HelloWorld.png");
    headImageBtn->setPosition(Vec2(52, 830));
    headImageBtn->setAnchorPoint(Vec2(0, 0));
    headImageBtn->setScale9Enabled(true);
    headImageBtn->setContentSize(Size(141, 141));
    headImageBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *headLayer= createAlbumLayer();
            headLayer->setTag(200);
            this->addChild(headLayer);
        }
        default:
            break;
    }
    });
    bkView->addChild(headImageBtn);
    
    auto exitBtn=Button::create();
    exitBtn->loadTextures("btn_userInfo_back.png", "btn_userInfo_back.png");
    exitBtn->setPosition(Vec2(visibleSize.width/2-120, 154));
    exitBtn->setAnchorPoint(Vec2(0, 0));
    exitBtn->setScale(0.87);
    exitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto exitLayer=createExitLayer();
            exitLayer->setTag(2001);
            this->addChild(exitLayer);
                break;
        }
        default:
            break;
    }
    });
    bkView->addChild(exitBtn);
//密码修改
    auto judgeBtn=Button::create();
    judgeBtn->loadTextures("userInfo_judge.png", "userInfo_judge.png");
    judgeBtn->setPosition(Vec2(visibleSize.width-90, 338));
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto chageLayer=createChangeKeyLayer();
            chageLayer->setTag(1050);
            this->addChild(chageLayer);
        }
        default:
            break;
    }
    });
    bkView->addChild(judgeBtn);
    //手势锁
    auto keyCheckBox = CheckBox::create("btn_userInfo_OFF.png","btn_userInfo_ON.png");
    //设置CheckBox的位置
    keyCheckBox->setPosition(Vec2(visibleSize.width-180, 268));
    keyCheckBox->setTag(10);
    keyCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    keyCheckBox->setTouchEnabled(true);
    keyCheckBox->addEventListener(CC_CALLBACK_2(UserCaseScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(keyCheckBox);
    
    auto userName = Label::createWithSystemFont("用户名：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(Point(233,886));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto textFieldUser = TextField::create("抵抗力","Arial",35);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(300, 50));
    textFieldUser->setPosition(Vec2(380,886));
    textFieldUser->setAnchorPoint(Vec2(0,0));
    textFieldUser->setContentSize(Size(300,50));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldUser->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(210, 880));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.6);
    bkView->addChild(lineV);
    
    auto sex = Label::createWithSystemFont("性别：","Arial",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    sex->setPosition(Point(233,822));
    sex->setTextColor(Color4B(91, 144, 229, 255));
    sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(sex);
    
    auto textFieldSex = TextField::create("女","Arial",35);
    textFieldSex->setMaxLength(40);
    textFieldSex->setTouchSize(Size(80, 50));
    textFieldSex->setPosition(Vec2(350,822));
    textFieldSex->setAnchorPoint(Vec2(0,0));
    textFieldSex->setContentSize(Size(80,50));
    textFieldSex->setTextColor(Color4B::BLACK);
    textFieldSex->setPlaceHolderColor(Color4B::GRAY);
    textFieldSex->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldSex->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    bkView->addChild(textFieldSex);
    
    auto age = Label::createWithSystemFont("性别：","Arial",35,Size(140,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    age->setPosition(Point(412,822));
    age->setTextColor(Color4B(91, 144, 229, 255));
    age->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(age);
    
    auto textFieldAge = TextField::create("32","Arial",35);
    textFieldAge->setMaxLength(40);
    textFieldAge->setTouchSize(Size(120, 50));
    textFieldAge->setPosition(Vec2(530,822));
    textFieldAge->setAnchorPoint(Vec2(0,0));
    textFieldAge->setContentSize(Size(120,50));
    textFieldAge->setTextColor(Color4B::BLACK);
    textFieldAge->setPlaceHolderColor(Color4B::GRAY);
    textFieldAge->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldAge->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    bkView->addChild(textFieldAge);
    
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(210, 816));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setScaleX(0.6);
    bkView->addChild(lineV2);
    
    auto textfieldName=createBasicData(bkView, Vec2(59, 758), "真实姓名：", "张牧之");
    auto textfieldNum=createBasicData(bkView, Vec2(59, 688), "证件号：", "未填写");
     auto textfieldTel1=createBasicData(bkView, Vec2(59, 618), "电话：", "未填写");
    auto textfieldTel2=createBasicData(bkView, Vec2(59, 548), "电话1：", "未填写");
    auto textfieldTel3=createBasicData(bkView, Vec2(59, 478), "电话2：", "未填写");
    auto textfieldCaseNum=createBasicData(bkView, Vec2(59, 408), "病历号：", "未填写");
    
    auto password = Label::createWithSystemFont("密码修改","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    password->setPosition(Vec2(59, 338));
    password->setTextColor(Color4B(91, 144, 229, 255));
    password->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(password);
    auto lineV3=Sprite::create("userInfo_line.png");
    lineV3->setPosition(Vec2(51, 332));
    lineV3->setAnchorPoint(Vec2(0, 0));
    lineV3->setScaleX(0.85);
    bkView->addChild(lineV3);
    
    auto key = Label::createWithSystemFont("手势锁：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    key->setPosition(Vec2(59, 268));
    key->setTextColor(Color4B(91, 144, 229, 255));
    key->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(key);
    auto lineV4=Sprite::create("userInfo_line.png");
    lineV4->setPosition(Vec2(51, 262));
    lineV4->setAnchorPoint(Vec2(0, 0));
    lineV4->setScaleX(0.85);
    bkView->addChild(lineV4);
    
    
    
    return layer;
}

TextField*  UserCaseScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
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
    textFieldUser->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}


//实现CheckBox回调函数
void UserCaseScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if (tag==10) {
//手势锁
        }else{
        //切换按钮的高亮
        for (int i=0; i<4; i++) {
            if (i!=tag) {
                CheckBox * checkBox=(CheckBox*)this->getChildByTag(i);
                checkBox->setSelected(false);
            }
        }
        }
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            if (tag==10) {
                //手势锁
            }else{
                //切换页面
            multLayer->switchTo(tag);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}
void UserCaseScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
     int tag= textField->getTag();
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            if (tag>=1000&&tag<=1002) {
                if (textField->getStringLength()>13) {
                    textField->setString(subUTF8(textField->getString(), 0, 12));
                }
            }
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            if (tag>=1000&&tag<=1002) {
                
            }
            CCLOG("DETACH_WITH_IME");
            
            break;
            
    }
    
}

//退出账号
Layer* UserCaseScene::createExitLayer(){
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
    auto contentV = Sprite::create("bk_sureExit.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(160, 541));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
           this->removeChildByTag(2001);
            auto loginnSC=LoginScene::createScene();
            Director::getInstance()->replaceScene(loginnSC);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);

    return layer;
    
}


TextField *originalPassword;
TextField *newPassword;
TextField* surePassword;
//修改密码
Layer* UserCaseScene::createChangeKeyLayer(){
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
    auto contentV = Sprite::create("bk_change_password.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(visibleSize.width-110, 700));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(1050);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_change_password_save.png", "btn_change_password_save.png");
    sureBtn->setPosition(Vec2(225, 361));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->cocos2d::Node::setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (newPassword->getStringLength()<6) {
                auto judgeV = Label::createWithSystemFont("您设置的密码位数少于6位","Arial",35,Size(visibleSize.width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2+100, 268));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0, 0));
                this->addChild(judgeV);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else if(strcmp(newPassword->getString().c_str(), surePassword->getString().c_str())){
                auto judgeV = Label::createWithSystemFont("您输入的密码前后不一样","Arial",35,Size(visibleSize.width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2+100, 268));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0, 0));
                this->addChild(judgeV);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else{
               this->removeChildByTag(1050);
            }
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    originalPassword = TextField::create("未填写","Arial",35);
    originalPassword->setMaxLength(40);
    originalPassword->setTouchSize(Size(visibleSize.width-300, 50));
    originalPassword->setPosition(Vec2(visibleSize.width-100,590));
    originalPassword->setAnchorPoint(Vec2(1,0));
    originalPassword->setContentSize(Size(visibleSize.width-300,50));
    originalPassword->setTextColor(Color4B::BLACK);
    originalPassword->setPlaceHolderColor(Color4B::GRAY);
    originalPassword->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    originalPassword->setPasswordEnabled(true);
    originalPassword->setTag(1000);
    originalPassword->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    contentV->addChild(originalPassword);
    
    newPassword = TextField::create("未填写","Arial",35);
    newPassword->setMaxLength(40);
    newPassword->setTouchSize(Size(visibleSize.width-300, 50));
    newPassword->setPosition(Vec2(visibleSize.width-100,524));
    newPassword->setAnchorPoint(Vec2(1,0));
    newPassword->setContentSize(Size(visibleSize.width-300,50));
    newPassword->setTextColor(Color4B::BLACK);
    newPassword->setPlaceHolderColor(Color4B::GRAY);
    newPassword->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    newPassword->setTag(1001);
    newPassword->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    contentV->addChild(newPassword);
    
    surePassword = TextField::create("未填写","Arial",35);
    surePassword->setMaxLength(40);
    surePassword->setTouchSize(Size(visibleSize.width-300, 50));
    surePassword->setPosition(Vec2(visibleSize.width-100,455));
    surePassword->setAnchorPoint(Vec2(1,0));
    surePassword->setContentSize(Size(visibleSize.width-300,50));
    surePassword->setTextColor(Color4B::BLACK);
    surePassword->setPlaceHolderColor(Color4B::GRAY);
    surePassword->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    surePassword->setTag(1002);
    surePassword->addEventListener(CC_CALLBACK_2(UserCaseScene::eventCallBack, this));
    contentV->addChild(surePassword);
    
    
    return layer;
}



//二维码
Layer* UserCaseScene::createCodeLayer(){
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
    auto contentV = Sprite::create("bk_QRCode.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    auto codeImage = Sprite::create("example.png");
    codeImage->setAnchorPoint(Vec2(0,0));
    codeImage->setPosition(Vec2(225,445));
    codeImage->setContentSize(Size(196, 196));
    contentV->addChild(codeImage);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(visibleSize.width-110, 700));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(201);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_QRCode_sure.png", "btn_QRCode_sure.png");
    sureBtn->setPosition(Vec2(225, 361));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->cocos2d::Node::setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(201);
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    return layer;
}

//上传头像
Layer* UserCaseScene::createAlbumLayer(){
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
    auto contentV = Sprite::create("update_album.png");
    contentV->setAnchorPoint(Vec2(0,1));
    contentV->setPosition(Vec2(57,visibleSize.height-300));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto cameraBtn=Button::create();
    cameraBtn->setScale9Enabled(true);
    cameraBtn->setPosition(Vec2(0, 88));
    cameraBtn->setAnchorPoint(Vec2(0,0));
    cameraBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    cameraBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(cameraBtn);
    
    auto albumBtn=Button::create();
    albumBtn->setScale9Enabled(true);
    albumBtn->setPosition(Vec2(0, 168));
    albumBtn->setAnchorPoint(Vec2(0,0));
    albumBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    albumBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(albumBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(111, 15));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->cocos2d::Node::setScale(0.87);
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(200);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    
    return layer;
}

//截取字符串
std::vector<std::string> UserCaseScene::parseUTF8(const std::string &str)
{
    int l = str.length();
    std::vector<std::string> ret;
    ret.clear();
    for(int p = 0; p < l; )
    {
        int size=0;
        unsigned char c = str[p];
        if(c < 0x80) {
            size = 1;
        }
        else if(c < 0xc2)
        {
            size = 2;
        }
        else if(c < 0xe0)
        {
            size = 2;
        }
        else if(c < 0xf0)
        {
            size = 3;
        }
        else if(c < 0xf8)
        {
            size = 4;
        }
        else if (c < 0xfc)
        {
            size = 5;
        }
        else if (c < 0xfe)
        {
            size = 6;
        }
        else
            size = 7;
        std::string temp = "";
        temp = str.substr(p, size);
        ret.push_back(temp);
        p += size;
    }
    return ret;
}

std::string UserCaseScene::subUTF8(const std::string &str,int from, int to)
{
    if(from > to) return "";
    if (str.length() < to) return "";
    std::vector<std::string> vstr = parseUTF8(str);
    std::vector<std::string>::iterator iter=vstr.begin();
    std::string res;
    std::string result;
    for(iter=(vstr.begin() + from); iter != (vstr.begin() + to); iter++)
    {
        res += *iter;
    }
    return res;
}

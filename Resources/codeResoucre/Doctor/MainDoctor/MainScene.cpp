//
//  MainScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#include "MainScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "AccountManageScene.hpp"
#include "GroupLeaderScene.hpp"
#include "GroupMemberScene.hpp"
#include "CaseSearchScene.hpp"
#include "ReceiveChatScene.hpp"
#include "WaitChatScene.hpp"
#include "SetTemporaryRoom.hpp"
#include "SickRoomScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MainScene::createScene(){
    return MainScene::create();
}

bool MainScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    
    boxVec = std::make_shared<Vector<CheckBox*>>();  //default constructor
    
    auto layer1=createSickRoomLayer();
    auto layer2=createOutPatientLayer();
    auto layer3=createCalendarLayer();
    auto layer4=createSickInfoLayer();
    multLayer = LayerMultiplex::create(layer1, layer2,layer3,layer4,nullptr);
    addChild(multLayer, 0);
    
    auto bottom=Sprite::create("bk_perfect_bottom.png");
    bottom->setPosition(Vec2(0, 0));
    bottom->setAnchorPoint(Vec2(0, 0));
    bottom->setContentSize(Size(visibleSize.width, 100));
    this->addChild(bottom);
    
    auto sickRoomBox = CheckBox::create("box_sickRoom_unselect.png","box_sickRoom_select.png");
    //设置CheckBox的位置
    sickRoomBox->setPosition(Vec2(50,10));
    sickRoomBox->setTag(0);
    sickRoomBox->setAnchorPoint(Vec2(0, 0));
    sickRoomBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickRoomBox->setTouchEnabled(true);
    sickRoomBox->setSelected(true);
    sickRoomBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickRoomBox);
    
    auto outPatientBox = CheckBox::create("box_outpatient_unselect.png","box_outpatient_select.png");
    //设置CheckBox的位置
    outPatientBox->setPosition(Vec2(200,10));
    outPatientBox->setTag(1);
    outPatientBox->setAnchorPoint(Vec2(0, 0));
    outPatientBox->setScale(0.87);
    //设置CheckBox是否可点击
    outPatientBox->setTouchEnabled(true);
    outPatientBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(outPatientBox);
    
    auto calendarBox = CheckBox::create("box_calendar_unselect.png","box_calendar_select.png");
    //设置CheckBox的位置
    calendarBox->setPosition(Vec2(370,10));
    calendarBox->setTag(2);
    calendarBox->setAnchorPoint(Vec2(0, 0));
    calendarBox->setScale(0.87);
    //设置CheckBox是否可点击
    calendarBox->setTouchEnabled(true);
    calendarBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(calendarBox);
    
    auto sickInfoBox = CheckBox::create("box_sickInfo_unselelct.png","box_sickInfo_selelct.png");
    //设置CheckBox的位置
    sickInfoBox->setPosition(Vec2(520,10));
    sickInfoBox->setTag(3);
    sickInfoBox->setAnchorPoint(Vec2(0, 0));
    sickInfoBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickInfoBox->setTouchEnabled(true);
    sickInfoBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickInfoBox);
    return true;
}

//病床
Layer* MainScene::createSickRoomLayer(){
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
    
    auto bkView=Sprite::create("bk_sickRoom.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_addCase_add.png", "btn_addCase_add.png");
    addBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto temporaryRoomSC=SetTemporaryRoom::createScene();
            Director::getInstance()->pushScene(temporaryRoomSC);
        }
        default:
            break;
    }
    });
    bkView->addChild(addBtn);
    
    auto tempBedBox=CheckBox::create("box_tempBed_unselect.png","box_tempBed_select.png");
    //设置CheckBox的位置
    tempBedBox->setPosition(Vec2(visibleSize.width/2,918));
    tempBedBox->setTag(5);
    tempBedBox->setAnchorPoint(Vec2(0, 0));
    tempBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    tempBedBox->setTouchEnabled(true);
    tempBedBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
   bkView->addChild(tempBedBox);
    boxVec->pushBack(tempBedBox);
    auto fixedBedBox=CheckBox::create("box_fixedBed_unselect.png","box_fixedBed_select.png");
    //设置CheckBox的位置
    fixedBedBox->setPosition(Vec2(0,918));
    fixedBedBox->setTag(6);
    fixedBedBox->setAnchorPoint(Vec2(0, 0));
    fixedBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    fixedBedBox->setTouchEnabled(true);
    fixedBedBox->setSelected(true);
    fixedBedBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(fixedBedBox);
    boxVec->pushBack(fixedBedBox);
    
    auto line1=Sprite::create("userInfo_line.png");
    line1->setPosition(Vec2(0, 915));
    line1->setAnchorPoint(Vec2(0, 0));
    line1->setScaleX(1.05);
    bkView->addChild(line1);
    
    auto job = Label::createWithSystemFont("上海医院松江分院外科楼6楼","Arial",35,Size(visibleSize.width-40,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
    job->setPosition(Vec2(20,850));
    job->setTextColor(Color4B(0, 0, 0, 255/2));
    job->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(job);
    
    auto line2=Sprite::create("userInfo_line.png");
    line2->setPosition(Vec2(0, 835));
    line2->setAnchorPoint(Vec2(0, 0));
    line2->setScaleX(1.05);
    bkView->addChild(line2);
    
    ScrollView *scrollV=createScrollV();
    bkView->addChild(scrollV);
    scrollV->setInnerContainerSize(Size(visibleSize.width, (int)(11/5)*155+20));//设置内容大小
    for (int i=0; i<11; i++) {
        Menu *menu=createRectButton(Vec2(27, scrollV->getInnerContainerSize().height-143), i);
        scrollV->addChild(menu);
    }
    return layer;
}

ScrollView* MainScene::createScrollV(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0,100));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 730));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    return scrollView;
}

Menu*   MainScene::createRectButton(Vec2 point,int i){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto menuItem  = MenuItemImage::create("bk_bed.png","bk_bed.png",CC_CALLBACK_1(MainScene::menuBedNumCallback, this));
    menuItem->setAnchorPoint(Vec2(0,0));
    menuItem->setPosition(Vec2(0,0));
    menuItem->setTag(i+100);
    menuItem->setScale(0.87);
    auto button = Menu::create();
    button->setAnchorPoint(Vec2(0,0));
    button->setPosition(point);
    button->addChild(menuItem);
    Size imageSize=menuItem->getContentSize()*0.87;
    int width=point.x+(imageSize.width+46)*i+imageSize.width;
            if (width<visibleSize.width) {
                button->setPosition(Vec2(point.x+(imageSize.width+46)*i, point.y));
            }else{
                button->setPosition(Vec2(point.x+(imageSize.width+46)*(i%5),point.y-((int)((width-point.x)/((imageSize.width+46)*5))*(imageSize.height+31))));
            }
    char strtest[500] = {0};
    sprintf(strtest,"bedNum%d.png",i%4+1);
    string numStr=strtest;
    auto num=Sprite::create(numStr);
    num->setPosition(Vec2(3, 30));
    num->setAnchorPoint(Vec2(0, 0));
    num->setScale(1.2);
    auto numLB = Label::createWithSystemFont(CCString::createWithFormat("%d",i+1)->getCString(),"Arial",35,Size(num->getContentSize().width,num->getContentSize().width),TextHAlignment::CENTER,TextVAlignment::CENTER);
    numLB->setPosition(Vec2(0,0));
    numLB->setTextColor(Color4B(255, 255, 255, 255));
    numLB->setAnchorPoint(Vec2(0, 0));
    num->addChild(numLB);
    menuItem->addChild(num);
    return button;
}



//门诊
Layer* MainScene::createOutPatientLayer(){
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
    
    auto bkView=Sprite::create("bk_outpatient.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    
    auto waitBtn=Button::create();
    waitBtn->loadTextures("btn_outpatient_content.png", "btn_outpatient_content.png");
    waitBtn->setPosition(Vec2(20, 849));
    waitBtn->setAnchorPoint(Vec2(0, 0));
    waitBtn->setScale(0.86);
    waitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto chatScene=WaitChatScene::createScene();
            Director::getInstance()->pushScene(chatScene);
//候诊病人
        }
        default:
            break;
    }
    });
    bkView->addChild(waitBtn);
    auto waitLB=Label::createWithSystemFont("候诊病人","Arial",50,Size(300,100),TextHAlignment::LEFT,TextVAlignment::CENTER);
    waitLB->setPosition(Vec2(20,15));
    waitLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    waitLB->setAnchorPoint(Vec2(0, 0));
    waitBtn->addChild(waitLB);
    
    auto receiveBtn=Button::create();
    receiveBtn->loadTextures("btn_outpatient_content.png", "btn_outpatient_content.png");
    receiveBtn->setPosition(Vec2(20, 710));
    receiveBtn->setAnchorPoint(Vec2(0, 0));
    receiveBtn->setScale(0.86);
    receiveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto chatScene=ReceiveChatScene::createScene();
            Director::getInstance()->pushScene(chatScene);
//接诊病人
        }
        default:
            break;
    }
    });
    bkView->addChild(receiveBtn);
    auto receiveLB=Label::createWithSystemFont("接诊病人","Arial",50,Size(300,100),TextHAlignment::LEFT,TextVAlignment::CENTER);
    receiveLB->setPosition(Vec2(20,15));
    receiveLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    receiveLB->setAnchorPoint(Vec2(0, 0));
    receiveBtn->addChild(receiveLB);
    
    return layer;
}
//日历
Layer* MainScene::createCalendarLayer(){
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
    
    return layer;
}
//我的
Layer* MainScene::createSickInfoLayer(){
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
    
    auto bkView=Sprite::create("bk_sickInfo.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto caseBtn=Button::create();
    caseBtn->loadTextures("btn_sickInfo_case.png", "btn_sickInfo_case.png");
    caseBtn->setPosition(Vec2(30, 840));
    caseBtn->setAnchorPoint(Vec2(0, 0));
    caseBtn->setScale(0.9);
    caseBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED: {
            auto caseScene= CaseSearchScene::createScene();
            Director::getInstance()->pushScene(caseScene);
        }
        default:
            break;
    }
    });
    bkView->addChild(caseBtn);
    
    auto groupBtn=Button::create();
    groupBtn->loadTextures("btn_sickInfo_group.png", "btn_sickInfo_group.png");
    groupBtn->setPosition(Vec2(30, 690));
    groupBtn->setAnchorPoint(Vec2(0, 0));
    groupBtn->setScale(0.9);
    groupBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (UserDefault::getInstance()->getIntegerForKey("isleader")) {
            auto groupScene= GroupLeaderScene::createScene();
            Director::getInstance()->pushScene(groupScene);
            }else{
                auto groupScene= GroupMemberScene::createScene();
                Director::getInstance()->pushScene(groupScene);
            }
        }
        default:
            break;
    }
    });
    bkView->addChild(groupBtn);
    
    auto messageBtn=Button::create();
    messageBtn->loadTextures("btn_sickInfo_message.png", "btn_sickInfo_message.png");
    messageBtn->setPosition(Vec2(30, 540));
    messageBtn->setAnchorPoint(Vec2(0, 0));
    messageBtn->setScale(0.9);
    messageBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    bkView->addChild(messageBtn);
    
    auto accountBtn=Button::create();
    accountBtn->loadTextures("btn_sickInfo_account.png", "btn_sickInfo_account.png");
    accountBtn->setPosition(Vec2(30, 390));
    accountBtn->setAnchorPoint(Vec2(0, 0));
    accountBtn->setScale(0.9);
    accountBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto accountScene= AccountManageScene::createScene();
            Director::getInstance()->pushScene(accountScene);
        }
        default:
            break;
    }
    });
    bkView->addChild(accountBtn);
    
    auto sponsorBtn=Button::create();
    sponsorBtn->loadTextures("btn_sickInfo_addSponsor.png", "btn_sickInfo_addSponsor.png");
    sponsorBtn->setPosition(Vec2(30, 240));
    sponsorBtn->setAnchorPoint(Vec2(0, 0));
    sponsorBtn->setScale(0.9);
    sponsorBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Layer *layer= createSponsorLayer();
            layer->setTag(1000);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    bkView->addChild(sponsorBtn);
    return layer;
}
Layer* MainScene::createSponsorLayer(){
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
    auto contentV = Sprite::create("bk_sickInfo_writeName.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(57,454));
    contentV->setContentSize(Size(526,300));
    layer->addChild(contentV);
    
    //必须写在textfield之前才能释放textfield响应者
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_register_delete.png", "btn_register_delete.png");
    deleteBtn->setPosition(Vec2(465, 240));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1000);
        default:
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_register_sure.png", "btn_register_sure.png");
    sureBtn->setPosition(Vec2(163, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *codeLayer= createSQCodeLayer();
            codeLayer->setTag(1001);
            this->addChild(codeLayer);
            this->removeChildByTag(1000);
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto textFieldCase = TextField::create("在此填写","Arial",40);
    textFieldCase->setMaxLength(40);
    textFieldCase->setTouchSize(Size(400, 42));
    textFieldCase->setAnchorPoint(Vec2(0.5,0));
    textFieldCase->setPosition(Vec2(264,123));
    textFieldCase->setContentSize(Size(400,42));
    textFieldCase->setTextColor(Color4B(0, 0, 0, 255/3*2));
    textFieldCase->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textFieldCase->addEventListener(CC_CALLBACK_2(MainScene::eventCallBack, this));
    contentV->addChild(textFieldCase);
    
    auto lineSp=Sprite::create("userInfo_line.png");
    lineSp->setPosition(Vec2(150, 120));
    lineSp->setAnchorPoint(Vec2(0, 0));
    lineSp->setContentSize(Size(226, 1));
    contentV->addChild(lineSp);
    
    return layer;
}
Layer* MainScene::createSQCodeLayer(){
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
    auto contentV = Sprite::create("bk_sickInfo_QRCode.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(57,344));
    contentV->setContentSize(Size(526,410));
    layer->addChild(contentV);
    
    //必须写在textfield之前才能释放textfield响应者
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_register_delete.png", "btn_register_delete.png");
    deleteBtn->setPosition(Vec2(465, 350));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1001);
        default:
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sendBtn=Button::create();
    sendBtn->loadTextures("btn_sickInfo_send.png", "btn_sickInfo_send.png");
    sendBtn->setPosition(Vec2(38, 15));
    sendBtn->setAnchorPoint(Vec2(0,0));
    sendBtn->setScale(0.87);
    sendBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1001);
        default:
            break;
    }
    });
    contentV->addChild(sendBtn);
    
    auto saveBtn=Button::create();
    saveBtn->loadTextures("btn_sickInfo_save.png", "btn_sickInfo_save.png");
    saveBtn->setPosition(Vec2(302, 15));
    saveBtn->setAnchorPoint(Vec2(0,0));
    saveBtn->setScale(0.87);
    saveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1001);
        default:
            break;
    }
    });
    contentV->addChild(saveBtn);
    
//加入二维码
    DrawNode *SQCode=createSQCodeImage("www.baidu.com",Vec2(164, 100));
    contentV->addChild(SQCode);
    return layer;
}

cocos2d::DrawNode * MainScene::createSQCodeImage(std::string content,Vec2 origin){
    char* contentStr=(char*)content.c_str();
    bool bRet = m_QREncode.EncodeData(0, 0, 1, -1, contentStr);
    if(bRet)
    {
        int nSize = 5;
        int originalSize = m_QREncode.m_nSymbleSize + (QR_MARGIN * 2);
        CCDrawNode *pQRNode = CCDrawNode::create();
        
        CCPoint pt[6];
        ccColor4F color;
        
        pt[0] = ccp(0, 0);
        pt[1] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
        pt[2] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, 0);
        
        pt[3] = pt[0];
        pt[4] = ccp(0, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
        pt[5] = pt[1];
        color = ccc4f(1, 1, 1, 1);
        pQRNode->drawPolygon(pt, 6, color, 0, color);
        
        for (int i = 0; i < m_QREncode.m_nSymbleSize; ++i)
        {
            for (int j = 0; j < m_QREncode.m_nSymbleSize; ++j)
            {
                pt[0] = ccp((i + QR_MARGIN)*nSize, (j + QR_MARGIN)*nSize);
                pt[1] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 1)*nSize);
                pt[2] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 0)*nSize);
                
                pt[3] = pt[0];
                pt[4] = ccp(((i + QR_MARGIN) + 0)*nSize, ((j + QR_MARGIN) + 1)*nSize);
                pt[5] = pt[1];
                if (m_QREncode.m_byModuleData[i][j] == 1)
                {
                    color = ccc4f(0, 0, 0, 1);
                }
                else
                {
                    color = ccc4f(1, 1, 1, 1);
                }
                pQRNode->drawPolygon(pt, 6, color, 0, color);
            }
        }
//        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//        pQRNode->setPosition(ccp((winSize.width - nSize*m_QREncode.m_nSymbleSize) / 2, winSize.height - (winSize.height - nSize*m_QREncode.m_nSymbleSize) / 2));
        pQRNode->setAnchorPoint(Vec2(0, 0));
        pQRNode->setPosition(origin);
        pQRNode->setScale(1.70);
//        pQRNode->setScaleY(-1);
        return pQRNode;
}
}



void MainScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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

//实现CheckBox回调函数
void MainScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if (tag==5||tag==6) {
//临时病床和固定病床
            for (int i=0; i<2; i++) {
                CheckBox *box=boxVec->at(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
        }else if(tag>=0&&tag<=4){
//底部切换按钮的高亮
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
            if (tag==5||tag==6) {
            }else if(tag>=0&&tag<=4){
                //切换页面
                multLayer->switchTo(tag);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            if (tag==5||tag==6) {
               item->setSelected(true);
            }
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

void MainScene::menuBedNumCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    int tag= item->getTag();
    auto sickroomSC=(SickRoomScene*)SickRoomScene::createScene();
    sickroomSC->bedNum=tag-99;
    Director::getInstance()->pushScene(sickroomSC);
    
}

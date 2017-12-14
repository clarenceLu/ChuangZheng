//
//  ResigterDetailScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/13.
//

#include "ResigterDetailScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *RegisterDetailScene::createScene(){
    return RegisterDetailScene::create();
}
bool RegisterDetailScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_registerDetail.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    this->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-90));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto headBtn=Button::create();
    headBtn->loadTextures("btn_update_head.png", "btn_update_head.png");
    headBtn->setPosition(Vec2(310, visibleSize.height-220));
    headBtn->setScale(0.8);
    headBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Layer *layer= createAlbumLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    this->addChild(headBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_perfect_sure.png", "btn_perfect_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width/2-120, 30));
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->setScale(0.70);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    auto textfieldName=createBasicData(bkView, Vec2(59, 768), "用户名：", "张牧之");
    auto textfieldPass=createBasicData(bkView, Vec2(59, 688), "密码：", "未填写");
     textfieldPass->setPasswordEnabled(true);
    auto textfieldSurePass=createBasicData(bkView, Vec2(59, 608), "确认密码：", "未填写");
     textfieldSurePass->setPasswordEnabled(true);
    auto textfieldTel=createBasicData(bkView, Vec2(59, 448), "联系电话：", "未填写");
    auto textfieldCaseTel2=createBasicData(bkView, Vec2(59, 368), "手机：", "未填写");
    auto textfieldCaseAddress=createBasicData(bkView, Vec2(59, 288), "家庭住址：", "未填写");
    
     auto textfieldCaseRefer=createBasicData(bkView, Vec2(59, 208), "家庭住址：", "未填写");
    
    
    
    
    auto scan = Label::createWithSystemFont("推荐人","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    scan->setPosition(Vec2(59, 128));
    scan->setTextColor(Color4B(91, 144, 229, 255));
    scan->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(scan);
    auto scanStar = Label::createWithSystemFont("*","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    scanStar->setPosition(30,123);
    scanStar->setTextColor(Color4B(205, 133, 147, 255));
    scanStar->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(scanStar);
    auto scanlineV=Sprite::create("userInfo_line.png");
    scanlineV->setPosition(Vec2(51,122));
    scanlineV->setAnchorPoint(Vec2(0, 0));
    scanlineV->setScaleX(0.85);
    bkView->addChild(scanlineV);
    
    auto scanBtn=Button::create();
    scanBtn->loadTextures("alpha.png", "alpha.png");
    scanBtn->setTitleText("点击扫描");
    scanBtn->setTitleColor(Color3B(51, 145, 233/2));
    scanBtn->setTitleFontSize(33);
    scanBtn->setPosition(Vec2(visibleSize.width-110, 135));
    scanBtn->setAnchorPoint(Vec2(1, 0));
    scanBtn->setScale9Enabled(false);
    scanBtn->setContentSize(Size(100, 40));
    scanBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //扫描二维码
        }
        default:
            break;
    }
    });
    bkView->addChild(scanBtn);

    
    
    
    auto Sex = Label::createWithSystemFont("性别","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Sex->setPosition(Vec2(59, 528));
    Sex->setTextColor(Color4B(91, 144, 229, 255));
    Sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Sex);
    auto Star = Label::createWithSystemFont("*","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Star->setPosition(30,523);
    Star->setTextColor(Color4B(205, 133, 147, 255));
    Star->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Star);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51,522));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    auto manCheckBox = CheckBox::create("message_select_man.png","select_sure.png");
    //设置CheckBox的位置
    manCheckBox->setPosition(Vec2(350, 530));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(50);
    //设置CheckBox是否可点击
    manCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    auto bool selected  = manCheckBox->getSelectedState();
    manCheckBox->addEventListener(CC_CALLBACK_2(RegisterDetailScene::checkBoxCallback,this));
    addChild(manCheckBox);
    
    auto womanCheckBox = CheckBox::create("message_select_woman.png","select_sure.png");
    //设置CheckBox的位置
    womanCheckBox->setPosition(Vec2(460, 530));
    womanCheckBox->setTag(51);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    womanCheckBox->setTouchEnabled(true);
    womanCheckBox->addEventListener(CC_CALLBACK_2(RegisterDetailScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(womanCheckBox);
    
    return true;
}

TextField*  RegisterDetailScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name1,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto Star = Label::createWithSystemFont("*","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Star->setPosition(30,point.y-5);
    Star->setTextColor(Color4B(205, 133, 147, 255));
    Star->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Star);
    
    auto textFieldUser = TextField::create(name2,"Arial",35);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(visibleSize.width-300, 50));
    textFieldUser->setPosition(Vec2(visibleSize.width-70,point.y));
    textFieldUser->setAnchorPoint(Vec2(1,0));
    textFieldUser->setContentSize(Size(visibleSize.width-300,50));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->addEventListener(CC_CALLBACK_2(RegisterDetailScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}



//实现CheckBox回调函数
void RegisterDetailScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    MenuItem* item = (MenuItem*)ref;
    int tag= item->getTag();
    CheckBox *checkBox;
    if (tag==50) {
        checkBox=(CheckBox*)this->getChildByTag(51);
    }else{
        checkBox=(CheckBox*)this->getChildByTag(50);
    }
    //     bool selected  = checkBox->getSelectedState();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}


void RegisterDetailScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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



Layer* RegisterDetailScene::createAlbumLayer(){
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

#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "RegisterScene.hpp"
#include "PerfectCaseScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

Scene* LoginScene::createScene()
{
    return LoginScene::create();
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
    
    CCLOG("%f",visibleSize.width);
    CCLOG("%f",visibleSize.height
          );
    
    auto bkView = Sprite::create("login_bk.png");
    bkView->setAnchorPoint(Vec2(0,0));
    bkView->setPosition(Vec2(0,0));
    bkView->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(bkView);
    
    auto bg_input_account  = Sprite::create("bg_input_account.png");
    bg_input_account->setAnchorPoint(Vec2(0,0));
    bg_input_account->setPosition(Vec2(50,721));
    bg_input_account->setContentSize(Size(540,70));
    this->addChild(bg_input_account);
    
    auto bg_input_passwd  = Sprite::create("bg_input_passwd.png");
    bg_input_passwd->setAnchorPoint(Vec2(0,0));
    bg_input_passwd->setPosition(Vec2(50,614));
    bg_input_passwd->setContentSize(Size(540,70));
    this->addChild(bg_input_passwd);
    
    auto textFieldName = TextField::create("请输入账户名","Arial",30);
    textFieldName->setMaxLength(40);
    textFieldName->setTouchSize(Size(400, 54));
    textFieldName->setAnchorPoint(Vec2(0,0));
    textFieldName->setPosition(Vec2(130,735));
    textFieldName->setContentSize(Size(400,54));
    textFieldName->setTextColor(Color4B::BLACK);
    textFieldName->addEventListener(CC_CALLBACK_2(LoginScene::eventCallBack, this));
    this->addChild(textFieldName);
   
    auto textFieldPasswd = TextField::create("请输入密码","Arial",30);
    textFieldPasswd->setMaxLength(40);
    textFieldPasswd->setTouchSize(Size(400, 54));
    textFieldPasswd->setAnchorPoint(Vec2(0,0));
    textFieldPasswd->setPosition(Vec2(130,637));
    textFieldPasswd->setContentSize(Size(400,54));
    textFieldPasswd->setTextColor(Color4B::BLACK);
    textFieldPasswd->addEventListener(CC_CALLBACK_2(LoginScene::eventCallBack, this));
    this->addChild(textFieldPasswd);
    
    
    auto LoginBtn = Menu::create();
    LoginBtn->setAnchorPoint(Vec2(0,0));
    LoginBtn->setPosition(Vec2(50,458));
    //LoginBtn->setContentSize(Size(100,68));
    this->addChild(LoginBtn);
    auto loginMenuItem  = MenuItemImage::create("btn_login.png","btn_login.png",CC_CALLBACK_1(LoginScene::menuLoginCallback, this));
    loginMenuItem->setAnchorPoint(Vec2(0,0));
    loginMenuItem->setPosition(Vec2(0,0));
    loginMenuItem->setTag(100);
    loginMenuItem->setScale(0.87);
    LoginBtn->addChild(loginMenuItem);
    
    
    auto registerBtn = Menu::create();
    registerBtn->setAnchorPoint(Vec2(0,0));
    registerBtn->setPosition(Vec2(50,99));
    this->addChild(registerBtn);
    auto registerMenuItem  = MenuItemImage::create("btn_register.png","btn_register.png",CC_CALLBACK_1(LoginScene::menuLoginCallback, this));
    registerMenuItem->setAnchorPoint(Vec2(0,0));
    registerMenuItem->setTag(101);
    registerMenuItem->setPosition(Vec2(0,0));
    registerMenuItem->setScale(0.87);
    registerBtn->addChild(registerMenuItem);

    
    return true;
}




void LoginScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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


void LoginScene::menuLoginCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    int tag= item->getTag();
    if (tag==101) {
        auto registerScene=RegisterScene::createScene();
        Director::getInstance()->pushScene(registerScene);
    }
    if (tag==100) {
        auto perfectSC=PerfectCaseScene::create();
        Director::getInstance()->pushScene(perfectSC);
    }

}

#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "WelcomeScene.hpp"

using namespace rapidjson; // 命名空间


#include "NetWrokMangerData.hpp"
#include "RegisterScene.hpp"
#include "PerfectCaseScene.hpp"

#include "ui/UIWebView.h"


using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d;

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
    this->createHudView();
    return true;
}

TextField *userName;
TextField *password;
void LoginScene::createHudView(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
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
    loginMenuItem->setTag(100);
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
    registerMenuItem->setTag(101);
    registerBtn->addChild(registerMenuItem);
    
//    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    
    
    
//    using rapidjson::Value;
//    rapidjson::Document Jsondata;
//
//     Value item(Type::kObjectType);
//
//    using rapidjson::Document;
//    Document doc;
//    string      stringFromStream;
//
//    auto & contents =doc["content"];;
//    item.AddMember("key", "word5",Jsondata.GetAllocator());
//    item.AddMember("value", "单词5",Jsondata.GetAllocator());
//    contents.PushBack(item, Jsondata.GetAllocator());
//
//    StringBuffer buffer;      // in rapidjson/stringbuffer.h
//    Writer<StringBuffer> writer(buffer); // in rapidjson/writer.h
//    Jsondata.Accept(writer);
//
//    CCLOG("%s",buffer.GetString());
//
//
    
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("int", 1, allocator);
    object.AddMember("double", 1.0, allocator);
    object.AddMember("bool", true, allocator);
    object.AddMember("hello", "HelloWorld", allocator);
    array.PushBack(object, allocator);

    document.AddMember("json", array, allocator);

    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    
    
    CCLOG("%s", buffer.GetString());
    
    CCDictionary * pDict = CCDictionary::create();
    
    pDict->setObject(CCString::create("value1"), "key1");
    
    pDict->setObject(CCString::create("value2"), "key2");
    
    
    CCLOG("%s",pDict->valueForKey("key1")->getCString());
    CCLOG("%s",pDict->valueForKey("key2")->getCString());
    
    
    for(int i =0 ;i<pDict->allKeys()->count();i++){
        
        CCString *str =(CCString*)pDict->allKeys()->getObjectAtIndex(i);

        CCLOG("%s",str->getCString());
        
        CCLOG("%s",pDict->valueForKey(str->getCString())->getCString());
    }

//    netManeger->sendMessage("http://api2.innfinityar.com/web/getArtist",CC_CALLBACK_2(LoginScene::onHttpRequestCompleted, this),(char *)buffer.GetString());
    
    userName = TextField::create("请输入账户名","Arial",30);
    userName->setMaxLength(40);
    userName->setTouchSize(Size(400, 54));
    userName->setAnchorPoint(Vec2(0,0));
    userName->setPosition(Vec2(130,735));
    userName->setContentSize(Size(400,54));
    userName->setTextColor(Color4B::BLACK);
    userName->addEventListener(CC_CALLBACK_2(LoginScene::eventCallBack, this));
    this->addChild(userName);
    
    password = TextField::create("请输入密码","Arial",30);
    password->setMaxLength(40);
    password->setTouchSize(Size(400, 54));
    password->setAnchorPoint(Vec2(0,0));
    password->setPosition(Vec2(130,637));
    password->setContentSize(Size(400,54));
    password->setTextColor(Color4B::BLACK);
    password->addEventListener(CC_CALLBACK_2(LoginScene::eventCallBack, this));
    this->addChild(password);
    
    
 //   webView
    
//    auto webView = cocos2d::experimental::ui::WebView::create();
//    webView->loadURL("http://www.baidu.com");
//    webView->setContentSize(Size(visibleSize.width, visibleSize.height));
//    webView->setAnchorPoint(Vec2(0,0));
//    webView->setPosition(Vec2(0,0));
//    this->addChild(webView);
//
}

void LoginScene::saveData(rapidjson::Value& object,int type){
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    loginData.Accept(writer);
    CCLOG("%s", buffer.GetString());
    
//    UserDefault::getInstance()->deleteValueForKey("DrawPassWord");
   
    UserDefault::getInstance()->setStringForKey("id",object["id"].GetString());
    UserDefault::getInstance()->setStringForKey("name",object["name"].GetString());
    UserDefault::getInstance()->setStringForKey("userId",object["userId"].GetString());
    UserDefault::getInstance()->setStringForKey("passwd",object["passwd"].GetString());
    if (type==1) {
         UserDefault::getInstance()->setStringForKey("isLock", object["isLock"].GetString());
       UserDefault::getInstance()->setStringForKey("groupId",object["groupId"].GetString());
         if (!object["isleader"].IsNull()) {
//             string isleader=CCString::createWithFormat("%d",object["isleader"].GetInt())->getCString();
             UserDefault::getInstance()->setIntegerForKey("isleader",object["isleader"].GetInt());
             UserDefault::getInstance()->setStringForKey("role",object["role"].GetString());
             log("role:%s",object["role"].GetString());
         }
    }
}

void LoginScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
   // rapidjson::Document Jsondata;
    
    this->loginData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->loginData.HasParseError()) {
        
        return;
    }
    if(this->loginData.HasMember("data")){
//        for(int i = 0; i < this->loginData["data"].Size(); i++) {
            rapidjson::Value& object = this->loginData["data"];
        if (!object.HasMember("groupId")) {
//如果不存在此参数
            log("没有此参数");
            saveData(object,0);
            auto userCaseSC=(UserCaseScene*)UserCaseScene::create();
            userCaseSC->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
            Director::getInstance()->replaceScene(userCaseSC);
        }
      else  if (!object["groupId"].IsNull()) {
//如果此参数不为空
           CCLOG("%s", object["groupId"].GetString());
          saveData(object,1);
          auto doctorSC=WelcomeScene::create();
          Director::getInstance()->replaceScene(doctorSC);
        }
//        }
    }else{
        Size visibleSize= Director::getInstance()->getVisibleSize();
        auto judgeV = Label::createWithSystemFont("登录失败","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
        judgeV->setPosition(Vec2(visibleSize.width/2, 568));
        judgeV->setTextColor(Color4B(91, 144, 229, 255));
        judgeV->setAnchorPoint(Vec2(0.5, 0));
        this->addChild(judgeV,10);
        judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
    }

//    this->printLog();
}
#pragma-用于加载网络数据

void LoginScene::pushDataToNetWork(string username,string passwd){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"userId=%s&passwd=%s",username.c_str(),passwd.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/userLogin";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(LoginScene::onHttpRequestCompleted, this),url);
}


void LoginScene::printLog()
{
    
    CCLOG("%d",this->loginData["data"].Size());
    
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
         Size visibleSize=Director::getInstance()->getVisibleSize();
        if (strcmp(userName->getString().c_str(), "")==0) {
            auto judgeV = Label::createWithSystemFont("请输入您的账号","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
            judgeV->setPosition(Vec2(visibleSize.width/2, 568));
            judgeV->setTextColor(Color4B(91, 144, 229, 255));
            judgeV->setAnchorPoint(Vec2(0.5, 0));
            this->addChild(judgeV,10);
            judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
        }else if(strcmp(password->getString().c_str(), "")==0){
            auto judgeV = Label::createWithSystemFont("请输入您的密码","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
            judgeV->setPosition(Vec2(visibleSize.width/2, 568));
            judgeV->setTextColor(Color4B(91, 144, 229, 255));
            judgeV->setAnchorPoint(Vec2(0.5, 0));
            this->addChild(judgeV,10);
            judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
        }else {
     pushDataToNetWork(userName->getString(), password->getString());
        }
    }

}

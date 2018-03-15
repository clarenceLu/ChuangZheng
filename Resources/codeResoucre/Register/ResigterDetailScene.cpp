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

using namespace rapidjson; // 命名空间
#include "NetWrokMangerData.hpp"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *RegisterDetailScene::createScene(){
    return RegisterDetailScene::create();
}

//data
TextField* textfieldName;
TextField* textfieldPass;
TextField* textfieldSurePass;
TextField* textfieldTel;
TextField* textfieldCaseTel2;
TextField* textfieldCaseAddress;
TextField* textfieldCaseRefer;
string sexLB;

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
    sureBtn->setPosition(Vec2(visibleSize.width/2-120, 60));
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->setScale(0.70);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //在这里请求接口
            if (textfieldPass->getStringLength()<6) {
                auto judgeV = Label::createWithSystemFont("您设置的密码位数少于6位","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else if(strcmp(textfieldPass->getString().c_str(), textfieldSurePass->getString().c_str())){
                auto judgeV = Label::createWithSystemFont("您输入的密码前后不一样","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else{
                pushDataToNetWork(textfieldName->getString(),textfieldPass->getString(),textfieldName->getString(),sexLB,"",textfieldTel->getString(),textfieldCaseTel2->getString(),"",textfieldCaseAddress->getString(),"","");
            }
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    textfieldName=createBasicData(bkView, Vec2(59, 768), "姓名：", "张牧之");
    textfieldPass=createBasicData(bkView, Vec2(59, 688), "密码：", "未填写");
     textfieldPass->setPasswordEnabled(true);
     textfieldSurePass=createBasicData(bkView, Vec2(59, 608), "确认密码：", "未填写");
     textfieldSurePass->setPasswordEnabled(true);
     textfieldTel=createBasicData(bkView, Vec2(59, 448), "联系电话：", "未填写");
     textfieldCaseTel2=createBasicData(bkView, Vec2(59, 368), "手机：", "未填写");
     textfieldCaseAddress=createBasicData(bkView, Vec2(59, 288), "家庭住址：", "未填写");
      textfieldCaseRefer=createBasicData(bkView, Vec2(59, 208), "推荐人：", "");
    
    auto scanBtn=Button::create();
    scanBtn->loadTextures("alpha.png", "alpha.png");
    scanBtn->setTitleText("点击扫描");
    scanBtn->setTitleColor(Color3B(51, 145, 233/2));
    scanBtn->setTitleFontSize(33);
    scanBtn->setPosition(Vec2(visibleSize.width-90, 215));
    scanBtn->setAnchorPoint(Vec2(1, 0));
    scanBtn->setScale9Enabled(true);
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
    
    auto manCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    manCheckBox->setPosition(Vec2(340, 530));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(50);
    //设置CheckBox是否可点击
    manCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    auto bool selected  = manCheckBox->getSelectedState();
    manCheckBox->addEventListener(CC_CALLBACK_2(RegisterDetailScene::checkBoxCallback,this));
    addChild(manCheckBox);
    auto manLB= Label::createWithSystemFont("男","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    manLB->setPosition(Vec2(380, 530));
    manLB->setTextColor(Color4B::GRAY);
    manLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(manLB);
    
    auto womanCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    womanCheckBox->setPosition(Vec2(460, 530));
    womanCheckBox->setTag(51);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    womanCheckBox->setTouchEnabled(true);
    womanCheckBox->addEventListener(CC_CALLBACK_2(RegisterDetailScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(womanCheckBox);
    auto womanLB= Label::createWithSystemFont("女","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    womanLB->setPosition(Vec2(500, 530));
    womanLB->setTextColor(Color4B::GRAY);
    womanLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(womanLB);
    
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
            if (tag==50) {sexLB="M";}     else{sexLB="F";}
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


#pragma-用于加载网络数据
std::string RegisterDetailScene::getTimeForSystem(){
    //获取系统时间
    struct timeval now;
    struct tm *time;
    gettimeofday(&now, NULL);
    time = localtime(&now.tv_sec);      //microseconds: 微秒
    int year = time->tm_year +1900;
    log("year = %d", year);         //显示年份
    char date1[32] = {0};
    sprintf(date1, "%d %02d %02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday);
    log("%s", date1);        //显示年月日
    char date2[50] = {0};
    sprintf(date2, "%02d %02d %02d", (int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
    log("%s", date2);       //显示时分秒
    char date[100] = {0};
    sprintf(date, "%d%d%d%d%d%d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday,(int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
    return date;
    
}

void RegisterDetailScene::pushDataToNetWork(string username,string passwd,string name,string sex,string age,string phone,string phone1,string idCardNo,string address,string headUrl,string caseNo){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
sprintf(memberUrl,"userId=%s&passwd=%s&name=%s&sex=%s&phone=%s&phone1=%s&address=%s&caseNo=%s",username.c_str(),passwd.c_str(),name.c_str(),sex.c_str(),phone.c_str(),phone1.c_str(),address.c_str(),getTimeForSystem().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/createUser";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(RegisterDetailScene::onHttpRequestCompleted, this),url);
}

void RegisterDetailScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
        log("注册成功");
        Director::getInstance()->popToRootScene();
        
    }else{
        Size visibleSize=Director::getInstance()->getVisibleSize();
        auto judgeV = Label::createWithSystemFont("用户名重复","Arial",35,Size(visibleSize.width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
        judgeV->setPosition(Vec2(visibleSize.width/2+100, 268));
        judgeV->setTextColor(Color4B(91, 144, 229, 255));
        judgeV->setAnchorPoint(Vec2(0, 0));
        this->addChild(judgeV);
        judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
    }
    
}




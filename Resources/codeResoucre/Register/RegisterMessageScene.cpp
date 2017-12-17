
#include "RegisterMessageScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>

using namespace rapidjson; // 命名空间
#include "NetWrokMangerData.hpp"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *RegisterMessageScene::createScene(){
    return RegisterMessageScene::create();
}

//data
TextField* textFieldUser;
TextField* textFieldPass;
TextField* textFieldSurePass;
TextField* textFieldName;
TextField*textFieldAge;
TextField*textFieldNum;
TextField*textFieldCard;
string sex;



Sprite* bkView;
bool RegisterMessageScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    bkView=Sprite::create("bk_register_message.png");
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
    
    textFieldUser = TextField::create("未填写","Arial",33);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(400, 54));
    textFieldUser->setAnchorPoint(Vec2(1,0));
    textFieldUser->setPosition(Vec2(560,800));
    textFieldUser->setContentSize(Size(400,54));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldUser);
    
    textFieldPass = TextField::create("未填写","Arial",33);
    textFieldPass->setMaxLength(40);
    textFieldPass->setTouchSize(Size(400, 54));
    textFieldPass->setAnchorPoint(Vec2(1,0));
    textFieldPass->setPosition(Vec2(560,715));
    textFieldPass->setContentSize(Size(400,54));
    textFieldPass->setPasswordEnabled(true);
    textFieldPass->setTextColor(Color4B::BLACK);
    textFieldPass->setPlaceHolderColor(Color4B::GRAY);
    textFieldPass->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldPass->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldPass);
    
    textFieldSurePass = TextField::create("未填写","Arial",33);
    textFieldSurePass->setMaxLength(40);
    textFieldSurePass->setTouchSize(Size(400, 54));
    textFieldSurePass->setAnchorPoint(Vec2(1,0));
    textFieldSurePass->setPosition(Vec2(560,632));
    textFieldSurePass->setContentSize(Size(400,54));
     textFieldSurePass->setPasswordEnabled(true);
    textFieldSurePass->setTextColor(Color4B::BLACK);
    textFieldSurePass->setPlaceHolderColor(Color4B::GRAY);
    textFieldSurePass->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldSurePass->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldSurePass);
    
    textFieldName= TextField::create("未填写","Arial",33);
    textFieldName->setMaxLength(40);
    textFieldName->setTouchSize(Size(400, 54));
    textFieldName->setAnchorPoint(Vec2(1,0));
    textFieldName->setPosition(Vec2(560,550));
    textFieldName->setContentSize(Size(400,54));
    textFieldName->setTextColor(Color4B::BLACK);
    textFieldName->setPlaceHolderColor(Color4B::GRAY);
    textFieldName->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldName->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldName);
    
     textFieldAge= TextField::create("未填写","Arial",33);
    textFieldAge->setMaxLength(40);
    textFieldAge->setTouchSize(Size(400, 54));
    textFieldAge->setAnchorPoint(Vec2(1,0));
    textFieldAge->setPosition(Vec2(560,385));
    textFieldAge->setContentSize(Size(400,54));
    textFieldAge->setTextColor(Color4B::BLACK);
    textFieldAge->setPlaceHolderColor(Color4B::GRAY);
    textFieldAge->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldAge->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldAge);
    
    textFieldNum= TextField::create("未填写","Arial",33);
    textFieldNum->setMaxLength(40);
    textFieldNum->setTouchSize(Size(400, 54));
    textFieldNum->setAnchorPoint(Vec2(1,0));
    textFieldNum->setPosition(Vec2(560,305));
    textFieldNum->setContentSize(Size(400,54));
    textFieldNum->setTextColor(Color4B::BLACK);
    textFieldNum->setPlaceHolderColor(Color4B::GRAY);
    textFieldNum->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldNum->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldNum);
    
     textFieldCard= TextField::create("未填写","Arial",33);
    textFieldCard->setMaxLength(40);
    textFieldCard->setTouchSize(Size(400, 54));
    textFieldCard->setAnchorPoint(Vec2(1,0));
    textFieldCard->setPosition(Vec2(560,225));
    textFieldCard->setContentSize(Size(400,54));
    textFieldCard->setTextColor(Color4B::BLACK);
    textFieldCard->setPlaceHolderColor(Color4B::GRAY);
    textFieldCard->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldCard->addEventListener(CC_CALLBACK_2(RegisterMessageScene::eventCallBack, this));
    this->addChild(textFieldCard);
    
    
    auto manCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    manCheckBox->setPosition(Vec2(340, 470));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(50);
    //设置CheckBox是否可点击
    manCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    auto bool selected  = manCheckBox->getSelectedState();
    manCheckBox->addEventListener(CC_CALLBACK_2(RegisterMessageScene::checkBoxCallback,this));
    addChild(manCheckBox);
    auto manLB= Label::createWithSystemFont("男","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    manLB->setPosition(Vec2(380, 470));
    manLB->setTextColor(Color4B::GRAY);
    manLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(manLB);
    
    auto womanCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    womanCheckBox->setPosition(Vec2(460, 470));
    womanCheckBox->setTag(51);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    womanCheckBox->setTouchEnabled(true);
     womanCheckBox->addEventListener(CC_CALLBACK_2(RegisterMessageScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(womanCheckBox);
    auto womanLB= Label::createWithSystemFont("女","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    womanLB->setPosition(Vec2(500, 470));
    womanLB->setTextColor(Color4B::GRAY);
    womanLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(womanLB);
    

        auto referrer = Label::createWithSystemFont("推荐人","Arial",32,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        referrer->setPosition(Vec2(80, 140));
        referrer->setTextColor(Color4B(51, 145, 233, 255));
        referrer->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(referrer);
        
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(70, 140-6));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setScaleX(0.78);
        bkView->addChild(lineV);
    
    auto scanBtn=Button::create();
    scanBtn->loadTextures("alpha.png", "alpha.png");
    scanBtn->setTitleText("点击扫描");
    scanBtn->setTitleColor(Color3B(51, 145, 233/2));
    scanBtn->setTitleFontSize(33);
    scanBtn->setPosition(Vec2(visibleSize.width-110, 150));
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
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_perfect_sure.png", "btn_perfect_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width/2-115, 50));
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->setScale(0.70);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //在这里请求接口
            if (textFieldPass->getStringLength()<6) {
                auto judgeV = Label::createWithSystemFont("您设置的密码位数少于6位","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else if(strcmp(textFieldPass->getString().c_str(), textFieldSurePass->getString().c_str())){
                auto judgeV = Label::createWithSystemFont("您输入的密码前后不一样","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else{
                    pushDataToNetWork(textFieldUser->getString(),textFieldSurePass->getString(),textFieldName->getString(),sex,textFieldAge->getString(),textFieldNum->getString(),"",textFieldCard->getString(),"","","");
            }
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    return true;
}



//实现CheckBox回调函数
void RegisterMessageScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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
            if (tag==50) {sex="M";}else{sex="F";}
            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}


void RegisterMessageScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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


Layer* RegisterMessageScene::createAlbumLayer(){
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

void RegisterMessageScene::pushDataToNetWork(string username,string passwd,string name,string sex,string age,string phone,string phone1,string idCardNo,string address,string headUrl,string caseNo){
     NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
        char strtest[500] = {0};
        sprintf(strtest,"http://czapi.looper.pro/web/createUser?userId=%s&passwd=%s&name=%s&sex=%s&number=%s&phone=%s&idCardNo=%s", username.c_str(),passwd.c_str(),name.c_str(),sex.c_str(),age.c_str(),phone.c_str(),idCardNo.c_str());
        string url=strtest;
        
    netManeger->sendMessage(url,CC_CALLBACK_2(RegisterMessageScene::onHttpRequestCompleted, this),nullptr);
}

void RegisterMessageScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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




/*
 auto man=Sprite::create("message_select_man.png");
 man->setPosition(Vec2(350, 470));
 man->setAnchorPoint(Vec2(0, 0));
 this->addChild(man);
 
 auto manBtn=Button::create();
 manBtn->loadTextures("select_sure.png", "select_sure.png");
 manBtn->setPosition(Vec2(380, 500));
 manBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
 case ui::Widget::TouchEventType::BEGAN: break;
 case ui::Widget::TouchEventType::ENDED:
 
 default:
 break;
 }
 });
 this->addChild(manBtn);
 
 auto woman=Sprite::create("message_select_woman.png");
 woman->setPosition(Vec2(460, 470));
 woman->setAnchorPoint(Vec2(0, 0));
 this->addChild(woman);
 
 auto womanBtn=Button::create();
 womanBtn->loadTextures("select_sure.png", "select_sure.png");
 womanBtn->setPosition(Vec2(490, 500));
 womanBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
 case ui::Widget::TouchEventType::BEGAN: break;
 case ui::Widget::TouchEventType::ENDED:
 default:
 break;
 }
 });
 this->addChild(womanBtn);
 */

//
//  ChatUserDetailScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/11.
//

#include "ChatUserDetailScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SelectStep3Scene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *ChatUserDetailScene::createScene(){
    return ChatUserDetailScene::create();
}
bool ChatUserDetailScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_chat_userdetail.png");
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
    
    scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0, 30));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 950));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 255, 255));//设置背景颜色
    
    bkView->addChild(scrollView);
    return true;
};

void ChatUserDetailScene::onEnter(){
    Scene::onEnter();
    getUserDataToNetWork();
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    infoData.Accept(writer);
    CCLOG("%s", buffer.GetString());
    
}

void ChatUserDetailScene::createScrollDetailView(ScrollView* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    rapidjson::Value& data = infoData["data"];
    
    auto bkView=Sprite::create("alpha.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, 950));
    superV->addChild(bkView);
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(244, 815));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
    float height3=headBtn->getContentSize().height;
    headBtn->setScale(151.0/height3);
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            log("点击上传头像");
            Layer *layer= createAlbumLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
    });
    string name="佚名";
    string caseNo="未知";
    string sex="男";
    string age="未知";
    string  contentStr="自述：";
    if(!data["name"].IsNull()){
        name=data["name"].GetString();
    } if(!data["caseNo"].IsNull()){
        caseNo=data["caseNo"].GetString();
    } if(!data["sex"].IsNull()){
               if (strcmp(data["sex"].GetString(), "F")==0) {sex="女";}
    } if(!data["age"].IsNull()){
        age=data["age"].GetString();
    }
    if (!data["step1"].IsNull()) {
        log("step1:%s",data["step1"].GetString());
        contentData.Parse<rapidjson::kParseNoFlags>(infoData["data"]["step1"].GetString());
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        contentData.Accept(writer);
        CCLOG("%s", buffer.GetString());
            contentStr=searchContentForInfoData(contentStr, "step1：",contentData);
    }if (!data["step2"].IsNull()) {
        contentStr.append(data["step2"].GetString());
    }
    createLabel(Vec2(0, 758), "真实姓名：", name, bkView);
    createLabel(Vec2(0, 678), "病历号：", caseNo, bkView);
    createLabel(Vec2(0, 598), "性别：", sex, bkView);
    createLabel(Vec2(0, 518), "年龄：", age, bkView);
    float height= createLabel(Vec2(0, 438), "自述症状：", contentStr, bkView);

    auto imageLB = Label::createWithSystemFont("影像：","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    imageLB->setPosition(Point(56,400-height));
    imageLB->setTextColor(Color4B(91,144,230, 255));
    imageLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(imageLB);
    float currentHeight=0;
    for (int i=0; i<12; i++) {
        if (i==12-1) {
            auto imageBtn1=ImageView::create("btn_chat_userImage.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 320-height+10));
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 320-height-(int)((width-154)/(visibleSize.width-154))*150+10));
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->setScale(0.87);
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    auto updateLayer=createUpdateImageLayer();
                    this->addChild(updateLayer);
                }
            });
            currentHeight=975-(320-height-(int)((width-154)/(visibleSize.width-154))*150);
        }else{
            auto imageBtn1=ImageView::create("bk_headIV.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 320-height));
                //                 log("width:%d,height:%f i的值%d,屏幕宽度%f",154+150*(i%3),320-height-(int)(width/(int)visibleSize.width)*150,i,visibleSize.width);
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 320-height-(int)((width-154)/(visibleSize.width-154))*150));
                //                log("width:%d,height:%f i的值%d,总长度:%d",154+150*(i%3),320-height-(int)((width-154)/(visibleSize.width-154))*150,i,width);
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            float height2=imageBtn1->getContentSize().height;
            imageBtn1->setScale(125.0/height2);
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    log("点击查看照片");
                }
            });
        }
    }
    superV->setInnerContainerSize(Size(visibleSize.width, currentHeight+30));
    
    bkView->setPosition(Vec2(0, currentHeight-960));
    
}

std::string ChatUserDetailScene::searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data){
    if (data.IsObject()) {
        content.append(title);
        for (auto j=data.MemberBegin(); j!=data.MemberEnd(); ++j) {
            auto key = (j->name).GetString();
            if (data[key].Size()) {
                if (strcmp(key, "chooseKey")==0) {
                    content.append("手脚、胳膊、腿");
                }else  if (strcmp(key, "headKey")==0) {
                    content.append("疼痛程度");
                }else  if (strcmp(key, "lastKey")==0) {
                    content.append("症状补充");
                }else  if (strcmp(key, "milStringKey")==0) {
                    content.append("一口气做多走(单位:米)");
                }else{
                content.append(key);
                }
                content.append(":");
                //仅修改棘突异常
            }
            log("key:%s", key);
            for(auto i = 0; i < data[key].Size(); ++i){
                content.append(data[key][i].GetString());
                if (i==data[key].Size()-1&&j==data.MemberEnd()-1) {}else{
                    content.append(" ");}
                //仅修改棘突异常
                if (i==data[key].Size()-1) {
                    if (strcmp(title.c_str(), "棘突：")==0) {
                        content.append("）");
                    }
                }
                
                log("%s", data[key][i].GetString());
            }
        }
        content.append(";");
    }else if(data.IsArray()){
        if (data.Size()>0) {
            content.append(title);
        }
        for(auto i = 0; i < data.Size(); ++i){
            content.append(data[i].GetString());
            content.append(" ");
            log("%s", data[i].GetString());
        }
        if (data.Size()>0) {
            content.append(";");
        }
    }
    log("content：%s",content.c_str());
    return content;
}

Layer* ChatUserDetailScene::createAlbumLayer(){
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
Layer* ChatUserDetailScene::createUpdateImageLayer(){
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
    
    
    auto bkView=Sprite::create("bk_updateImageLayer.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    layer->addChild(bkView);
    
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
    bkView->addChild(backBtn);
    
    auto updateBtn=Button::create();
    updateBtn->loadTextures("btn_updateImage.png", "btn_updateImage.png");
    updateBtn->setPosition(Vec2(visibleSize.width/2, 486));
    updateBtn->setScale(0.87);
    updateBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto step3SC=SelectStep3Scene::create();
            Director::getInstance()->pushScene(step3SC);
        }
    
        default:
            break;
    }
    });
    bkView->addChild(updateBtn);
    
    return layer;
    
}

float ChatUserDetailScene::createLabel(Vec2 point,string name1,string name2,Sprite* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto nameLB = Label::createWithSystemFont(name1,"fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(56,point.y));
    nameLB->setTextColor(Color4B(91,144,230, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB);
    
    auto nameLB2 = Label::createWithSystemFont(name2,"Arial",35,Size(visibleSize.width-265,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
     float height=nameLB2->getContentSize().height;
    nameLB2->setPosition(Point(218,point.y+41-height));
    nameLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    nameLB2->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB2);
    
    return height;
}



#pragma-个人资料界面
void ChatUserDetailScene::getUserDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getUserById?patientId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(ChatUserDetailScene::onHttpRequestCompleted2, this),nullptr);
}

void ChatUserDetailScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    // rapidjson::Document Jsondata;
    
    infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        if (this->infoData["status"].GetInt()==0) {
            scrollView->removeAllChildren();
           createScrollDetailView(scrollView);
            }
        }
}

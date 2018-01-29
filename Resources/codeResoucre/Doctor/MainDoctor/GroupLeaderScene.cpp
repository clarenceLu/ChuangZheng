//
//  GroupLeaderScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/28.
//

#include "GroupLeaderScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>

#include "NetWrokMangerData.hpp"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *GroupLeaderScene::createScene(){
    return GroupLeaderScene::create();
}
bool GroupLeaderScene::init(){
    if (!Scene::init()) {
        return false;
    }
//#pragma-ValueVector加入数据
//    ValueVector vector1;
//    vector1.push_back(Value("小白"));
//    vector1.push_back(Value("老白"));
//    vector1.push_back(Value("小黑"));
//    vector1.push_back(Value("小小黑"));
//    string key1 = "医疗组成员";
//    ValueVector vector2;
//    vector2.push_back(Value("小黄"));
//    vector2.push_back(Value("小小白"));
//    vector2.push_back(Value("大白"));
//    string key2 = "组员申请列表";
//#pragma-ValueMap加入数据
//    map1[key1] = Value(vector1).asValueVector();
//    map1[key2]=Value(vector2).asValueVector();

    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_group_leader.png");
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
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_group_leader_sure.png", "btn_group_leader_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=createPromptLayer("确认将该医生加入医疗组吗？");
            layer->setTag(2001);
            this->addChild(layer);
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    pushDataToNetWork();
    return true;
}
ScrollView* GroupLeaderScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setAnchorPoint(Vec2(0, 1));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setTag(10000);
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    moveView=Sprite::create("alpha.png");
    moveView->setAnchorPoint(Vec2(0, 1));
    moveView->setContentSize(visibleSize);
    scrollView->addChild(moveView);
    
    auto userName = Label::createWithSystemFont("所属医疗组：","Arial",38,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(40,visibleSize.height));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 1));
    moveView->addChild(userName);
    auto userLB = Label::createWithSystemFont(UserDefault::getInstance()->getStringForKey("name"),"Arial",38,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userLB->setPosition(Vec2(300,visibleSize.height));
    userLB->setTextColor(Color4B(0, 0, 0, 255/2));
    userLB->setAnchorPoint(Vec2(0, 1));
    moveView->addChild(userLB);
    
    float pointY1 =createPopUpView(Vec2(40, visibleSize.height-80), moveView, "医疗组成员",0,2);
    ValueVector vect=map1.at("医疗组成员").asValueVector();
    int index=vect.size();
    float pointY2 =createPopUpView(Vec2(40, pointY1+60*index), moveView, "组员申请列表",index,1);
    
#warning -在这里设置没有用，因为当innerSize<contentSize，以contentSize为准
    if (visibleSize.height>visibleSize.height-20-pointY2) {
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height-20-pointY2));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY2));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }else{
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY2));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }
    log("%f,%f",scrollView->getInnerContainerSize().height,visibleSize.height-20-pointY2);
    return scrollView;
}


float GroupLeaderScene::createPopUpView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
#pragma-ValueMap取值
    ValueVector vect=map1.at(name).asValueVector();
    long index=vect.size();
    
    auto wholeV=Sprite::create("alpha.png");
    wholeV->setPosition(Vec2(0,0));
    wholeV->setAnchorPoint(Vec2(0, 0));
    wholeV->setContentSize(Size(visibleSize.width, point.y));
    wholeV->setTag(200+tag);
    bkView->addChild(wholeV);
#pragma-Map<int, Sprite*> wholeDic加入字典
    wholeDic.insert(tag, wholeV);
    
    auto whiteV=Sprite::create("usercase_whiterect.png");
    whiteV->setPosition(Vec2(point.x, point.y-60*(index+1)));
    whiteV->setAnchorPoint(Vec2(0, 0));
    whiteV->setContentSize(Size(visibleSize.width-80, 60*(index+1)));
    whiteV->setTag(tag+200);
    whiteV->setVisible(false);
    wholeV->addChild(whiteV);
#pragma-ValueVector取值
    for (int i=index-1; i>=0; i--) {
        auto whiteStr= vect.at(i).asString();
        creatBlueLabelView(Vec2(0,60*(index-1-i)), whiteV,whiteStr,tag+i,type);
    }
    
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(point.x, point.y-60));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-80, 60));
    wholeV->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    
    
    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_appearance_down.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_appearance_up.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(GroupLeaderScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(Vec2(blueV->getContentSize().width-60,20));  //设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setTag(100+tag);
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    blueV->addChild(box);
    log("%f",point.y-(index+1)*60-20);
    return point.y-(index+1)*60-20;
    
}

float GroupLeaderScene::creatBlueLabelView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(point.x+20, point.y));
    userName->setTextColor(Color4B(0, 0, 0, 255/2));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    if (type==1) {
        auto box = CheckBox::create("btn_appearance_unsure.png","btn_appearance_sure.png");
        //设置CheckBox的位置
        box->setPosition(Vec2(bkView->getContentSize().width-60,point.y+10));
        box->setScale(0.87);
        box->setTag(tag);
        box->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box->setTouchEnabled(true);
        box->addEventListener(CC_CALLBACK_2(GroupLeaderScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box);
        boxDic.insert(tag, box);
    }else if (type==2){
        auto box = CheckBox::create("btn_group_leader_delete.png","btn_group_leader_delete.png");
        //设置CheckBox的位置
        box->setPosition(Vec2(bkView->getContentSize().width-50,point.y+20));
        box->setScale(0.87);
        box->setTag(tag);
        box->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box->setTouchEnabled(true);
        box->addEventListener(CC_CALLBACK_2(GroupLeaderScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box);
    }
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, point.y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.89);
    bkView->addChild(lineV);
    return point.y-20;
}




void GroupLeaderScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    int tag= item->getTag();
    if (index==1) {
#pragma-Map<int, Sprite*> wholeDic取值
        auto wholeV = (Sprite*)wholeDic.at(tag-100);
        auto whiteV=(Sprite*)wholeV->getChildByTag(tag+100);
        whiteV->setVisible(true);
        //判断是否需要移动下方的sprite
        std::vector<int> mapKeyVec;
        mapKeyVec = wholeDic.keys();
        sort(mapKeyVec.begin(), mapKeyVec.end());
        for(int nextTag : mapKeyVec)
        {
            //                    log("%d",nextTag);
            if (nextTag>tag-100) {
                auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y-whiteV->getContentSize().height+60));
            }
        }
        //                log("原先的%f",scrollV->getInnerContainerSize().height);
        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height+whiteV->getContentSize().height-60));
                       log("现在的%f",scrollV->getInnerContainerSize().height);
        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
        scrollV->setInnerContainerPosition(Vec2(0, 60-whiteV->getContentSize().height));
         log("%f",scrollV->getInnerContainerPosition().y);
        if (scrollV->getInnerContainerSize().height<visibleSize.height-190) {
            //用于调整scrollView的contentOffset
            scrollV->setContentSize(Size(visibleSize.width, scrollV->getInnerContainerSize().height));
        }else{
            scrollV->setContentSize(Size(visibleSize.width, visibleSize.height-190));
        }
    }else if (index==0){
        auto wholeV = (Sprite*)wholeDic.at(tag-100);
        auto whiteV=wholeV->getChildByTag(tag+100);
        whiteV->setVisible(false);
        //判断是否需要移动下方的sprite
        std::vector<int> mapKeyVec;
        mapKeyVec = wholeDic.keys();
        sort(mapKeyVec.begin(), mapKeyVec.end());
        for(int nextTag : mapKeyVec)
        {
            log("%d",nextTag);
            if (nextTag>tag-100) {
                auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y+whiteV->getContentSize().height-60));
            }
        }
        scrollV->setContentSize(Size(visibleSize.width, scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
            //用于调整scrollView的contentOffset
        
    }
    
}

cocos2d::Layer* GroupLeaderScene::createPromptLayer(std::string content){
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
    auto contentV = Sprite::create("bk_group_leader_prompt.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(120, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            ValueVector vect=map1.at("医疗组成员").asValueVector();
            int index=vect.size();
        if (currentDeleteIndex<index) {
    //发送删除请求
            rapidjson::Value& object = this->memberData["data"][currentDeleteIndex];
            log("%s",object["name"].GetString());
            pushDeleteToNetWork(object["id"].GetString());
            }else {
     //发送同意申请请求
                    //发送加入请求
                    rapidjson::Value& object = this->applicationData["data"][currentDeleteIndex-index];
                    log("doctorId  %s",object["doctorId"].GetString());
                    pushAffirmToNetWork(object["id"].GetString(),object["doctorId"].GetString());
                
                
            }
            this->removeChildByTag(2001);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(2001);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto contentLB=Label::createWithSystemFont(content,"Arial",36,Size(contentV->getContentSize().width-40,120),TextHAlignment::CENTER,TextVAlignment::CENTER);
    contentLB->setPosition(Vec2(20,120));
    contentLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(contentLB);
    
    return layer;
}

//实现CheckBox回调函数
void GroupLeaderScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    log("tag %d",tag);
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            ValueVector vect=map1.at("医疗组成员").asValueVector();
            int index=vect.size();
            
//            rapidjson::Value& obj = this->memberData["data"][tag];
//             log("%s",obj["name"].GetString());
            if (tag<index) {
                currentDeleteIndex=tag;
                auto layer=createPromptLayer("确认将该医生移出医疗组吗？");
                layer->setTag(2001);
                this->addChild(layer);
            }else{
                currentDeleteIndex=tag;
                log("总数%d 当前%d",index,tag);
                for (int i=index; i<index+boxDic.size(); i++) {
                    CheckBox*box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
        {
        }
            break;
        default:
            break;
    }
}


#pragma-用于加载网络数据
void GroupLeaderScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
//获取医疗组申请
    char strtest[500] = {0};
    sprintf(strtest,"http://czapi.looper.pro/web/getGroupApplication?doctorId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string url=strtest;
    netManeger->sendMessage(url,CC_CALLBACK_2(GroupLeaderScene::onHttpRequestCompleted, this),nullptr);
}

void GroupLeaderScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    this->applicationData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->applicationData.HasParseError()) {
        
        return;
    }
    if(this->applicationData.HasMember("data")){
        log("获取医疗组申请");
        ValueVector vector2;
    for(int i = 0; i < this->applicationData["data"].Size(); i++) {
        rapidjson::Value& object = this->applicationData["data"][i];
        vector2.push_back(Value(object["name"].GetString()));
        log("%s",object["id"].GetString());
        }
        string key2 = "组员申请列表";
        map1[key2]=Value(vector2).asValueVector();
         pushMemberToNetWork();
    }
}
#pragma-用于加载网络数据
void GroupLeaderScene::pushMemberToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
        //当type为2时，获取医疗组成员
        char memberUrl[500]={0};
        sprintf(memberUrl,"http://czapi.looper.pro/web/getGroupMember?groupId=%s",UserDefault::getInstance()->getStringForKey("groupId").c_str());
        string memberURL=memberUrl;
        netManeger->sendMessage(memberURL,CC_CALLBACK_2(GroupLeaderScene::onHttpRequestCompleted2, this),nullptr);
}

void GroupLeaderScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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
    
    this->memberData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->memberData.HasParseError()) {
        
        return;
    }
    if(this->memberData.HasMember("data")){
            log("医疗组成员");
            ValueVector vector2;
            for(int i = 0; i < this->memberData["data"].Size(); i++) {
                rapidjson::Value& object = this->memberData["data"][i];
                vector2.push_back(Value(object["name"].GetString()));
            }
            string key2 = "医疗组成员";
            map1[key2]=Value(vector2).asValueVector();
            scrollV=createTableView(Vec2(0, visibleSize.height-170), Size(visibleSize.width, visibleSize.height-190));
            this->addChild(scrollV);
    }
}
#pragma-用于加载网络数据
void GroupLeaderScene::pushDeleteToNetWork(string doctorId){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/removeGroupMember?groupId=%s&doctorId=%s",UserDefault::getInstance()->getStringForKey("groupId").c_str(),doctorId.c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(GroupLeaderScene::onHttpRequestCompleted3, this),nullptr);
}

void GroupLeaderScene::onHttpRequestCompleted3(HttpClient* sender, HttpResponse* response)
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
    
    this->deleteData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->deleteData.HasParseError()) {
        
        return;
    }
    if(this->deleteData.HasMember("status")){
        if (this->deleteData["status"].GetInt()==0) {
//删除数据
            rapidjson::Value& object = this->memberData["data"][currentDeleteIndex];
           memberData["data"].Erase(memberData["data"].Begin()+currentDeleteIndex);
            for (int i=0; i<memberData["data"].Size(); i++) {
                log("%s",memberData["data"][i]["name"].GetString());
            }
            ValueVector vect=map1.at("医疗组成员").asValueVector();
            vect.erase(vect.begin() + currentDeleteIndex);
            map1["医疗组成员"]=Value(vect).asValueVector();
            for (int i=0; i<vect.size(); i++) {
                log("%s",vect.at(i).asString().c_str());
            }
//需要重新刷新界面
            this->removeChildByTag(10000);
            scrollV=createTableView(Vec2(0, visibleSize.height-170), Size(visibleSize.width, visibleSize.height-190));
            this->addChild(scrollV);
            
            log("%s",object["name"].GetString());
          log("删除成功");
        }
        
//        for(int i = 0; i < this->loginData["data"].Size(); i++) {
//            rapidjson::Value& object = this->loginData["data"];
    }
}


void GroupLeaderScene::pushAffirmToNetWork(string requestId,string doctorId){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/updateGroupApplication?groupId=%s&doctorId=%s&requestId=%s",UserDefault::getInstance()->getStringForKey("groupId").c_str(),doctorId.c_str(),requestId.c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(GroupLeaderScene::onHttpRequestCompleted4, this),nullptr);
}

void GroupLeaderScene::onHttpRequestCompleted4(HttpClient* sender, HttpResponse* response)
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
    
    this->affirmData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->affirmData.HasParseError()) {
        
        return;
    }
    if(this->affirmData.HasMember("status")){
        if (this->affirmData["status"].GetInt()==0) {
//同意申请
            this->removeChildByTag(10000);
            pushDataToNetWork();
            log("同意申请");
        }
        
        //        for(int i = 0; i < this->loginData["data"].Size(); i++) {
        //            rapidjson::Value& object = this->loginData["data"];
    }
}




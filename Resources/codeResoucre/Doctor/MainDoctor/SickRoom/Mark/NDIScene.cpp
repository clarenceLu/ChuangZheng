//
//  NDIScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/8.
//

#include "NDIScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *NDIScene::createScene(){
    return NDIScene::create();
}
bool NDIScene::init(){
    if (!Scene::init()) {
        return false;
    }
#pragma-ValueVector加入数据
    createData();
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_NDI.png");
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
            pushDataToNetWork();
            log("NeckJOA sure");
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    scrollV=createTableView(Vec2(0, visibleSize.height-170), Size(visibleSize.width, visibleSize.height-200));
    this->addChild(scrollV);
    return true;
}
ScrollView* NDIScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setAnchorPoint(Vec2(0, 1));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色

    moveView=Sprite::create("alpha.png");
    moveView->setAnchorPoint(Vec2(0, 1));
    moveView->setContentSize(visibleSize);
    scrollView->addChild(moveView);

    float pointY1 =createPopUpView(Vec2(40, visibleSize.height-10), moveView, "疼痛程度",0,1);
    float pointY3 =createPopUpView(Vec2(40, pointY1+60*6), moveView, "个人生活料理(洗澡穿衣等)",6,1);
    float pointY4 =createPopUpView(Vec2(40, pointY3+60*6), moveView, "抬起(拿起)物品",12,1);
    float pointY5 =createPopUpView(Vec2(40, pointY4+60*6), moveView, "阅读",18,1);
    float pointY6 =createPopUpView(Vec2(40, pointY5+60*6), moveView, "头痛",24,1);
    float pointY7 =createPopUpView(Vec2(40, pointY6+60*6), moveView, "集中注意力",30,1);
    float pointY8 =createPopUpView(Vec2(40, pointY7+60*6), moveView, "工作",36,1);
    float pointY9 =createPopUpView(Vec2(40, pointY8+60*6), moveView, "开车或骑车",42,1);
    float pointY10 =createPopUpView(Vec2(40, pointY9+60*7), moveView, "睡眠",49,1);
    float pointY2 =createPopUpView(Vec2(40, pointY10+60*6), moveView, "娱乐休闲",55,1);

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


float NDIScene::createPopUpView(Vec2 point,Sprite* bkView,string name,int tag,int type){
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
    for (int i=0; i<index; i++) {
        auto whiteStr= vect.at(i).asString();
        creatBlueLabelView(Vec2(0,60*i), whiteV,whiteStr,tag+i,type);
    }

    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(point.x, point.y-60));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-80, 60));
    wholeV->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(500,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);


    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_appearance_down.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_appearance_up.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(NDIScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(Vec2(blueV->getContentSize().width-60,20));  //设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setTag(100+tag);
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    blueV->addChild(box);

    return point.y-(index+1)*60-20;

}

float NDIScene::creatBlueLabelView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",25,Size(500,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
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
        box->addEventListener(CC_CALLBACK_2(NDIScene::checkBoxCallback,this));
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
        box->addEventListener(CC_CALLBACK_2(NDIScene::checkBoxCallback,this));
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




void NDIScene::menuLoginCallback(Ref* pSender)
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

//实现CheckBox回调函数
void NDIScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            log("Box tag:%d,boxSize :%ld",tag,boxDic.size());
            if (tag>=0&&tag<6) {
                for (int i=0; i<6; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=6&&tag<12) {
                for (int i=6; i<12; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=12&&tag<18) {
                for (int i=12; i<18; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=18&&tag<24) {
                for (int i=18; i<24; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=24&&tag<30) {
                for (int i=24; i<30; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=30&&tag<36) {
                for (int i=30; i<36; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=36&&tag<42) {
                for (int i=36; i<42; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=42&&tag<49) {
                for (int i=42; i<49; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=49&&tag<55) {
                for (int i=49; i<55; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=55&&tag<61) {
                for (int i=55; i<61; i++) {
                    CheckBox *box=boxDic.at(i);
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


std::string NDIScene::getJsonData(int type)
{
    totalNum=0;
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    if (type==0) {
        rapidjson::Value array(rapidjson::kArrayType);
        rapidjson::Value array2(rapidjson::kArrayType);
        rapidjson::Value array3(rapidjson::kArrayType);
        rapidjson::Value array4(rapidjson::kArrayType);
        rapidjson::Value array5(rapidjson::kArrayType);
        rapidjson::Value array6(rapidjson::kArrayType);
        rapidjson::Value array7(rapidjson::kArrayType);
        rapidjson::Value array8(rapidjson::kArrayType);
        rapidjson::Value array9(rapidjson::kArrayType);
        rapidjson::Value array10(rapidjson::kArrayType);
        for (int i=0; i<boxDic.size(); i++) {
            CheckBox* box=(CheckBox*)boxDic.at(i);
            int tag=box->getTag();
            if (tag>=0&&tag<6) {
                if (box->getSelectedState()) {
                    totalNum+=5-tag;
                    array.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=6&&tag<12) {
                if (box->getSelectedState()) {
                    totalNum+=11-tag;
                    array2.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=12&&tag<18) {
                if (box->getSelectedState()) {
                    totalNum+=17-tag;
                    array3.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=18&&tag<24) {
                if (box->getSelectedState()) {
                    totalNum+=23-tag;
                    array4.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=24&&tag<30) {
                if (box->getSelectedState()) {
                    totalNum+=29-tag;
                    array5.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=30&&tag<36) {
                if (box->getSelectedState()) {
                    totalNum+=35-tag;
                    array6.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=36&&tag<42) {
                if (box->getSelectedState()) {
                    totalNum+=41-tag;
                    array7.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=42&&tag<49) {
                if (box->getSelectedState()) {
                    totalNum+=48-tag;
                    array8.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=49&&tag<55) {
                if (box->getSelectedState()) {
                    totalNum+=54-tag;
                    array9.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=55&&tag<61) {
                if (box->getSelectedState()) {
                    totalNum+=60-tag;
                    array10.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
        }
        document.AddMember("疼痛程度", array, allocator);
        document.AddMember("个人生活料理", array2, allocator);
        document.AddMember("抬起物品", array3, allocator);
        document.AddMember("阅读", array4, allocator);
        document.AddMember("头痛", array5, allocator);
        document.AddMember("集中注意力", array6, allocator);
        document.AddMember("工作", array7, allocator);
        document.AddMember("开车/骑车", array8, allocator);
        document.AddMember("睡眠", array9, allocator);
        document.AddMember("娱乐休闲", array10, allocator);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void NDIScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    string jsonData=getJsonData(0);
    sprintf(jsonStr,"%s;%s",jsonData.c_str(),to_string((int)totalNum).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"pf_jNDI;pf_jNDI_total",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(NDIScene::onHttpRequestCompleted, this),url);
}

void NDIScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    if(!response -> isSucceed()){
        log("response failed");
        log("error buffer: %s", response -> getErrorBuffer());
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    rapidjson::Document jsondata;
    
    jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (jsondata.HasParseError()) {
        
        return;
    }
    if(jsondata.HasMember("status")){
        if (jsondata["status"].GetInt()==0) {
            Director::getInstance()->popScene();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}
string NDIScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 0:
            content="现在没有疼痛";break;
        case 1:
            content="现在有轻微疼痛";break;
        case 2:
            content="现在有中等程度疼痛";break;
        case 3:
            content="现在疼痛相当严重";break;//神经根型颈椎病
        case 4:
            content="现在疼痛非常严重";break;
        case 5:
            content="现在疼痛严重的无法形容";break;
        case 6:
            content="我能正常地照料自己而不引起额外的疼痛";break;
        case 7:
            content="我能正常地照料自己但会引起额外的疼痛";break;
        case 8:
            content="只能较慢地小心地活动且引起疼痛";break;
        case 9:
            content="需人帮助，但大部分可以自己完成";break;
        case 10:
            content="每天多数的日常生活需要帮助";break;
        case 11:
            content="我不能穿衣，洗簌有困难，不能离床";break;
        case 12:
            content="我能提起重物而不引起额外的疼痛";break;
        case 13:
            content="我能提起重物，但会引起额外的疼痛";break;//神经根型颈椎病
        case 14:
            content="因为疼痛不能把重物从地上提起但从桌子上可能提起";break;
        case 15:
            content="不能提起重物但可提起较轻或中等重物";break;
        case 16:
            content="我仅仅能提起非常轻的重物";break;
        case 17:
            content="我不能提起任何东西";break;
        case 18:
            content="我可如常阅读，而不引起颈痛";break;
        case 19:
            content="我可如常阅读，但会引起轻微的颈痛";break;
        case 20:
            content="我可如常阅读，但会引起中度颈痛";break;
        case 21:
            content="我不能如常阅读，由于有中度颈痛";break;
        case 22:
            content="我几乎完全不能阅读，由于有严重的颈痛";break;
        case 23:
            content="我根本不能阅读";break;
        case 24:
            content="我根本没有头痛";break;
        case 25:
            content="我有轻度头痛（不常发作）";break;
        case 26:
            content="我有中度头痛（不常头痛）";break;
        case 27:
            content="我有中度头痛（经常发作）";break;
        case 28:
            content="我有严重的头痛（经常发作）";break;
        case 29:
            content="我的头痛几乎没有停止过";break;
        case 30:
            content="如有需要时我能充分集中注意力（没有困难）";break;
        case 31:
            content="需要时我能集中注意力";break;
        case 32:
            content="当我需要集中注意力有不小的困难";break;
        case 33:
            content="当我需要集中注意力时，相当难做到";break;//神经根型颈椎病
        case 34:
            content="当我需要集中注意力时，很难做到";break;
        case 35:
            content="我根本不能集中注意力";break;
        case 36:
            content="我完全能胜任工作，想做多少就做多少";break;
        case 37:
            content="只能干一些基本分量的工作，但不能过量";break;
        case 38:
            content="只能完成一些基本分量的工作，但不能过量";break;
        case 39:
            content="不能做基本分量的工作";break;
        case 40:
            content="几乎不能工作";break;
        case 41:
            content="完全不能工作";break;
        case 42:
            content="能开车或骑车，没有颈痛";break;
        case 43:
            content="能随意开车或骑车，但引起轻微疼痛";break;//神经根型颈椎病
        case 44:
            content="能随意开车或骑车，但引起中度疼痛";break;
        case 45:
            content="中度颈痛不能随意开车或骑车";break;
        case 46:
            content="因颈痛严重，几乎不能开车或骑车";break;
        case 47:
            content="因颈痛严重，根本不能开车或骑车";break;
        case 48:
            content="我不会开车或骑车";break;
        case 49:
            content="我睡眠没有问题";break;
        case 50:
            content="我有点睡不好（失眠少于1小时）";break;
        case 51:
            content="我睡得不好（失眠1-2小时）";break;
        case 52:
            content="我睡得不好（失眠2-3小时）";break;
        case 53:
            content="我睡得相当不好（失眠3-5小时）";break;//神经根型颈椎病
        case 54:
            content="我完全不能入睡（失眠5-7小时）";break;
        case 55:
            content="我能参加各种娱乐活动根本无颈痛";break;
        case 56:
            content="我能参加各种娱乐活动但有轻度颈痛";break;
        case 57:
            content="由于颈痛我只能参加大部分日常娱乐活动";break;
        case 58:
            content="由于颈痛我只能参加少数娱乐活动";break;
        case 59:
            content="由于颈痛我几乎不能参加任何娱乐活动";break;
        case 60:
            content="由于颈痛我完全不能参加任何娱乐活动";break;
        
        default:
            break;
    }
    return content;
}






void  NDIScene::createData(){
    ValueVector vector1;
    vector1.push_back(Value("5分：现在没有疼痛 "));
    vector1.push_back(Value("4分：现在有轻微疼痛"));
    vector1.push_back(Value("3分：现在有中等程度疼痛"));
    vector1.push_back(Value("2分：现在疼痛相当严重"));
    vector1.push_back(Value("1分：现在疼痛非常严重"));
    vector1.push_back(Value("0分：现在疼痛严重得无法形容"));
    string key1 = "疼痛程度";
    ValueVector vector2;
    vector2.push_back(Value("5分：我能正常地照料自己而不引起额外的疼痛"));
    vector2.push_back(Value("4分：我能正常地照料自己但会引起额外的疼痛"));
    vector2.push_back(Value("3分：只能较慢地小心地活动且引起疼痛"));
    vector2.push_back(Value("2分：需人帮助，但大部分可以自己完成  "));
    vector2.push_back(Value("1分：每天多数的日常生活需要帮助"));
    vector2.push_back(Value("0分：我不能穿衣、洗漱有困难，不能离床"));
    string key2 = "个人生活料理(洗澡穿衣等)";
    ValueVector vector3;
    vector3.push_back(Value("5分：我能提起重物而不引起额外的疼痛"));
    vector3.push_back(Value("4分：我能提起重物，但会引起额外的疼痛"));
    vector3.push_back(Value("3分：因为疼痛不能把重物从地上提起但从桌子上可能提起"));
    vector3.push_back(Value("2分：不能提起重物但可提起较轻或中等重物  "));
    vector3.push_back(Value("1分：我仅仅能提起非常轻的重物"));
    vector3.push_back(Value("0分：我不能提起任何东西"));
    string key3 = "抬起(拿起)物品";
    ValueVector vector4;
    vector4.push_back(Value("5分：我可如常阅读，而不引起颈痛"));
    vector4.push_back(Value("4分：我可如常阅读，但会引起轻微的颈痛"));
    vector4.push_back(Value("3分：我可如常阅读，但会引起中度颈痛"));
    vector4.push_back(Value("2分：我不能如常阅读，由于有中度颈痛"));
    vector4.push_back(Value("1分：我几乎完全不能阅读，由于有严重的颈痛"));
    vector4.push_back(Value("0分：我根本不能阅读 "));
    string key4 = "阅读";
    ValueVector vector5;
    vector5.push_back(Value("5分：我根本没有头痛"));
    vector5.push_back(Value("4分：我有轻度头痛（不常发作）"));
    vector5.push_back(Value("3分：我有中度头痛（不常头痛）"));
    vector5.push_back(Value("2分：我有中度头痛（经常发作）"));
    vector5.push_back(Value("1分：我有严重的头痛（经常发作）"));
    vector5.push_back(Value("0分：我的头痛几乎没有停止过 "));
    string key5 = "头痛";
    ValueVector vector6;
    vector6.push_back(Value("5分：如有需要时我能充分集中注意力（没有困难）"));
    vector6.push_back(Value("4分：需要时我能集中注意力"));
    vector6.push_back(Value("3分：当我需要集中注意力有不少困难  "));
    vector6.push_back(Value("2分：当我需要集中注意力时，相当难做到 "));
    vector6.push_back(Value("1分：当我需要集中注意力时，很难做到"));
    vector6.push_back(Value("0分：我根本不能集中注意力"));
    string key6 = "集中注意力";
    ValueVector vector7;
    vector7.push_back(Value("5分：完全能胜任工作，想做多少就做多少 "));
    vector7.push_back(Value("4分：只能干一些基本分量的工作，但不能过量"));
    vector7.push_back(Value("3分：只能完成大部分基本工作工作，但不能过量"));
    vector7.push_back(Value("2分：不能做基本分量的工作"));
    vector7.push_back(Value("1分：几乎不能工作"));
    vector7.push_back(Value("0分：完全不能工作"));
    string key7 = "工作";
    ValueVector vector8;
    vector8.push_back(Value("5分：能开车或骑车，没有颈痛"));
    vector8.push_back(Value("4分：能随意开车或骑车，但引起轻微疼痛"));
    vector8.push_back(Value("3分：能随意开车或骑车，但引起中度疼痛"));
    vector8.push_back(Value("2分：中度颈痛不能随意开车或骑车"));
    vector8.push_back(Value("1分：因颈痛严重，几乎不能开车或骑车"));
    vector8.push_back(Value("0分：因颈痛严重，根本不能开车或骑车"));
    vector8.push_back(Value("我不会开车或骑车"));
    string key8 = "开车或骑车";
    ValueVector vector9;
    vector9.push_back(Value("5分：我睡眠没有问题"));
    vector9.push_back(Value("4分：我有点睡不好（失眠少于1小时）"));
    vector9.push_back(Value("3分：我睡得不好（失眠1-2小时）"));
    vector9.push_back(Value("2分：我睡得不好（失眠2-3小时）"));
    vector9.push_back(Value("1分：我睡得相当不好（失眠3-5小时）"));
    vector9.push_back(Value("0分：我完全不能入睡（失眠5-7小时）"));
    string key9 = "睡眠";
    ValueVector vector10;
    vector10.push_back(Value("5分：我能参加各种娱乐活动根本无颈痛"));
    vector10.push_back(Value("4分：我能参加各种娱乐活动但有轻度颈痛"));
    vector10.push_back(Value("3分：由于颈痛我只能参加大部分日常娱乐活动"));
    vector10.push_back(Value("2分：由于颈痛我只能参加少数娱乐活动"));
    vector10.push_back(Value("1分：由于颈痛我几乎不能参加任何娱乐活动"));
    vector10.push_back(Value("0分：由于颈痛我完全不能参加任何娱乐活动"));
    string key10 = "娱乐休闲";

#pragma-ValueMap加入数据
    map1[key1] = Value(vector1).asValueVector();
    map1[key2]=Value(vector2).asValueVector();
    map1[key3]=Value(vector3).asValueVector();
    map1[key4]=Value(vector4).asValueVector();
    map1[key5]=Value(vector5).asValueVector();
    map1[key6]=Value(vector6).asValueVector();
    map1[key7]=Value(vector7).asValueVector();
    map1[key8]=Value(vector8).asValueVector();
    map1[key9]=Value(vector9).asValueVector();
    map1[key10]=Value(vector10).asValueVector();
}


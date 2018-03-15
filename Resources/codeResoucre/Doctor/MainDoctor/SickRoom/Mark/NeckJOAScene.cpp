//
//  NeckJOAScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#include "NeckJOAScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *NeckJOAScene::createScene(){
    return NeckJOAScene::create();
}
bool NeckJOAScene::init(){
    if (!Scene::init()) {
        return false;
    }
#pragma-ValueVector加入数据
    ValueVector vector1;
    vector1.push_back(Value("4分:正常"));
    vector1.push_back(Value("3分:能持筷及一般家务劳动，但手笨拙"));
    vector1.push_back(Value("2分:虽手不灵活，但能持筷"));
    vector1.push_back(Value("1分:能持勺，但不能持筷"));
    vector1.push_back(Value("0分:自己不能持筷或勺进餐"));
    string key1 = "上肢运动功能";
    ValueVector vector2;
    vector2.push_back(Value("4分:正常"));
    vector2.push_back(Value("3分:平地或上楼行走不用支持物，但下肢不灵活"));
    vector2.push_back(Value("2分:在平地行走可不用支持物，但上楼时需用"));
    vector2.push_back(Value("1分:即使在平地行走也需用支持物"));
    vector2.push_back(Value("0分:不能行走"));
    string key2 = "下肢运动功能";
    ValueVector vector3;
    vector3.push_back(Value("2分:正常"));
    vector3.push_back(Value("1分:有轻度感觉障碍或麻木"));
    vector3.push_back(Value("0分:有明显感觉障碍"));
    string key3 = "上肢（感觉）";
    ValueVector vector4;
    vector4.push_back(Value("2分:正常"));
    vector4.push_back(Value("1分:有轻度感觉障碍或麻木"));
    vector4.push_back(Value("0分:有明显感觉障碍"));
    string key4 = "下肢（感觉）";
    ValueVector vector5;
    vector5.push_back(Value("2分:正常"));
    vector5.push_back(Value("1分:有轻度感觉障碍或麻木"));
    vector5.push_back(Value("0分:有明显感觉障碍"));
    string key5 = "躯干（感觉）";
    ValueVector vector6;
    vector6.push_back(Value("3分:正常"));
    vector6.push_back(Value("2分:轻度排尿困难，尿频，尿踌躇"));
    vector6.push_back(Value("1分:高度排尿困难，尿费力，尿失禁或淋漓"));
    vector6.push_back(Value("0分:尿潴留"));
    string key6 = "膀胱功能";
    
#pragma-ValueMap加入数据
    map1[key1] = Value(vector1).asValueVector();
    map1[key2]=Value(vector2).asValueVector();
    map1[key3]=Value(vector3).asValueVector();
    map1[key4]=Value(vector4).asValueVector();
    map1[key5]=Value(vector5).asValueVector();
    map1[key6]=Value(vector6).asValueVector();
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_neck_JOA.png");
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
    
    scrollV=createTableView(Vec2(0, visibleSize.height-170), Size(visibleSize.width, visibleSize.height-190));
    this->addChild(scrollV);
    return true;
}
ScrollView* NeckJOAScene::createTableView(Vec2 origin,Size visibleSize){
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
    
    float pointY1 =createPopUpView(Vec2(40, visibleSize.height-10), moveView, "上肢运动功能",0,1);
     float pointY3 =createPopUpView(Vec2(40, pointY1+60*5), moveView, "下肢运动功能",5,1);
     float pointY4 =createPopUpView(Vec2(40, pointY3+60*5), moveView, "上肢（感觉）",10,1);
     float pointY5 =createPopUpView(Vec2(40, pointY4+60*3), moveView, "下肢（感觉）",13,1);
     float pointY6 =createPopUpView(Vec2(40, pointY5+60*3), moveView, "躯干（感觉）",16,1);
    float pointY2 =createPopUpView(Vec2(40, pointY6+60*3), moveView, "膀胱功能",19,1);
    
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


float NeckJOAScene::createPopUpView(Vec2 point,Sprite* bkView,string name,int tag,int type){
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
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    
    
    //设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_appearance_down.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_appearance_up.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(NeckJOAScene::menuLoginCallback,this),
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

float NeckJOAScene::creatBlueLabelView(Vec2 point,Sprite* bkView,string name,int tag,int type){
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
        box->addEventListener(CC_CALLBACK_2(NeckJOAScene::checkBoxCallback,this));
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
        box->addEventListener(CC_CALLBACK_2(NeckJOAScene::checkBoxCallback,this));
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




void NeckJOAScene::menuLoginCallback(Ref* pSender)
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
void NeckJOAScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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
            if (tag>=0&&tag<5) {
                for (int i=0; i<5; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=5&&tag<10) {
                for (int i=5; i<10; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=10&&tag<13) {
                for (int i=10; i<13; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=13&&tag<16) {
                for (int i=13; i<16; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=16&&tag<19) {
                for (int i=16; i<19; i++) {
                    CheckBox *box=boxDic.at(i);
                    if (box->getTag()!=tag) {
                        box->setSelected(false);
                    }
                }
            }
            if (tag>=19&&tag<23) {
                for (int i=19; i<23; i++) {
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

std::string NeckJOAScene::getJsonData(int type)
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
        for (int i=0; i<boxDic.size(); i++) {
            CheckBox* box=(CheckBox*)boxDic.at(i);
            int tag=box->getTag();
            if (tag>=0&&tag<5) {
                    if (box->getSelectedState()) {
                        totalNum+=4-tag;
                         array.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
               }
            }
            if (tag>=5&&tag<10) {
                    if (box->getSelectedState()) {
                        totalNum+=9-tag;
                        array2.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=10&&tag<13) {
                    if (box->getSelectedState()) {
                        totalNum+=12-tag;
                        array3.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    }
            }
            if (tag>=13&&tag<16) {
                    if (box->getSelectedState()) {
                        totalNum+=15-tag;
                        array4.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                    }
            }
            if (tag>=16&&tag<19) {
                    if (box->getSelectedState()) {
                        totalNum+=18-tag;
                        array5.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
            if (tag>=19&&tag<23) {
                    if (box->getSelectedState()) {
                        totalNum+=22-tag;
                        array6.PushBack(rapidjson::Value(changeNumToString(tag).c_str(), allocator),allocator);
                }
            }
        }
        document.AddMember("上肢运动功能", array, allocator);
        document.AddMember("下肢运动功能", array2, allocator);
        document.AddMember("上肢感觉", array3, allocator);
        document.AddMember("下肢感觉", array4, allocator);
        document.AddMember("躯干感觉", array5, allocator);
        document.AddMember("膀胱功能", array6, allocator);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void NeckJOAScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    string jsonData=getJsonData(0);
    sprintf(jsonStr,"%s;%s",jsonData.c_str(),to_string(totalNum).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"pf_jJOA;pf_jJOA_total",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(NeckJOAScene::onHttpRequestCompleted, this),url);
}

void NeckJOAScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
string NeckJOAScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 0: case 5:case 10:case 13:case 16:case 19:
            content="正常";break;
        case 1:
            content="能持筷及一般家务劳动，但手笨拙";break;
        case 2:
            content="虽手不灵活，但能持筷";break;
        case 3:
            content="能持勺，但不能持筷";break;//神经根型颈椎病
        case 4:
            content="自己不能持筷或勺进餐";break;
        case 6:
            content="平地或上楼行走不用支持物，但下肢不灵活";break;
        case 7:
            content="在平地行走可不用支持物，但上楼时需用";break;
        case 8:
            content="即使在平地行走也需用支持物";break;
        case 9:
            content="不能行走";break;
        case 11: case 14:case 17:
            content="有轻度感觉障碍或麻木";break;
        case 12:case 15:case 18:
            content="有明显感觉障碍";break;
        case 20:
            content="轻度排尿困难，尿频，尿踌躇";break;
        case 21:
            content="高度排尿困难，尿费力，尿失禁或淋漓";break;
        case 22:
            content="尿潴留";break;
        default:
            break;
    }
    return content;
}


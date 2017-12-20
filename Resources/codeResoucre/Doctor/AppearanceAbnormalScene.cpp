//
//  AppearanceAbnormalScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/19.
//

#include "AppearanceAbnormalScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "ChatUserDetailScene.hpp"
#include "SearchScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *AppearanceAbnormalScene::createScene(){
    return AppearanceAbnormalScene::create();
}
//用于存储数据
ValueMap map1;

Map<int, Sprite*> wholeDic;

ScrollView *scrollV;
Sprite *moveView;
bool AppearanceAbnormalScene::init(){
    if (!Scene::init()) {
        return false;
    }
#pragma-ValueVector加入数据
    ValueVector vector1;
    vector1.push_back(Value("面部不对称"));
     vector1.push_back(Value("双肩不等高"));
     vector1.push_back(Value("肩胛骨不等高（前屈位）"));
     vector1.push_back(Value("骼棘不等高"));
     vector1.push_back(Value("下肢不等长"));
    log("%ld",vector1.size());
    string key1 = "双侧不对称";
    ValueVector vector2;
    vector2.push_back(Value("鱼际肌"));
    vector2.push_back(Value("掌间肌"));
    vector2.push_back(Value("肱二头肌"));
    vector2.push_back(Value("肱三头肌"));
    vector2.push_back(Value("三角肌"));
    vector2.push_back(Value("股四头肌"));
    vector2.push_back(Value("腓肠肌"));
    string key2 = "肌肉萎缩";
#pragma-ValueMap加入数据
    map1["双侧不对称"] = Value(vector1).asValueVector();
    map1["肌肉萎缩"]=Value(vector2).asValueVector();
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_chat.png");
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
    
   scrollV=createTableView(Vec2(0, 0), Size(visibleSize.width, visibleSize.height-150));
    this->addChild(scrollV);
    
    return true;
}

ScrollView* AppearanceAbnormalScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    moveView=Sprite::create("alpha.png");
    moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    moveView->setAnchorPoint(Vec2(0, 1));
    moveView->setContentSize(visibleSize);
    scrollView->addChild(moveView);
    
    float pointY1 =creatLabelView(Vec2(59, scrollView->getInnerContainerSize().height-50), moveView, "短颈",1);
    float pointY2=creatLabelView(Vec2(59, pointY1-50), moveView, "牛奶咖啡斑",2);
    float pointY3=creatLabelView(Vec2(59, pointY2-50), moveView, "剃刀背",3);
    float pointY4=creatLabelView(Vec2(59, pointY3-50), moveView, "足下垂",4);
    
    float pointY5 =createPopUpView(Vec2(40, pointY4-20), moveView, "双侧不对称",5);
     float pointY6 =createPopUpView(Vec2(40, pointY5+60*5), moveView, "肌肉萎缩",10);
    
     createPopUpView(Vec2(40, pointY6+60*7), moveView, "双侧不对称",17);
    
    scrollView->setInnerContainerSize(Size(visibleSize.width, 60*8));
    
    return scrollView;
}

float AppearanceAbnormalScene::createPopUpView(Vec2 point,Sprite* bkView,string name,int tag){
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
        creatBlueLabelView(Vec2(0,60*i), whiteV,whiteStr,tag+i);
    }
    
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(point.x, point.y-60));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-80, 60));
    wholeV->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    auto box = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(blueV->getContentSize().width-60,10));
    box->setScale(0.8);
    box->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->setTag(100+tag);
    box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    blueV->addChild(box);
    
    return point.y-(index+1)*60-20;
    
}





//实现CheckBox回调函数
void AppearanceAbnormalScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
            if (tag>=100) {
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
                    log("%d",nextTag);
                    if (nextTag>tag-100) {
                        auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                        nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y-whiteV->getContentSize().height+60));
                        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height+whiteV->getContentSize().height-60));//设置内容大小
                        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
                        
                    }
                }
        }
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
        {
            if (tag>=100) {
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
                        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
                        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
                    }
                }
                
            }
        }
            break;
        default:
            break;
    }
}

float AppearanceAbnormalScene::creatBlueLabelView(Vec2 point,Sprite* bkView,string name,int tag){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(point.x+20, point.y));
    userName->setTextColor(Color4B(0, 0, 0, 255/2));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto box = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(bkView->getContentSize().width-60,point.y+10));
    box->setScale(0.87);
    box->setTag(tag);
    box->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(box);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, point.y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.89);
    bkView->addChild(lineV);
    return point.y-20;
}


float AppearanceAbnormalScene::creatLabelView(Vec2 point,Sprite* bkView,string name,int tag){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto box = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(visibleSize.width-100,point.y+2));
    box->setScale(0.87);
    box->setAnchorPoint(Vec2(0, 0));
    box->setTag(tag);
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(box);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-10));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    return point.y-20;
}




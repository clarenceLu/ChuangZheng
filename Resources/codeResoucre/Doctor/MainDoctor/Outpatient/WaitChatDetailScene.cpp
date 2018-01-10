//
//  WaitChatDetailScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/3.
//

#include "WaitChatDetailScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SelectStep3Scene.hpp"
#include "SelectStep4Scene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *WaitChatDetailScene::createScene(){
    return WaitChatDetailScene::create();
}
bool WaitChatDetailScene::init(){
    if (!Scene::init()) {
        return false;
    }
    return true;
};

void WaitChatDetailScene::onEnter()
{
    
    log("%d",type);
    Scene::onEnter();
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
    
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0, 30));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 950));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 255, 255));//设置背景颜色
    createScrollDetailView(scrollView);
    bkView->addChild(scrollView);
}

void WaitChatDetailScene::createScrollDetailView(ScrollView* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("alpha.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, 950));
    superV->addChild(bkView);
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(244, 815));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
    headBtn->ignoreContentAdaptWithSize(true);
    headBtn->setScale9Enabled(true);
    headBtn->setContentSize(Size(151, 151));
    bkView->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            log("点击上传头像");
            Layer *layer= createAlbumLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
    });
    
    createLabel(Vec2(0, 758), "真实姓名：", "张牧之", bkView);
    createLabel(Vec2(0, 678), "病历号：", "20171112082214", bkView);
    createLabel(Vec2(0, 598), "性别：", "女", bkView);
    createLabel(Vec2(0, 518), "年龄：", "32", bkView);
    float height= createLabel(Vec2(0, 438), "自述症状：", "头后仰上身麻无敌无敌无敌无敌无敌", bkView);
    createLabel(Vec2(0, 400-height), "介绍人：", "董大伟", bkView);
    createLabel(Vec2(0, 320-height), "推荐人：", "小布什", bkView);
    
    
    auto imageLB = Label::createWithSystemFont("影像：","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    imageLB->setPosition(Point(56,240-height));
    imageLB->setTextColor(Color4B(91,144,230, 255));
    imageLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(imageLB);
    float currentHeight=0;
    for (int i=0; i<3; i++) {
        if (i==3-1) {
            auto imageBtn1=ImageView::create("btn_chat_userImage.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 160-height+10));
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 160-height-(int)((width-154)/(visibleSize.width-154))*150+10));
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
            currentHeight=975-(160-height-(int)((width-154)/(visibleSize.width-154))*150);
        }else{
            auto imageBtn1=ImageView::create("bk_headIV.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 160-height));
                //                 log("width:%d,height:%f i的值%d,屏幕宽度%f",154+150*(i%3),320-height-(int)(width/(int)visibleSize.width)*150,i,visibleSize.width);
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 160-height-(int)((width-154)/(visibleSize.width-154))*150));
                //                log("width:%d,height:%f i的值%d,总长度:%d",154+150*(i%3),320-height-(int)((width-154)/(visibleSize.width-154))*150,i,width);
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->ignoreContentAdaptWithSize(true);
            imageBtn1->setScale9Enabled(true);
            imageBtn1->setContentSize(Size(125, 125));
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    log("点击查看照片");
                }
            });
        }
    }
    if (type==1) {
    superV->setInnerContainerSize(Size(visibleSize.width, currentHeight+30));
    bkView->setPosition(Vec2(0, currentHeight-960));
    }else if(type==2){
        superV->setInnerContainerSize(Size(visibleSize.width, currentHeight+210));
        bkView->setPosition(Vec2(0, currentHeight-960+185));
        auto acceptBtn=Button::create();
        acceptBtn->loadTextures("btn_wait_accept.png", "btn_wait_accept.png");
        acceptBtn->setPosition(Vec2(188, 105-bkView->getPosition().y));
        acceptBtn->setAnchorPoint(Vec2(0, 0));
        acceptBtn->setScale(0.87);
        acceptBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto layer=createPromptLayer("确认接诊该病人？");
                layer->setTag(2001);
                this->addChild(layer);
            }
            default:
                break;
        }
        });
        bkView->addChild(acceptBtn);
        
        auto recommendBtn=Button::create();
        recommendBtn->loadTextures("btn_waitDetail_recommend.png", "btn_waitDetail_recommend.png");
        recommendBtn->setPosition(Vec2(188, 10-bkView->getPosition().y));
        recommendBtn->setScale(0.87);
        recommendBtn->setAnchorPoint(Vec2(0, 0));
        recommendBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                log("推荐给别人");
                auto select4SC=SelectStep4Scene::createScene();
                Director::getInstance()->pushScene(select4SC);
            }
            default:
                break;
        }
        });
        bkView->addChild(recommendBtn);
        
        auto refuseBtn=Button::create();
        refuseBtn->loadTextures("btn_wait_accept_refuse.png", "btn_wait_accept_refuse.png");
        refuseBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
        refuseBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto layer=createRefuseLayer();
                layer->setTag(2002);
                this->addChild(layer);
            }
                
            default:
                break;
        }
        });
        this->addChild(refuseBtn);
        
    }else if(type==3){
        superV->setInnerContainerSize(Size(visibleSize.width, currentHeight+210));
        bkView->setPosition(Vec2(0, currentHeight-960+185));
        auto acceptBtn=Button::create();
        acceptBtn->loadTextures("btn_accept_again.png", "btn_accept_again.png");
        acceptBtn->setPosition(Vec2(188, 105-bkView->getPosition().y));
        acceptBtn->setAnchorPoint(Vec2(0, 0));
        acceptBtn->setScale(0.87);
        acceptBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto layer=createPromptLayer("确认重新接诊该病人？");
                layer->setTag(2001);
                this->addChild(layer);
            }
            default:
                break;
        }
        });
        bkView->addChild(acceptBtn);
        
        auto recommendBtn=Button::create();
        recommendBtn->loadTextures("btn_waitDetail_recommend.png", "btn_waitDetail_recommend.png");
        recommendBtn->setPosition(Vec2(188, 10-bkView->getPosition().y));
        recommendBtn->setScale(0.87);
        recommendBtn->setAnchorPoint(Vec2(0, 0));
        recommendBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto select4SC=SelectStep4Scene::createScene();
                Director::getInstance()->pushScene(select4SC);
                log("推荐给别人");
            }
            default:
                break;
        }
        });
        bkView->addChild(recommendBtn);
    }
    
}

Layer* WaitChatDetailScene::createRefuseLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255));
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
    auto contentV = Sprite::create("bk_refuse_layer.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(2002);
        default:
            break;
    }
    });
    contentV->addChild(backBtn);
    auto nameLB = Label::createWithSystemFont("请填写拒绝理由：","fonts/Marker Felt.ttf",40,Size(400,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(39,923));
    nameLB->setTextColor(Color4B(0,0,0, 220));
    nameLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(nameLB);
    
    auto textFieldBottom=Sprite::create("textfield_bottom.png");
    textFieldBottom->setPosition(Vec2(23, 623));
    textFieldBottom->setAnchorPoint(Vec2(0, 0));
    textFieldBottom->setScale(0.87);
    contentV->addChild(textFieldBottom);
    
    auto textFieldCenter=Sprite::create("textfield_center.png");
    textFieldCenter->setPosition(Vec2(23, 623+textFieldBottom->getContentSize().height*0.87));
    textFieldCenter->setScale(0.87);
    textFieldCenter->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(textFieldCenter);
    
    auto textFieldTop=Sprite::create("textfield_top.png");
    textFieldTop->setPosition(Vec2(23, textFieldCenter->getContentSize().height*0.87+textFieldCenter->getPosition().y));
    textFieldTop->setScale(0.87);
    textFieldTop->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(textFieldTop);
    
    
    auto textFieldContent= TextField::create("一百字以内","Arial",35);
    textFieldContent->setMaxLength(240);
    //用于多行输入
    textFieldContent->ignoreContentAdaptWithSize(false);
    textFieldContent->setTouchSize(Size(visibleSize.width-80,270));
    textFieldContent->setPosition(Vec2(45,625));
    textFieldContent->setAnchorPoint(Vec2(0,0));
    textFieldContent->setContentSize(Size(visibleSize.width-80,270));
    textFieldContent->setTextColor(Color4B::BLACK);
    textFieldContent->setPlaceHolderColor(Color4B::GRAY);
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->addEventListener(CC_CALLBACK_2(WaitChatDetailScene::eventCallBack, this));
    contentV->addChild(textFieldContent);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_step2_sure.png", "btn_step2_sure.png");
    sureBtn->setPosition(Vec2(185, 500));
    sureBtn->setScale(0.87);
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(2002);
            log("替换成拒绝列表,同时请求数据");
            auto chatSC=(WaitChatDetailScene*)WaitChatDetailScene::createScene();
            chatSC->type=3;
            Director::getInstance()->replaceScene(chatSC);
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    return layer;
}



Layer* WaitChatDetailScene::createAlbumLayer(){
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

Layer* WaitChatDetailScene::createUpdateImageLayer(){
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

float WaitChatDetailScene::createLabel(Vec2 point,string name1,string name2,Sprite* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto nameLB = Label::createWithSystemFont(name1,"fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(56,point.y));
    nameLB->setTextColor(Color4B(91,144,230, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB);
    
    auto nameLB2 = Label::createWithSystemFont(name2,"Arial",35,Size(visibleSize.width-265,0),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    float height=nameLB2->getContentSize().height;
    nameLB2->setPosition(Point(218,point.y+41-height));
    nameLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    nameLB2->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB2);
    
    return height;
}



cocos2d::Layer* WaitChatDetailScene::createPromptLayer(std::string content){
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
    auto contentV = Sprite::create("bk_wait_accept.png");
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
            this->removeChildByTag(2001);
            log("确认接诊");
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

void WaitChatDetailScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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


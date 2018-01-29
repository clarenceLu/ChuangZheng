//
//  ChatViewScene.cpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 19/01/2018.
//

#include "ChatViewScene.hpp"
#include "cocos2d.h"

using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d;


Scene *ChatViewScene::createScene(){
    return ChatViewScene::create();
}

bool ChatViewScene::init(){
    if (!Scene::init()) {
        return false;
    }
    return true;
};


void ChatViewScene::createHubView(){
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    
    auto webView = cocos2d::experimental::ui::WebView::create();
    webView->loadURL("http://www.luz.ink/index/index/index?uid=2&sid=123");
    webView->setContentSize(Size(visibleSize.width, visibleSize.height));
    webView->setAnchorPoint(Vec2(0,0));
    webView->setPosition(Vec2(0,0));
    this->addChild(webView);

}

void ChatViewScene::onEnter()
{

    Scene::onEnter();
  

}


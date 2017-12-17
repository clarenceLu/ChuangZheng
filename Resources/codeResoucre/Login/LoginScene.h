#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "UserCaseScene.hpp"
using namespace cocos2d;
using namespace cocos2d::network;



class LoginScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuLoginCallback(cocos2d::Ref* pSender);
    
    void createHudView();
    
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
    
    void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);

#pragma-用于加载数据
    void pushDataToNetWork(std::string username,std::string passwd);

private:
    rapidjson::Document loginData;
    
    
    void printLog();
    
    
};

#endif // __HELLOWORLD_SCENE_H__

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include <iostream>
<<<<<<< HEAD
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"





using namespace cocos2d;
=======
#include "UserCaseScene.hpp"
>>>>>>> 71f69d1b4a66c93c8b75d1b137d2deb86ddc7273
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
    
    void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
private:
    
    rapidjson::Document loginData;
    
    
    void printLog();
    
    
};

#endif // __HELLOWORLD_SCENE_H__

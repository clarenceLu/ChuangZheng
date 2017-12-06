#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include <iostream>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
<<<<<<< HEAD
using namespace cocos2d;
#include "UserCaseScene.hpp"
=======

#include "UserCaseScene.hpp"



using namespace cocos2d;

>>>>>>> 0bdfb25556ec566fd544334f0468261ab92ee8a3
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

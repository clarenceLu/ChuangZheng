//
//  WelcomeScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#ifndef WelcomeScene_hpp
#define WelcomeScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"


USING_NS_CC;
class WelcomeScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(WelcomeScene);
    std::string getEducationFromRole(std::string role);
    
    
    std::string getJsonData();
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    private:
    rapidjson::Document infoData;
    
    rapidjson::Document impressData;
};


#endif /* WelcomeScene_hpp */

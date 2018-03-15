//
//  RegisterMessageScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/11/29.
//

#ifndef RegisterMessageScene_hpp
#define RegisterMessageScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
class RegisterMessageScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(RegisterMessageScene);
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::Layer* createAlbumLayer();
    
#pragma-用于加载数据
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork(std::string username,std::string passwd,std::string name,std::string sex,std::string age,std::string phone,std::string phone1,std::string idCardNo,std::string address,std::string headUrl,std::string caseNo);
    
    std::string getTimeForSystem();
private:
    rapidjson::Document loginData;
    
    
};

#endif /* RegisterMessageScene_hpp */

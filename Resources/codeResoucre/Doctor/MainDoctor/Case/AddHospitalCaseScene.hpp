//
//  AddHospitalCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#ifndef AddHospitalCaseScene_hpp
#define AddHospitalCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
using namespace cocos2d::ui;
class AddHospitalCaseScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AddHospitalCaseScene);
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    //先查询
    void getUserDataToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    //查询没有再新建
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void getUserInfoToNetWork();
    std::string getTimeForSystem();
    //新建病例
    void createCaseToNetWork();
    void onHttpRequestCompleted3(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
private:
    TextField* textfieldName;
    TextField* textfieldAge;
    TextField* textfieldCase;
    TextField* textfieldBedNum;
    std::string sexLB;
    
    rapidjson::Document userData;
};
#endif /* AddHospitalCaseScene_hpp */

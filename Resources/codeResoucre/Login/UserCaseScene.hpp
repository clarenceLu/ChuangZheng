//
//  UserCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#ifndef UserCaseScene_hpp
#define UserCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "QR_Encode.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace cocos2d::network;
class UserCaseScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(UserCaseScene);
    
    void onEnter();
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    cocos2d::Layer* createCaseLayer();
    
    cocos2d::Layer* createInformLayer();
    cocos2d::Layer* createNotificationInformLayer();
    
    cocos2d::Layer* createDynamicLayer();
    
    cocos2d::Layer* createUserInfoLayer();
    
    cocos2d::Layer* createAlbumLayer();
    
    cocos2d::Layer* createCodeLayer();
    
    cocos2d::Layer* createChangeKeyLayer();
    
    cocos2d::Layer* createExitLayer();
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Button* createMessageBtn(int i, cocos2d::Size  innerSize);
    
  //登录时传入数据
    rapidjson::Document infoData;
    
    
#pragma-用于加载数据-动态
    void pushDataToNetWork();
    void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);
  
    
//userInfo
    void getUserDataToNetWork();
    void onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response);
    void pushUserDataToNetWork();
    void onHttpRequestCompleted3(HttpClient* sender, HttpResponse* response);
    
//case
    void getCaseDataToNetWork();
    void onHttpRequestCompleted4(HttpClient* sender, HttpResponse* response);
    
    
    cocos2d::DrawNode * createSQCodeImage(std::string content,cocos2d::Vec2 origin);
    
  //裁剪字符串
    static std::string subUTF8(const std::string &str, int from, int to);
private:
    static std::vector<std::string> parseUTF8(const std::string &str);
    
    CQR_Encode m_QREncode;
    
    
    rapidjson::Document dynamicData;
    
    
    cocos2d::Map<int, cocos2d::Label*> labelDic;
    cocos2d::Map<int, cocos2d::ui::TextField*> textFieldDic;
    cocos2d::ui::TextField *originalPassword;
    cocos2d::ui::TextField *newPassword;
    cocos2d::ui::TextField* surePassword;
    
    
    cocos2d::Layer* caseLayer;
    cocos2d::Layer* informLayer;
    cocos2d::Layer* dynamicLayer;
    cocos2d::Layer* userInfoLayer;
    
    
    //userInfo
    rapidjson::Document userData;
    rapidjson::Document caseData;
    
};
#endif /* UserCaseScene_hpp */

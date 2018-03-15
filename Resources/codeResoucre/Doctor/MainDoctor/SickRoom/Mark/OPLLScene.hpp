//
//  OPLLScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/8.
//

#ifndef OPLLScene_hpp
#define OPLLScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class OPLLScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OPLLScene);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
     void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
     void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    void createScrollDetailView(cocos2d::ui::ScrollView* superV);
    
    void createSelectView(int tag,cocos2d::Vec2 point,std::string title,cocos2d::Sprite*bkView);
    
    
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    std::string changeNumToString(int num);
    
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void getDataToNetWork();
    void updateForInfoData();
    
private:
    rapidjson::Document infoData;
    cocos2d::ui::ScrollView *scrollV;
    cocos2d::ui::TextField* weightField;
    cocos2d::ui::TextField* timeField;
    cocos2d::ui::TextField* occupyField;
    cocos2d::ui::TextField* cobbsField;
    cocos2d::ui::TextField* otherField;
    
    Map<int, cocos2d::ui::CheckBox*> boxDic;
    Map<int, cocos2d::ui::TextField*> textFieldDic;
};

#endif /* OPLLScene_hpp */

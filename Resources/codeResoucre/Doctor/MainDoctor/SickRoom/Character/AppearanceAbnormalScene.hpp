//
//  AppearanceAbnormalScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/19.
//

#ifndef AppearanceAbnormalScene_hpp
#define AppearanceAbnormalScene_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"



class AppearanceAbnormalScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(AppearanceAbnormalScene);
    
    
    void menuLoginCallback(cocos2d::Ref* pSender);
    
     void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    float creatLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag);
    float creatBlueLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    float createPopUpView(cocos2d::Vec2 point,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    
    
    std::string changeNumToString(int num);
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
private:
    cocos2d::LayerMultiplex *multLayer;
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
    
};

#endif /* AppearanceAbnormalScene_hpp */

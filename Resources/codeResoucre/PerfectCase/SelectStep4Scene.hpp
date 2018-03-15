//
//  SelectStep4Scene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#ifndef SelectStep4Scene_hpp
#define SelectStep4Scene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "cocos2d.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
class SelectStep4Scene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectStep4Scene);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    
    cocos2d::Layer* createMessageLayer(int i, cocos2d::Size  innerSize);
    
#pragma-用于加载数据
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void selectDoctorToNetWork();
    
    void onHttpRequestCompleted3(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void commandDoctorToNetWork();
//当commandtype为2时代表推荐病人给其他医生，这个时候是单选的
    void onEnter();
    int commandType;
    int selectDorctorId;
    
private:
    rapidjson::Document loginData;
    
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
    
    rapidjson::vector<int>  selectNumVector;
    
    cocos2d::ui::TextField *  searchText;
    
};
#endif /* SelectStep4Scene_hpp */

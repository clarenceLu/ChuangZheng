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
private:
    rapidjson::Document loginData;
    
};
#endif /* SelectStep4Scene_hpp */

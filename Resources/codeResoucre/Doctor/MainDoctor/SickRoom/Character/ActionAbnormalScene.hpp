//
//  ActionAbnormalScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/21.
//

#ifndef ActionAbnormalScene_hpp
#define ActionAbnormalScene_hpp
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class ActionAbnormalScene:public cocos2d::Scene{
    public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ActionAbnormalScene);
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
     float creatLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag);
    
    std::string changeNumToString(int num);
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
private:
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
    
    
};


#endif /* ActionAbnormalScene_hpp */

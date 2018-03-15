//
//  ReflectAbnormalScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef ReflectAbnormalScene_hpp
#define ReflectAbnormalScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class ReflectAbnormalScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ReflectAbnormalScene);
    
    void createSelectView(int tag,cocos2d::Sprite*bkView,float originY,std::string title);
    void createSelectView2(int tag,cocos2d::Sprite*bkView,float originY,std::string title);
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    
    std::string changeNumToString(int num);
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
private:
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
};

#endif /* ReflectAbnormalScene_hpp */

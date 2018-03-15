//
//  ReflectScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef ReflectScene_hpp
#define ReflectScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class ReflectScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ReflectScene);
    void createSelectView(int tag,cocos2d::Sprite*bkView,float originY,std::string title);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    std::string changeNumToString(int num);
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
private:
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
};

#endif /* ReflectScene_hpp */

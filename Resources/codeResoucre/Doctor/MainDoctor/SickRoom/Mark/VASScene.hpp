//
//  VASScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#ifndef VASScene_hpp
#define VASScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class VASScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(VASScene);
     void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    //裁剪字符串
    static std::string subUTF8(const std::string &str, int from, int to);
    static std::vector<std::string> parseUTF8(const std::string &str);
private:
    int count;
    cocos2d::ui::ListView* lv;
    
    cocos2d::ui::TextField* partField;
    cocos2d::ui::TextField* painField;
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
     cocos2d::ui::Layout * createPainView(cocos2d::Vec2 point,int i);
    
    
    cocos2d::Map<int, cocos2d::ui::TextField*> titleDic;
    cocos2d::Map<int, cocos2d::ui::TextField*> numDic;
    
};

#endif /* VASScene_hpp */

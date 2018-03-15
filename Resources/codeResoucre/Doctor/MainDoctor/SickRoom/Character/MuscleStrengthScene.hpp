//
//  MuscleStrengthScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef MuscleStrengthScene_hpp
#define MuscleStrengthScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class MuscleStrengthScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MuscleStrengthScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    cocos2d::Layer* createSelectLayer();
    void createSelectItem(std::string title,float Y,cocos2d::Sprite* contentV);
    
    std::string changeTitleToIndex(std::string title);
    std::string changeIndexToTitle(std::string index);
    
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void getDataToNetWork();
    
private:
    Map<int, cocos2d::Label*> labelDic;
    Map<int, cocos2d::Label*> titleDic;
    int selectIndex;
    
    rapidjson::Document infoData;
    
};

#endif /* MuscleStrengthScene_hpp */

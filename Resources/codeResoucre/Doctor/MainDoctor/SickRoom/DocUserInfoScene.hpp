//
//  DocUserInfoScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef DocUserInfoScene_hpp
#define DocUserInfoScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class DocUserInfoScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(DocUserInfoScene);
    cocos2d::Layer* createAlbumLayer();
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    
    void createContentViewWithBkView();
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void updatePatientInfoToNetWork();
    
private:
     rapidjson::Document infoData;
    
    cocos2d::ui::TextField*textfieldName;
    cocos2d::ui::TextField*textfieldNum;
    cocos2d::ui::TextField*textfieldCase;
    cocos2d::ui::TextField*textfieldSponsor;
    cocos2d::ui::TextField*textfieldRecommend;
    cocos2d::ui::TextField*textfieldTel1;
    cocos2d::ui::TextField*textfieldTel2;
    cocos2d::ui::TextField*textfieldTel3;
    cocos2d::ui::TextField* textFieldSex;
    cocos2d::ui::TextField* textFieldAge;
    cocos2d::Sprite* bkView;
};

#endif /* DocUserInfoScene_hpp */

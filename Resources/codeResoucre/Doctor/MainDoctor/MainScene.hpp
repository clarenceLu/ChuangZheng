//
//  MainScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "QR_Encode.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class MainScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MainScene);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void menuBedNumCallback(cocos2d::Ref* pSender);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);

    cocos2d::Layer* createSickRoomLayer();
    void createSickRoomWithBackView(cocos2d::Sprite* bkView);
    cocos2d::Layer* createOutPatientLayer();
    cocos2d::Layer* createSickInfoLayer();
                          cocos2d::Layer* createSponsorLayer();
    cocos2d::Layer* createSQCodeLayer();
     cocos2d::Layer* createCalendarLayer();
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Button* createMessageBtn(int i, cocos2d::Size  innerSize);
    
    cocos2d::LayerMultiplex *multLayer;
    
    std::shared_ptr<cocos2d::Vector<cocos2d::ui::CheckBox*>>  boxVec;
    
    cocos2d::Menu*   createRectButton(cocos2d::Vec2 point,int i);
    cocos2d::ui::ScrollView* createScrollV(int index);
    
    cocos2d::DrawNode * createSQCodeImage(std::string content,cocos2d::Vec2 origin);
    
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    private:
    CQR_Encode m_QREncode;
    
    rapidjson::Document infoData;
//加入一个参数用来判断他是否是临时床位
    int isTempBed;
};
#endif /* MainScene_hpp */

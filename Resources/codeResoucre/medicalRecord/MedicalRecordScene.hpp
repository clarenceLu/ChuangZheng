//
//  MedicalRecordScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/14.
//

#ifndef MedicalRecordScene_hpp
#define MedicalRecordScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace cocos2d;
using namespace cocos2d::network;
class MedicalRecordScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    
    CREATE_FUNC(MedicalRecordScene);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    cocos2d::ui::Layout* createLabel(int i,std::string title,std::string content);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    std::string searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data);
    
    rapidjson::Document infoData;
private:
    //impress
    rapidjson::Document impressData;
    rapidjson::Document formationData;
    rapidjson::Document infectData;
    rapidjson::Document injuryData;
    //symptom
    rapidjson::Document symptomData;
    
    cocos2d::ui::ListView* lv;
    
};

#endif /* MedicalRecordScene_hpp */

//
//  CaseDoctorScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#ifndef CaseListScene_hpp
#define CaseListScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class CaseListScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(CaseListScene);
    cocos2d::ui::Layout *creatLayout(cocos2d::ui::ListView*superV,int i);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type);
    
    cocos2d::Layer* addCaseLayer();
    rapidjson::Document infoData;
private:
    cocos2d::ui::ListView* lv;
};
#endif /*CaseListScene_hpp */

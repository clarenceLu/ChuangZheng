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
USING_NS_CC;
class CaseListScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CaseListScene);
    cocos2d::ui::Layout *creatLayout(cocos2d::ui::ListView*superV,int i);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type);
    
    cocos2d::Layer* addCaseLayer();
    
private:
};
#endif /*CaseListScene_hpp */

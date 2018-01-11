//
//  VisitCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#ifndef VisitCaseScene_hpp
#define VisitCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class VisitCaseScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(VisitCaseScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    void createTextFieldView(cocos2d::ui::Layout* contentV);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    
    Size calculateFontSize(const char *str );
    
private:
    cocos2d::ui::ListView* lv;
};

#endif /* VisitCaseScene_hpp */

//
//  CaseHistoryScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#ifndef CaseHistoryScene_hpp
#define CaseHistoryScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class CaseHistoryScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CaseHistoryScene);
    void  createLabelWithoutField(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name,int tag);
    void buttonCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    cocos2d::Layer* addCaseLayer();
    
private:
};

#endif /* CaseHistoryScene_hpp */

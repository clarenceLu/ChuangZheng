//
//  ASIAScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/5.
//

#ifndef ASIAScene_hpp
#define ASIAScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class ASIAScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ASIAScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    
private:
};

#endif /* ASIAScene_hpp */

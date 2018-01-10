//
//  SymptomScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef SymptomScene_hpp
#define SymptomScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class SymptomScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SymptomScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    cocos2d::ui::Layout *createItemLayout(int i,std::string title);
    
    
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
private:
};

#endif /* SymptomScene_hpp */

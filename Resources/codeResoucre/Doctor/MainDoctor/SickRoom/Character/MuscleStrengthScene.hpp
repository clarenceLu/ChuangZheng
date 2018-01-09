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
    
private:
    Map<int, cocos2d::Label*> labelDic;
    int selectIndex;
};

#endif /* MuscleStrengthScene_hpp */

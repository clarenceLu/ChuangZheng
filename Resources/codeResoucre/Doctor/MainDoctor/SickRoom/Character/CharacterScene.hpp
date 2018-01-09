//
//  CharacterScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef CharacterScene_hpp
#define CharacterScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class CharacterScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CharacterScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
private:
};

#endif /* CharacterScene_hpp */

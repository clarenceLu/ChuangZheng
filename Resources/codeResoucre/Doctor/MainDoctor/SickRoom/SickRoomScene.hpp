//
//  SickRoomScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/4.
//

#ifndef SickRoomScene_hpp
#define SickRoomScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class SickRoomScene:public cocos2d::Scene{
public:
    void onEnter();
    int bedNum;
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SickRoomScene);
    
    cocos2d::Layer* addCalendarLayer();
    
private:
};

#endif /* SickRoomScene_hpp */

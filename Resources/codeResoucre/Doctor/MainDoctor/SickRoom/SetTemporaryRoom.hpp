//
//  SetTemporaryRoom.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/3.
//

#ifndef SetTemporaryRoom_hpp
#define SetTemporaryRoom_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class SetTemporaryRoom:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetTemporaryRoom);
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
private:
    cocos2d::ui::TextField* textfieldHospital;
    cocos2d::ui::TextField* textfieldBuilding;
    cocos2d::ui::TextField* textfieldFloor;
    cocos2d::ui::TextField* textfieldBed;
    
};

#endif /* SetTemporaryRoom_hpp */

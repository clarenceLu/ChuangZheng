//
//  MedicalRecordScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/14.
//

#ifndef MedicalRecordScene_hpp
#define MedicalRecordScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class MedicalRecordScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MedicalRecordScene);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
};

#endif /* MedicalRecordScene_hpp */

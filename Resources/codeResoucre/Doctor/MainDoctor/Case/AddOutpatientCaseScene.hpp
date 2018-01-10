//
//  AddOutpatientCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#ifndef AddOutpatientCaseScene_hpp
#define AddOutpatientCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
class AddOutpatientCaseScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AddOutpatientCaseScene);
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
private:
    TextField* textfieldName;
    TextField* textfieldAge;
    std::string sexLB;

};

#endif /* AddOutpatientCaseScene_hpp */

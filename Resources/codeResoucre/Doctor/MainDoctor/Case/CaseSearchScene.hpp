//
//  CaseSearchScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#ifndef CaseSearchScene_hpp
#define CaseSearchScene_hpp
#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class CaseSearchScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CaseSearchScene);
    
    cocos2d::ui::TextField*  createBasicData(Sprite* bkView,Vec2 point,std::string name1,std::string name2);
    void  createLabelWithoutField(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name);
    
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
private:
    cocos2d::ui::TextField*textFiledName;
    cocos2d::ui::TextField*textFiledSex;
    cocos2d::ui::TextField*textFiledAge;
    cocos2d::ui::TextField*textFiledCase;
    cocos2d::ui::TextField*textFiledDate1;
    cocos2d::ui::TextField*textFiledDate2;
};
#endif /* CaseSearchScene_hpp */

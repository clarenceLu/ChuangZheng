//
//  AccountManageScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/28.
//

#ifndef AccountManageScene_hpp
#define AccountManageScene_hpp

#include "ui/CocosGUI.h"
USING_NS_CC;
class AccountManageScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AccountManageScene);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::Layer* createAlbumLayer();
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    void  createLabelWithoutField(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name);
    cocos2d::Layer* createChangeKeyLayer();
    cocos2d::Layer* createExitLayer();
    
private:
   cocos2d::ui:: TextField* textfieldName;
   cocos2d::ui::  TextField* textfieldPass;
    cocos2d::ui::  TextField*textfieldUser;
    
    cocos2d::ui::TextField *originalPassword;
    cocos2d::ui::TextField *newPassword;
    cocos2d::ui::TextField* surePassword;
};
#endif /* AccountManageScene_hpp */

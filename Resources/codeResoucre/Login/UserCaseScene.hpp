//
//  UserCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#ifndef UserCaseScene_hpp
#define UserCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class UserCaseScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(UserCaseScene);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    cocos2d::Layer* createCaseLayer();
    
    cocos2d::Layer* createInformLayer();
    cocos2d::Layer* createNotificationInformLayer();
    
    cocos2d::Layer* createDynamicLayer();
    
    cocos2d::Layer* createUserInfoLayer();
    
    cocos2d::Layer* createAlbumLayer();
    
    cocos2d::Layer* createCodeLayer();
    
    cocos2d::Layer* createChangeKeyLayer();
    
    cocos2d::Layer* createExitLayer();
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::ui::Button* createMessageBtn(int i, cocos2d::Size  innerSize);
    
    
    
    
  //裁剪字符串
    static std::string subUTF8(const std::string &str, int from, int to);
private:
    static std::vector<std::string> parseUTF8(const std::string &str);
    
    
};
#endif /* UserCaseScene_hpp */

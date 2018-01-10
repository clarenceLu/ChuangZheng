//
//  DocUserInfoScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef DocUserInfoScene_hpp
#define DocUserInfoScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class DocUserInfoScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(DocUserInfoScene);
    cocos2d::Layer* createAlbumLayer();
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
private:
};

#endif /* DocUserInfoScene_hpp */

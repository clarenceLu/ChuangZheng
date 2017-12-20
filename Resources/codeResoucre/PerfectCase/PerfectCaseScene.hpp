//
//  PerfectCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/1.
//

#ifndef PerfectCaseScene_hpp
#define PerfectCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class PerfectCaseScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(PerfectCaseScene);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::Layer* createMessageLayer();
   cocos2d::Layer* createAlbumLayer();

};
#endif /* PerfectCaseScene_hpp */

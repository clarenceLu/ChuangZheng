//
//  WelcomeScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#ifndef WelcomeScene_hpp
#define WelcomeScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class WelcomeScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WelcomeScene);
    
    private:
};


#endif /* WelcomeScene_hpp */

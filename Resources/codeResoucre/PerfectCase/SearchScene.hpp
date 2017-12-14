//
//  SearchScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/12.
//

#ifndef SearchScene_hpp
#define SearchScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class SearchScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SearchScene);
    
};

#endif /* SearchScene_hpp */

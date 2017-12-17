//
//  ChatScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/12.
//

#ifndef ChatScene_hpp
#define ChatScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
class ChatScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ChatScene);
    
};
#endif /* ChatScene_hpp */

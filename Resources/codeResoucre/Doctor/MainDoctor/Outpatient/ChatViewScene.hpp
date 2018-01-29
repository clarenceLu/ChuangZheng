//
//  ChatViewScene.hpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 19/01/2018.
//

#ifndef ChatViewScene_hpp
#define ChatViewScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

class ChatViewScene:public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    void createHubView();
private:
    
    //注：当type为1时接诊病人，当type为2时待接诊病人，当type为3时拒绝病人
};







#endif /* ChatViewScene_hpp */

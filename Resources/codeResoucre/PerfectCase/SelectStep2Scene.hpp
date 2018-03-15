//
//  SelectStep2Scene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/7.
//

#ifndef SelectStep2Scene_hpp
#define SelectStep2Scene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
class SelectStep2Scene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectStep2Scene);
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
private:
    cocos2d::ui::TextField* textFieldContent;
};

#endif /* SelectStep2Scene_hpp */

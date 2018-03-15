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
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
class ChatScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ChatScene);
    cocos2d::ui::Layout* createMessageLayer(int i, cocos2d::Size  innerSize);
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    
    void pushDataToNetWork();
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
private:
    cocos2d::ui::ListView* lv;
    rapidjson::Document infoData;
};
#endif /* ChatScene_hpp */

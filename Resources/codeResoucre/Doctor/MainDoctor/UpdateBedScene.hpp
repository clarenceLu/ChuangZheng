//
//  UpdateBedScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/15.
//

#ifndef UpdateBedScene_hpp
#define UpdateBedScene_hpp

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "QR_Encode.h"
class UpdateBedScene:public cocos2d::Scene{
    public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(UpdateBedScene);
    
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void updateBedToNetWork();
    rapidjson::Document infoData;
private:
    
};

#endif /* UpdateBedScene_hpp */

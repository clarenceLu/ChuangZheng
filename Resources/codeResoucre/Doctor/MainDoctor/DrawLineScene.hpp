//
//  DrawLineScene.hpp
//  looper-mobile
//
//  Created by 工作 on 2018/1/19.
//

#ifndef DrawLineScene_hpp
#define DrawLineScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class DrawLineScene : public cocos2d::Scene{
private:
    // 成员变量(私有的)
    cocos2d::Sprite *sprite;//定义一个精灵成员变量
    Map<int, cocos2d::Sprite*> imageDic;
     Map<int, cocos2d::Sprite*> copyImageDic;
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(DrawLineScene);
    //重载draw方法
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    
    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    int judgeOrigin(Vec2 origin);
    
    ValueVector numSortVector;
    cocos2d::Vec2 getPointfromVector(int i);
//用于传值
    int type;//1代表第一次进入
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork(std::string content);
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void verifyDataToNetWork(std::string content);
    
    
    void showServerMessage( std::string ch );
    
protected:
    rapidjson::Document infoData;
    //自定义draw实现
    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
    cocos2d::CustomCommand _customCommand;
    
    
    DrawNode* drawNode;
};

#endif /* DrawLineScene_hpp */

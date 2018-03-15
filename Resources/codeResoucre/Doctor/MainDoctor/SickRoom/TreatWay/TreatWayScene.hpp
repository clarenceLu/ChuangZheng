//
//  TreatWayScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/11.
//

#ifndef TreatWayScene_hpp
#define TreatWayScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class TreatWayScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TreatWayScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void menuLoginCallback(cocos2d::Ref* pSender);
    Map<int, cocos2d::ui::CheckBox*> boxDic;
    Map<int, cocos2d::Label*> boxTitleDic;
    
    
    cocos2d::ui::Layout *createBlueView(std::string name,int tag);
    cocos2d::Sprite *createWhiteView(int type,int tag);
    Map<int, cocos2d::Sprite*> whiteViewDic;
    void createSelectBox(cocos2d::Vec2 origin,std::string name,int tag,float width,Sprite*bkView);
    void createOtherSelectBox(cocos2d::Vec2 origin,std::string name,int tag,Sprite*bkView);
    
    
    float createResection(int type,int tag,cocos2d::Layer *bkView);
    void createImplant(int type,int tag,cocos2d::Layer *bkView,float height);
    void createMiniOperationView(int type,int tag,cocos2d::Layer *bkView);
    
//network
    std::string changeNumToString(int num);
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
     std::string changeNumToContent(int num);
    
    
private:
    cocos2d::ui::ListView* lv;
    cocos2d::LayerMultiplex *multLayer0;
    cocos2d::LayerMultiplex *multLayer1;
    cocos2d::LayerMultiplex *multLayer2;
    cocos2d::LayerMultiplex *multLayer3;
    cocos2d::LayerMultiplex *multLayer4;
};

#endif /* TreatWayScene_hpp */

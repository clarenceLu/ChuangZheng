//
//  TreatScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#ifndef TreatScene_hpp
#define TreatScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class TreatScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TreatScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createItemLayout(int tag,int type,int index,std::string name);
    void createSelectBox(cocos2d::Vec2 origin,std::string name,int tag,float width,Sprite*bkView);
    cocos2d::ui::TextField*  createBasicData(cocos2d::ui::Layout* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    cocos2d::Layer* createPromptLayer(std::string content);
    
    
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
     void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    Map<int, cocos2d::ui::CheckBox*> boxDic;
    
    
    
    
    cocos2d::ui::Layout *createBlueView(std::string name,int tag);
    void menuLoginCallback(cocos2d::Ref* pSender);
    
    cocos2d::Sprite *createWhiteView(int type,int tag);
    Map<int, cocos2d::Sprite*> whiteViewDic;
    
    
    float createMessage(cocos2d::Vec2 origin,std::string title,std::string content,cocos2d::Sprite*whiteV);
    Map<int, cocos2d::ui::Layout*> layoutDic;
    
private:
    cocos2d::ui::ListView* lv;

};

#endif /* TreatScene_hpp */

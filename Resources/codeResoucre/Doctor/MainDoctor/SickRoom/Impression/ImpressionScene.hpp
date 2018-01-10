//
//  ImpressionScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/9.
//

#ifndef ImpressionScene_hpp
#define ImpressionScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class ImpressionScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ImpressionScene);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createItemLayout(int tag,int type,int index,std::string name);
    cocos2d::Sprite* createWhiteView(int type,int tag,int index);
    void createSelectBox(cocos2d::Vec2 origin,std::string name,int tag,float width,Sprite*bkView);
    
    
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    Map<int, cocos2d::ui::CheckBox*> boxDic;
    
private:
};

#endif /* ImpressionScene_hpp */
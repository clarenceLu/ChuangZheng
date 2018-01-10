//
//  NDIScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/8.
//

#ifndef NDIScene_hpp
#define NDIScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class NDIScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    void  createData();
    CREATE_FUNC(NDIScene);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void menuLoginCallback(cocos2d::Ref* pSender);
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    float creatBlueLabelView(cocos2d::Vec2 origin,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    float createPopUpView(cocos2d::Vec2 point,cocos2d::Sprite* bkView,std::string name,int tag,int type);
    
private:
    //用于存储数据
    ValueMap map1;
    Map<int, Sprite*> wholeDic;
    cocos2d::ui::ScrollView *scrollV;
    Sprite *moveView;
    Map<int, cocos2d::ui::CheckBox*> boxDic;
};

#endif /* NDIScene_hpp */

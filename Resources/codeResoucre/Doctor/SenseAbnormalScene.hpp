//
//  SenseAbnormalScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/22.
//

#ifndef SenseAbnormalScene_hpp
#define SenseAbnormalScene_hpp

#include <stdio.h>
#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class SenseAbnormalScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SenseAbnormalScene);
    
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 origin,Size visibleSize);
    
    
    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    
public:
    double distance;    //两个触摸点之间的距离
    double deltax;    //目标x轴的改变值
    double deltay;    //目标y轴的改变值
    double mscale;   //初始地图缩放比例
    cocos2d::Sprite* imageV;
};



#endif /* SenseAbnormalScene_hpp */

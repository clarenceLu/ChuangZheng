//
//  OperationScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#ifndef OperationScene_hpp
#define OperationScene_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
USING_NS_CC;
class OperationScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(OperationScene);
    
    void menuSelectCallback(cocos2d::Ref* pSender);
    
    
    Label*   createRectButton(cocos2d::Vec2 point,int index,int tag,std::string title);
    
    
    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    
    
    bool judgeTouchMoveWith(cocos2d::Vec2 origin,cocos2d::Ref * ref);
    private:
    //用于储存MenuItemToggle
    std::shared_ptr<Vector<MenuItemToggle*>> spintVector;
};

#endif /* OperationScene_hpp */

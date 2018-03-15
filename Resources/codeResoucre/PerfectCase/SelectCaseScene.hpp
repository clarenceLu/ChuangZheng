//
//  SelectCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/3.
//

#ifndef SelectCaseScene_hpp
#define SelectCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
class SelectCaseScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    CREATE_FUNC(SelectCaseScene);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::ui::ScrollView* createScrollV();
    cocos2d::Layer*  createSelectMeterLayer();
    
    //读取json数据
    typedef struct data
    {
        std::string   title;
        const  cocos2d::ccArray*  content;
    }data;
    
    void getJsonData(std::string filename, std::vector<data> &vec);
    std::vector<data> _VecData;
    
    
    
    std::string changeNumToString(int num);
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
private:
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
};
#endif /* SelectCaseScene_hpp */

//
//  NetWrokMangerData.hpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 29/11/2017.
//

#ifndef NetWrokMangerData_hpp
#define NetWrokMangerData_hpp

#include <cocos2d.h>
#include <stdio.h>
#include "network/HttpClient.h"
#include <iostream>

using namespace cocos2d::network;
using namespace std;

class NetWorkManger:public cocos2d::Ref
{


public:
    
    ~NetWorkManger();
    
    static NetWorkManger* sharedWorkManger();
    
    void sendMessage(string UrlStr,const ccHttpRequestCallback& callback);
    
    
    void onHttpRequestCompleted(HttpClient* sender,HttpResponse* response);
    
private:

    NetWorkManger();

    
};


#endif 






//
//  NetWrokMangerData.cpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 29/11/2017.
//

#include "NetWrokMangerData.hpp"
#include "cocos2d.h"
#include "network/HttpClient.h"
#include <iostream>
#include "json/rapidjson.h"

#include "json/document.h"

#include "json/writer.h"

#include "json/stringbuffer.h"


using namespace rapidjson; // 命名空间
using namespace std;
using namespace cocos2d::network;
using namespace cocos2d;

NetWorkManger::NetWorkManger()
{
    
    
    
}

NetWorkManger::~NetWorkManger()
{
    

}
NetWorkManger * NetWorkManger::sharedWorkManger()
{
    static NetWorkManger instance;
    return  &instance;
}

void NetWorkManger::sendMessage(string UrlStr,const ccHttpRequestCallback& callback,char *requestDataStr)
{
    
    HttpRequest* request = new  HttpRequest();

    
    request->setUrl(UrlStr);
    
    request->setRequestType(HttpRequest::Type::POST);
    
    request->setUserData(requestDataStr);
    
    request->setResponseCallback(callback);

    HttpClient::getInstance()->sendImmediate(request);
    request->release();
}

void NetWorkManger::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    cout<<recieveData.length()<<endl;
    cout<<recieveData<<endl;
    
    rapidjson::Document d;
    
    d.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (d.HasParseError()) {
        
        return;
    }

    if(d.HasMember("data")){
        for(int i = 0; i < d["data"].Size(); i++) {
            
            rapidjson::Value& object = d["data"][i];
            
            CCLOG("%s", object["artistheaderimageurl"].GetString());
        }
    }
}

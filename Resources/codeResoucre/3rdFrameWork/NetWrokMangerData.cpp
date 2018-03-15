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


void NetWorkManger::upLoadData(string UrlStr,const ccHttpRequestCallback& callback,char *requestData,size_t len)
{
    
    HttpRequest* request = new  HttpRequest();
    
    vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    request -> setHeaders(headers);
    
    request->setUrl(UrlStr);
    
    request->setRequestType(HttpRequest::Type::POST);
    
    request->setRequestData((char*)requestData,len);
    
    request->setResponseCallback(callback);
    
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
}


void NetWorkManger::sendMessage(string UrlStr,const ccHttpRequestCallback& callback,char *requestDataStr)
{
    
    HttpRequest* request = new  HttpRequest();
    
    request->setUrl(UrlStr);
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(callback);
     if (requestDataStr!=nullptr) {
    const  char* postData = requestDataStr;
    request->setRequestData(postData,strlen(postData) );
     }
    request->setTag("POST test1");
    
    HttpClient::getInstance()->send(request);
     request->release();
     
}

//当传送json数据时需要使用此方法
void NetWorkManger::postHttpRequest(string UrlStr,const ccHttpRequestCallback& callback,char* requestDataStr){
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl(UrlStr);
    request -> setRequestType(HttpRequest::Type::POST);
     request->setResponseCallback(callback);
    auto postData = requestDataStr;
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    // 设置请求头，如果数据为键值对则不需要设置
//    request -> setHeaders(headers);
    // 传入发送的数据及数据ch n g
     if (requestDataStr!=nullptr) {
    request -> setRequestData(postData, strlen(postData));
     }
    request -> setTag("POST TEST");
    HttpClient::getInstance() -> send(request);
    request -> release();
}


void NetWorkManger::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        log("%s compeled",response->getHttpRequest()->getTag());
    }
    
    if (!response->isSucceed()) {
        log("response failed");
        log("error buffer:%s",response->getErrorBuffer());
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





/*string NetWorkManger::changeUTF8ToUnicode(string str){
 size_t sSize=str.length();
 wchar_t * dBuf=NULL;
 //    <SPAN style="COLOR: #ff0000">//注意：需要多分配一个空间，以存放终止符</SPAN>
 int dSize=mbstowcs(dBuf, str.c_str(), 0)+1;
 dBuf=new wchar_t[dSize];
 wmemset(dBuf, 0, dSize);
 int nRet=mbstowcs(dBuf, str.c_str(), sSize);
 if(nRet<=0){
 printf("转换失败\n");}
 else{
 printf("转换成功%d字符\n", nRet);
 wprintf(L"%ls\n", dBuf);
 //wchar_t转化为char
 int len = wcstombs(NULL,dBuf,0);
 char* buf = new char[len+1];
 wcstombs(buf,dBuf,len);
 buf[len] = 0;
 return buf;
 }
 return str;
 }*/

//
//  DrawLineScene.cpp
//  looper-mobile
//
//  Created by 工作 on 2018/1/19.
//

#include "DrawLineScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene * DrawLineScene::createScene(){
    return DrawLineScene::create();
}
bool DrawLineScene::init(){
    if (!Scene::init()) {
        return false;
    }
    //获取屏幕大小
    auto size = Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_deblock.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(size);
    this->addChild(bkView,-1);
    
    drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    for (int i=0; i<9; i++) {
        auto imageV1=Sprite::create("circle_deblock.png");
        imageV1->setPosition(Vec2(96+170*(i%3), 618-170*(i/3)));
        imageV1->setContentSize(Size(102, 102));
        imageV1->setAnchorPoint(Vec2(0, 0));
        addChild(imageV1);
        imageDic.insert(i, imageV1);
        copyImageDic.insert(i, imageV1);
    }
    
    //添加触控监听
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_2(DrawLineScene::onTouchesBegan,this);
    listen->onTouchesMoved = CC_CALLBACK_2(DrawLineScene::onTouchesMoved,this);
    listen->onTouchesEnded = CC_CALLBACK_2(DrawLineScene::onTouchesEnded,this);
    listen->onTouchesCancelled = CC_CALLBACK_2(DrawLineScene::onTouchesCancelled,this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
    
    
    return true;
}
void DrawLineScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawLineScene::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}
void DrawLineScene::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
{
    //利用Stack缓存
    Director *director = Director::getInstance();
    //CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    CHECK_GL_ERROR_DEBUG();
    Color4F colorRGB=Color4F(91/255.0, 144/255.0, 229/255.0, 1.0);
    //画边框
    if (numSortVector.size()==2) {
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 vertices[] = {origin1,origin2};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
    }else if(numSortVector.size()==3){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 vertices[] = {origin1,origin2,origin3};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
    }else if(numSortVector.size()==4){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 origin4=getPointfromVector(3);
        Vec2 vertices[] = {origin1,origin2,origin3,origin4};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
        drawNode->drawSegment(origin3, origin4, 10, colorRGB);
    }
    else if(numSortVector.size()==5){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 origin4=getPointfromVector(3);
        Vec2 origin5=getPointfromVector(4);
        Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
        drawNode->drawSegment(origin3, origin4, 10, colorRGB);
         drawNode->drawSegment(origin4, origin5, 10, colorRGB);
    } else if(numSortVector.size()==6){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 origin4=getPointfromVector(3);
        Vec2 origin5=getPointfromVector(4);
        Vec2 origin6=getPointfromVector(5);
        Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
        drawNode->drawSegment(origin3, origin4, 10, colorRGB);
        drawNode->drawSegment(origin4, origin5, 10, colorRGB);
        drawNode->drawSegment(origin5, origin6, 10, colorRGB);
    }else if(numSortVector.size()==7){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 origin4=getPointfromVector(3);
        Vec2 origin5=getPointfromVector(4);
        Vec2 origin6=getPointfromVector(5);
        Vec2 origin7=getPointfromVector(6);
        Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6,origin7};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
        drawNode->drawSegment(origin3, origin4, 10, colorRGB);
        drawNode->drawSegment(origin4, origin5, 10, colorRGB);
        drawNode->drawSegment(origin5, origin6, 10, colorRGB);
        drawNode->drawSegment(origin6, origin7, 10, colorRGB);
    }else if(numSortVector.size()==8){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 origin4=getPointfromVector(3);
        Vec2 origin5=getPointfromVector(4);
        Vec2 origin6=getPointfromVector(5);
        Vec2 origin7=getPointfromVector(6);
        Vec2 origin8=getPointfromVector(7);
        Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6,origin7,origin8};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
        drawNode->drawSegment(origin3, origin4, 10, colorRGB);
        drawNode->drawSegment(origin4, origin5, 10, colorRGB);
        drawNode->drawSegment(origin5, origin6, 10, colorRGB);
        drawNode->drawSegment(origin6, origin7, 10, colorRGB);
        drawNode->drawSegment(origin7, origin8, 10, colorRGB);
    }else if(numSortVector.size()==9){
        Vec2 origin1=getPointfromVector(0);
        Vec2 origin2=getPointfromVector(1);
        Vec2 origin3=getPointfromVector(2);
        Vec2 origin4=getPointfromVector(3);
        Vec2 origin5=getPointfromVector(4);
        Vec2 origin6=getPointfromVector(5);
        Vec2 origin7=getPointfromVector(6);
        Vec2 origin8=getPointfromVector(7);
        Vec2 origin9=getPointfromVector(8);
        Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6,origin7,origin8,origin9};
        drawNode->drawSegment(origin1, origin2, 10, colorRGB);
        drawNode->drawSegment(origin2, origin3, 10, colorRGB);
        drawNode->drawSegment(origin3, origin4, 10, colorRGB);
        drawNode->drawSegment(origin4, origin5, 10, colorRGB);
        drawNode->drawSegment(origin5, origin6, 10, colorRGB);
        drawNode->drawSegment(origin6, origin7, 10, colorRGB);
        drawNode->drawSegment(origin7, origin8, 10, colorRGB);
        drawNode->drawSegment(origin8, origin9, 10, colorRGB);
    }
    CHECK_GL_ERROR_DEBUG();
    //绘制停止，释放
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

Vec2 DrawLineScene::getPointfromVector(int i){
   auto num= numSortVector.at(i).asInt();
    Vec2 origin=Vec2(147+170*(num%3), 669-170*(num/3));
    return Vec2(origin.x, origin.y);
}

//触摸事件开始，手指按下时
void DrawLineScene::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches.at(0);
    //右指，从左往右的时候为扩大，从右往左的时候为缩放
    auto pos1 = touch->getLocation();
    auto pos2 = touch->getLocationInView();
    auto pos3 = Director::getInstance()->convertToUI(pos2);
    if (touches.size()==1){
#pragma-清空ValueVector
        numSortVector.clear();
        for (int i=0; i<9; i++) {
            Sprite *item=copyImageDic.at(i);
            imageDic.insert(i, item);
        }
        log("vector size %ld,imageDic size %ld",numSortVector.size(),imageDic.size());
    }
    drawNode->clear();
}

//触摸移动事件，也就是手指在屏幕滑动的过程
void DrawLineScene::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    auto touch = touches.at(0);
    //右指，从左往右的时候为扩大，从右往左的时候为缩放
    auto pos1 = touch->getLocation();
    auto pos2 = touch->getLocationInView();
    auto pos3 = Director::getInstance()->convertToUI(pos2);
//    log("pos1 x: %f, y: %f",pos1.x,pos1.y);
//    log("pos2 x: %f, y: %f",pos2.x,pos2.y);
//    log("pos3 x: %f, y: %f",pos3.x,pos3.y);
//    log("touch size %ld",touches.size());
     if (judgeOrigin(pos1)!=-1){ //设定起点
        log("%d",judgeOrigin(pos1));
         Sprite*imageV=imageDic.at(judgeOrigin(pos1));
        Vec2 origin=Vec2(imageV->getPosition().x+imageV->getContentSize().width/2, imageV->getPosition().y+imageV->getContentSize().height/2);
         numSortVector.push_back(Value(judgeOrigin(pos1)));
        imageDic.erase(judgeOrigin(pos1));//去除重复的点
     }
}

//触摸事件结束，也就是手指松开时
void DrawLineScene::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
//字符串拼接
    char content[50];
    strcpy(content, "") ;
    for (int i=0; i<numSortVector.size(); i++) {
        auto num= numSortVector.at(i).asInt();
        char str[50];
        sprintf(str,"%d",num);
         log("num  %s",str);
        strcat(content, str);
    }
    log("content%s",content);
#pragma-核对结果是否正确
    string result=content;
    if (result=="03678") {
        log("验证成功");
        showServerMessage("验证成功");
        Director::getInstance()->popScene();
    }else if(result!=""){
     showServerMessage("手势错误");
    }
    log("TouchTest onTouchesEnded");
}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断
void DrawLineScene::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    log("TouchTest onTouchesCancelled");
}
int DrawLineScene::judgeOrigin(Vec2 origin){
    for (int i=0; i<9; i++) {
        Sprite *item=imageDic.at(i);
        if (item!=nullptr) {
            if (origin.x>=item->getPosition().x&&origin.x<=item->getContentSize().width+item->getPosition().x&&origin.y>=item->getPosition().y&&origin.y<=item->getContentSize().height+item->getPosition().y) {
                return i;
            }
        }
    }
    return -1;
}


void DrawLineScene::showServerMessage( string ch )
{
    auto size = Director::getInstance()->getVisibleSize();
    auto judgeV = Label::createWithSystemFont(ch,"Arial",40,Size(size.width,50),TextHAlignment::CENTER,TextVAlignment::CENTER);
    judgeV->setPosition(Vec2(size.width/2, 850));
    judgeV->setTextColor(Color4B(91, 144, 229, 255));
    judgeV->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(judgeV);
    judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
}





/*   Director *director = Director::getInstance();
 //CCASSERT(nullptr != director, "Director is null when setting matrix stack");
 director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
 director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
 CHECK_GL_ERROR_DEBUG();
 //画边框
    DrawPrimitives::setDrawColor4B(91, 144, 229, 255);
    glLineWidth(20);
 if (numSortVector.size()==2) {
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 vertices[] = {origin1,origin2};
DrawPrimitives::drawPoly(vertices, 2, false);
 }else if(numSortVector.size()==3){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 vertices[] = {origin1,origin2,origin3};
        DrawPrimitives::drawPoly(vertices, 3, false);
 }else if(numSortVector.size()==4){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 origin4=getPointfromVector(3);
 Vec2 vertices[] = {origin1,origin2,origin3,origin4};
        DrawPrimitives::drawPoly(vertices, 4, false);
 }
 else if(numSortVector.size()==5){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 origin4=getPointfromVector(3);
 Vec2 origin5=getPointfromVector(4);
 Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5};
 DrawPrimitives::drawPoly(vertices, 5, false);
 } else if(numSortVector.size()==6){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 origin4=getPointfromVector(3);
 Vec2 origin5=getPointfromVector(4);
 Vec2 origin6=getPointfromVector(5);
 Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6};
 DrawPrimitives::drawPoly(vertices, 6, false);
 }else if(numSortVector.size()==7){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 origin4=getPointfromVector(3);
 Vec2 origin5=getPointfromVector(4);
 Vec2 origin6=getPointfromVector(5);
 Vec2 origin7=getPointfromVector(6);
 Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6,origin7};
 DrawPrimitives::drawPoly(vertices, 7, false);
 }else if(numSortVector.size()==8){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 origin4=getPointfromVector(3);
 Vec2 origin5=getPointfromVector(4);
 Vec2 origin6=getPointfromVector(5);
 Vec2 origin7=getPointfromVector(6);
 Vec2 origin8=getPointfromVector(7);
 Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6,origin7,origin8};
 DrawPrimitives::drawPoly(vertices, 8, false);
 }else if(numSortVector.size()==9){
 Vec2 origin1=getPointfromVector(0);
 Vec2 origin2=getPointfromVector(1);
 Vec2 origin3=getPointfromVector(2);
 Vec2 origin4=getPointfromVector(3);
 Vec2 origin5=getPointfromVector(4);
 Vec2 origin6=getPointfromVector(5);
 Vec2 origin7=getPointfromVector(6);
 Vec2 origin8=getPointfromVector(7);
 Vec2 origin9=getPointfromVector(8);
 Vec2 vertices[] = {origin1,origin2,origin3,origin4,origin5,origin6,origin7,origin8,origin9};
 DrawPrimitives::drawPoly(vertices, 9, false);
 }else{
 Vec2 vertices[] = {Vec2(100, 100)};
 DrawPrimitives::drawPoly(vertices, 1, false);
 }
 
 
 CHECK_GL_ERROR_DEBUG();
 //绘制停止，释放
 director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
 */

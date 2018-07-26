#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

class VisibleRect
{
public:
    static cocos2d::Rect getVisibleRect();
    static cocos2d::Vec2 left();
    static cocos2d::Vec2 right();
    static cocos2d::Vec2 top();
    static cocos2d::Vec2 bottom();
    static cocos2d::Vec2 center();
    static cocos2d::Vec2 leftTop();
    static cocos2d::Vec2 rightTop();
    static cocos2d::Vec2 leftBottom();
    static cocos2d::Vec2 rightBottom();
	static cocos2d::Rect rect12ByIndex(int index);//12的阵列
	static cocos2d::Vec2 splitBySum(int sum, int index,float length, int ScaleToPadding);  //将length 分为 sum , 次元素为第几个位置,weightScaleToPadding 表示元素和间隔的比例
	static cocos2d::Rect splitScreenAsRect(int row ,cocos2d::Vec2 vec,int weightScaleToPadding,int heightScaleToPadding, int column);	//将屏幕分为vec2(numberX,numberY) numberX*numberY 数量的矩形,具体位置由c(x,y) 决定,左下角为c(0,0),并且要设定横纵间距比例
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */

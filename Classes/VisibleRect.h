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
	//改进:该函数应该是将某块rect分为x*y,你想想相对: 精灵本身当做屏幕,其本身可以再添加节点
	static cocos2d::Rect splitScreenAsRect(int row, cocos2d::Vec2 vec, int weightScaleToPadding = 2,
		int heightScaleToPadding = 3, int column = 10, float witdhAll = s_visibleRect.size.width, float heightAll = s_visibleRect.size.height);	//将屏幕分为vec2(numberX,numberY) numberX*numberY 数量的矩形,具体位置由c(x,y) 决定,左下角为c(0,0),并且要设定横纵间距比例
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */

#include "VisibleRect.h"
#include "Util.h"

/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


USING_NS_CC;

Rect VisibleRect::s_visibleRect;

void VisibleRect::lazyInit()
{
    // no lazy init
    // Useful if we change the resolution in runtime
    s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect VisibleRect::getVisibleRect()
{
    lazyInit();
    return s_visibleRect;
}

Vec2 VisibleRect::left()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 VisibleRect::right()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 VisibleRect::top()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 VisibleRect::bottom()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

Vec2 VisibleRect::center()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 VisibleRect::leftTop()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 VisibleRect::rightTop()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 VisibleRect::leftBottom()
{
    lazyInit();
    return s_visibleRect.origin;
}

Vec2 VisibleRect::rightBottom()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}
/*
 *-------------------------
 *
 *	__	  __	__
 * |  |	 |  |  |  |
 * |9|	 |  |  |  |
 * |__|  |__|  |__|    左右间距 △width=1/2  卡牌width
 *
 *	__	  __	__	   上下间距 △height=1/3 卡牌height
 * |  |	 |  |  |  |
 * |6 |	 |  |  |  |
 * |__|  |__|  |__|	   整体将visualRect分为height/4  或者/3  
 * 
 *					   横排对三求余数+1
 *                     
 *                     竖排对三求商+1
 * 
 * 
 * 	__	  __	__
 * |  |	 |  |  |  |
 * |3 |	 |  |  |  |
 * |__|  |__|  |__|
 *
 *	__	  __	__
 * |  |	 |  |  |  |
 * |0 |	 |  |  |  |
 * |__|  |__|  |__|
 * 
 * 
 * --------------------------
 *  index 0-11
 */
Rect VisibleRect::Rect12ByIndex(int index)
{
	lazyInit();
	int sumHeightNumber = 3;	//表示将屏幕高分为几分
	int weightScaleToPadding = 2;  //表示卡片是间隔倍数
	int heightScaleToPadding = 3;  //表示卡片是间隔倍数

	auto visualWidth= s_visibleRect.size.width;
	auto visualHeight = s_visibleRect.size.height;
	//先计算缩放比例
	auto height0 = visualHeight / sumHeightNumber;
	auto weight0 = visualWidth;
	auto height1 = height0 / (heightScaleToPadding*2+3);
	auto weight1 = weight0 /(weightScaleToPadding*3+4) ;
	cocos2d:Vec2 vecCard(weight1 * 2, height1 * 3);
	//
	std::cout << "height0" << " " << height0<<std::endl;
	std::cout << "weight0" << " " << weight0 << std::endl;
	std::cout << "height1" << " " << height1 << std::endl;
	std::cout << "weight1" << " " << weight1 << std::endl;
	//计算坐标
	auto x = ((index % 3) + 1)*weight1 + (index % 3)*weight1 * weightScaleToPadding;
	int temp=index;
	if (index > 5)
		temp -= 6;
	auto y = ((temp / 3) + 1)*height1 + (temp / 3)*height1*heightScaleToPadding;
	if (index > 5)
		y += (visualHeight- height0);
	return Rect(x, y, vecCard.x, vecCard.y);
}

cocos2d::Rect VisibleRect::BottomByIndex(int sum, int index)
{
	lazyInit();
}

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
	isInit = true;
}

Rect VisibleRect::getVisibleRect()
{
	if(!isInit)
    lazyInit();
    return s_visibleRect;
}

Vec2 VisibleRect::left()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 VisibleRect::right()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 VisibleRect::top()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 VisibleRect::bottom()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

Vec2 VisibleRect::center()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 VisibleRect::leftTop()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 VisibleRect::rightTop()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 VisibleRect::leftBottom()
{
	if (!isInit)
		lazyInit();
    return s_visibleRect.origin;
}

Vec2 VisibleRect::rightBottom()
{
	if (!isInit)
		lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}
/*
 *-------------------------
 *
 *	__	  __	__
 * |  |	 |  |  |  |
 * |9|	 |  |  |  |
 * |__|  |__|  |__|    ���Ҽ�� ��width=1/2  ����width
 *
 *	__	  __	__	   ���¼�� ��height=1/3 ����height
 * |  |	 |  |  |  |
 * |6 |	 |  |  |  |
 * |__|  |__|  |__|	   ���彫visualRect��Ϊheight/4  ����/3  
 * 
 *					   ���Ŷ���������+1
 *                     
 *                     ���Ŷ�������+1
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
 *  
 *  ��ЩԪ��ê��ҪΪ 0,0
 */
Rect VisibleRect::rect12ByIndex(int index)
{
	if (!isInit)
		lazyInit();
	int sumHeightNumber = 3;	//��ʾ����Ļ�߷�Ϊ����
	int weightScaleToPadding = 2;  //��ʾ��Ƭ�Ǽ������
	int heightScaleToPadding = 3;  //��ʾ��Ƭ�Ǽ������

	auto visualWidth= s_visibleRect.size.width;
	auto visualHeight = s_visibleRect.size.height;
	//�ȼ������ű���
	auto height0 = visualHeight / sumHeightNumber;
	// auto weight0 = visualWidth;
	// auto height1 = height0 / (heightScaleToPadding*2+3);
	// auto weight1 = weight0 /(weightScaleToPadding*3+4) ;
	// cocos2d:Vec2 vecCard(weight1 * 2, height1 * 3);
	// //
	// std::cout << "height0" << " " << height0<<std::endl;
	// std::cout << "weight0" << " " << weight0 << std::endl;
	// std::cout << "height1" << " " << height1 << std::endl;
	// std::cout << "weight1" << " " << weight1 << std::endl;
	// //��������
	// auto x = ((index % 3) + 1)*weight1 + (index % 3)*weight1 * weightScaleToPadding;
	// int temp=index;
	// if (index > 5)
	// 	temp -= 6;
	// auto y = ((temp / 3) + 1)*height1 + (temp / 3)*height1*heightScaleToPadding;
	// if (index > 5)
	// 	y += (visualHeight- height0);
	// return Rect(x, y, vecCard.x, vecCard.y);
	cocos2d::Vec2 vX = splitBySum(3, index, visualWidth, weightScaleToPadding);
	cocos2d::Vec2 vY = splitBySum(2, index, height0, heightScaleToPadding);
	if (index > 5)
		vY.x = vY.x + (visualHeight - height0);
	return Rect(vX.x, vY.x, vX.y, vY.y);
}

/**
 *  ѡ�����ⳤ��,�����ȷ�Ϊsum��,indexΪ�ڼ���
 * 
 *	@sum ��ʾҪ�ֵķ�Χ����
 *	@index ��ʾλ�ô�0��ʼ
 *	@length ��ʾҪ�ֵĴ�С
 *	@ScaleToPadding ��ʾԪ��:���]
 *	������Ϊ0��ʾ�����ռ
 */
cocos2d::Vec2 VisibleRect::splitBySum(int sum, int index, float length, int ScaleToPadding=2)
{
	if (!isInit)
		lazyInit();
	if(ScaleToPadding!=0)
	{
		auto visualWidth = length;
		auto lenth0 = visualWidth / (sum + 1 + sum * ScaleToPadding);
		auto postion = ((index%sum) + 1)*lenth0 + (index%sum)*lenth0*ScaleToPadding;
		return Vec2(postion, lenth0*ScaleToPadding);
	}
	else
	{
		return Vec2(0, length);
	}
}

/**
 * �����ηֳ�row*column��
 *	@row 
 *	@colum
 *	@vec ��ʾԪ�طֽ�����ڵڼ�������λ��
 *	@weightScaleToPadding ��ʾԪ�ؿ�:���� Ĭ��Ϊ2
 *	@heightScaleToPadding ��ʾԪ�ظ�:�߼�� Ĭ��Ϊ3
 */
cocos2d::Rect VisibleRect::splitScreenAsRect(int row, cocos2d::Vec2 vec, int weightScaleToPadding ,
	int heightScaleToPadding , int column , float witdhAll, float heightAll)
{
	if (!isInit)
		lazyInit();

	cocos2d::Vec2 vecX = splitBySum(row, vec.x, witdhAll, weightScaleToPadding);
	cocos2d::Vec2 vecY = splitBySum(column, vec.y, heightAll, heightScaleToPadding);
	return cocos2d::Rect(vecX.x, vecY.x, vecX.y, vecY.y);
}

bool VisibleRect::isInit = false;
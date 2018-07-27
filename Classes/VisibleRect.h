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
	static cocos2d::Rect rect12ByIndex(int index);//12������
	static cocos2d::Vec2 splitBySum(int sum, int index,float length, int ScaleToPadding);  //��length ��Ϊ sum , ��Ԫ��Ϊ�ڼ���λ��,weightScaleToPadding ��ʾԪ�غͼ���ı���
	//�Ľ�:�ú���Ӧ���ǽ�ĳ��rect��Ϊx*y,���������: ���鱾������Ļ,�䱾���������ӽڵ�
	static cocos2d::Rect splitScreenAsRect(int row, cocos2d::Vec2 vec, int weightScaleToPadding = 2,
		int heightScaleToPadding = 3, int column = 10, float witdhAll = s_visibleRect.size.width, float heightAll = s_visibleRect.size.height);	//����Ļ��Ϊvec2(numberX,numberY) numberX*numberY �����ľ���,����λ����c(x,y) ����,���½�Ϊc(0,0),����Ҫ�趨���ݼ�����
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */

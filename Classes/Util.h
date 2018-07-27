#ifndef TEMPLATECPP_UTIL_h
#define TEMPLATECPP_UTIL_h
#include "math/Vec2.h"
#include "base/CCDirector.h"
#include "json/document.h"
#include <iostream>
#include "Data/data.h"
#include "json/writer.h"
#include "platform/CCFileUtils.h"
#include <stdlib.h>
#include "VisibleRect.h"
#include "marco.h"
#include "Particle3D/PU/CCPUSineForceAffector.h"


class Util
{
public:
	//-------------------------------精灵大小位置处理--------------------------------------
	//如果涉及到调整位置的话,就要把锚点设置为0 0

	/*
	*  将图片缩放 x y 缩放为屏幕的 sx ,sy倍
	*	@sX 表示精灵要缩放x比例倍数
	*	@sY 表示精灵要缩放y比例倍数
	*	@oSize 表示经理大小
	*	@sprite 表示要进行缩放的精灵
	*	@width 表示要进行比较的width
	*	@height 表示要进行比较的height
	*/

	static void setScaleRatio(float sX, float sY, cocos2d::Size oSize, cocos2d::Node* sprite, float width = cocos2d::Director::getInstance()->getVisibleSize().width, float height = cocos2d::Director::getInstance()->getVisibleSize().height)
	{
		auto width0 = width * sX;
		auto height0 = height * sY;
		float xScale = width0 / oSize.width;
		float yScale = height0 / oSize.height;
		sprite->setScale(xScale, yScale);
		// RECT_PRINT("精灵缩放后", cocos2d::Rect(sprite->getPosition().x, sprite->getPosition().y, sprite->getContentSize().width, sprite->getContentSize().height))
	}
	/**
	 * 缩放至全屏
	*  @filePath 文件名称
	*  @scene 场景
	*/
	static void setBackGround(std::string filePath, cocos2d::Scene* sence, int zOrder = 0)
	{
		auto back = cocos2d::Sprite::create(filePath);
		//首先拉伸或者缩放背景	
		setScaleRatio(1, 1, back->getContentSize(), back);
		back->setPosition(VisibleRect::center());
		sence->addChild(back, 0);
	}
	

	/**
	* 进行缩放,对精灵进行12格缩放并且设置位置
	*	0-11
	*	改变锚点的位置
	*/
	static void get12RectByIndex(int index, cocos2d::Node* sprite)
	{
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		auto rect = VisibleRect::rect12ByIndex(index);
		
		setNodePostionScale(sprite, rect);
	}
	/**
	 * 将节点设置为特定位置,并且进行一个缩放
	 */
	static void setNodePostionInScreen(cocos2d::Node* sprite, int row, cocos2d::Vec2 vec, int weightScaleToPadding,
		int heightScaleToPadding, int column)
	{
		auto rect = VisibleRect::splitScreenAsRect( row, vec, weightScaleToPadding, heightScaleToPadding, column);
		//测试
		// RECT_PRINT("获取的缩放", rect)
		setNodePostionScale(sprite, rect);
	}
	/**
	 * 跟上边函数相对比这是一个相对矩形
	 */
	static void setNodePostionInRect(cocos2d::Node* sprite, int row, cocos2d::Vec2 vec, int weightScaleToPadding,
		int heightScaleToPadding, int column, cocos2d::Size size)
	{
		auto rect=VisibleRect::splitScreenAsRect(row, vec, weightScaleToPadding, heightScaleToPadding, column,size.width,size.height);
		setNodePostionScale(sprite, rect);
	}
	//进行缩放,并设置位置
private:
	static void setNodePostionScale(cocos2d::Node* sprite, cocos2d::Rect rect)
	{
		sprite->setAnchorPoint(cocos2d::Vec2(0,0));
		sprite->setPosition(rect.origin.x, rect.origin.y);
		setScaleRatio(1, 1, sprite->getContentSize(), sprite, rect.size.width, rect.size.height);
	}
public:
	//--------------------------------------io处理----------------------------------------
	/**
	* 通过读取json文件获取当前用户拥有的数据
	*/
	static std::vector<spriteData> getInitSprite()
	{
		rapidjson::Document doc;
		std::vector<spriteData> vector;
		//读取内容
		ssize_t size = 0;
		unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData("config.json", "r", &size);
		if (content)
		{
			std::string str(reinterpret_cast<const char*>(content), size);
			doc.Parse<0>(str.c_str());
			// std::cout << doc.GetType();
			//使用迭代器
			for (rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
			{
				// std::cout << itr->name.GetString();
				spriteData d;
				d.className = itr->name.GetString();
				// std::cout << itr->value.GetObjectW()["level"].GetInt();
				d.level = itr->value.GetObject()["level"].GetInt();
				vector.push_back(d);
			}
		}
		return vector;
	}
	/**
	* 修改当前用户用于的sprite
	*/
	static void insertJson(std::vector<spriteData> vector)
	{
		rapidjson::Document jsonDoc;
		rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator(); //获取分配器
		jsonDoc.SetObject();
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		//创建doc
		for (spriteData s : vector)
		{
			rapidjson::Value value(rapidjson::kObjectType);
			value.AddMember("level", 1, allocator);
			rapidjson::Value valueName(rapidjson::kStringType);
			valueName.SetString(s.className.c_str(), s.className.length(), allocator);
			jsonDoc.AddMember(valueName, value, allocator);
		}
		jsonDoc.Accept(writer);
		std::cout << buffer.GetString();
		cocos2d::FileUtils::getInstance()->writeStringToFile(buffer.GetString(), "config.json");
	}
	/**
	* 获取所有的精灵plist文件信息
	*/
	static std::vector<plistData> getAllSpriteData()
	{
		rapidjson::Document doc;
		std::vector<plistData> vector;
		//读取内容
		ssize_t size = 0;
		unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData("plistJson.json", "r", &size);
		if (content)
		{
			std::string str(reinterpret_cast<const char*>(content), size);
			doc.Parse<0>(str.c_str());
			for (rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
			{
				plistData d;
				d.plist = itr->name.GetString();
				// std::cout << d.plist<<std::endl;
				d.png = itr->value.GetObject()["png"].GetString();
				// std::cout << d.png<<std::endl;
				auto arrays = itr->value.GetObject()["spriteName"].GetArray();
				for (rapidjson::SizeType index = 0; index < arrays.Size(); ++index)
				{
					// std::cout << arrays[index].GetString() << std::endl;
					d.spriteName[index] = arrays[index].GetString();
				}
				auto arrays2 = itr->value.GetObject()["spriteBack"].GetArray();
				for (rapidjson::SizeType index = 0; index < arrays.Size(); ++index)
				{
					// std::cout << arrays[index].GetString() << std::endl;
					d.spriteBack[index] = arrays[index].GetString();
				}
				vector.push_back(d);
			}
		}
		return vector;
	}
	//-------------------------------------------------------------算法--------------------------------------------
	//产生一个范围随机数 0---ran-1
	static int getRandom(int ran)
	{
		srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
		return rand() % ran;
	}
	//简单的概率机制 0-100
	static bool getProbability(int rate)
	{
		if (rate == 0)
			return false;
		srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
		const int result = (rand() % 100)+1; //1-100
		return 0 < result <= rate;
	}
};
#endif TEMPLATECPP_UTIL_h

 






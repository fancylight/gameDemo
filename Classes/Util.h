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

class Util
{
public:
	/*
	*  将图片缩放 x y 缩放为屏幕的 sx ,sy倍
	*	@sX 表示精灵要缩放x比例倍数
	*	@sY 表示精灵要缩放y比例倍数
	*	@oSize 表示经理大小
	*	@sprite 表示要进行缩放的精灵
	*	@width 表示要进行比较的width
	*	@height 表示要进行比较的height
	*/

	static void setScaleRatio(float sX, float sY, cocos2d::Size oSize, cocos2d::Sprite* sprite, float width = cocos2d::Director::getInstance()->getVisibleSize().width, float height = cocos2d::Director::getInstance()->getVisibleSize().height)
	{
		auto width0 = width * sX;
		auto height0 = height * sY;
		float xScale = width0 / oSize.width;
		float yScale = height0 / oSize.height;
		sprite->setScale(xScale, yScale);
		std::cout << "执行了";
	}
	//该文件存放一些处理用的函数
	/**
	* 获取缩放到看见size大小
	*/
	static void setScaleVisiableSize(cocos2d::Sprite* sprite)
	{
		setScaleRatio(1, 1, sprite->getContentSize(), sprite);
	}
	/**
	* 进行缩放,对精灵进行12格缩放并且设置位置
	*	0-11
	*	改变锚点的位置
	*/
	static void get12RectByIndex(int index, cocos2d::Sprite* sprite)
	{
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		auto rect = VisibleRect::Rect12ByIndex(index);
		sprite->setPosition(rect.origin.x, rect.origin.y);
		setScaleRatio(1, 1, sprite->getContentSize(), sprite, rect.size.width, rect.size.height);
	}
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
	//产生一个范围随机数 0---ran-1
	static int getRandom(int ran)
	{
		srand(static_cast<unsigned int>(time(0))); // 设置随机数种子
		return rand() % ran;
	}
	/**
	 *  @filePath 文件名称
	 *  @scene 场景
	 */
	static void setBackGround(std::string filePath, cocos2d::Scene* sence,int zOrder=0)
	{
		auto back = cocos2d::Sprite::create(filePath);
		//首先拉伸或者缩放背景	
		Util::setScaleVisiableSize(back);
		back->setPosition(VisibleRect::center());
		sence->addChild(back,0);
	}
};
#endif TEMPLATECPP_UTIL_h

 






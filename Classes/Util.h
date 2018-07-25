#ifndef TEMPLATECPP_UTIL_h
#define TEMPLATECPP_UTIL_h
#include "math/Vec2.h"
#include "base/CCDirector.h"
#include "json/document.h"
#include <iostream>
#include "Data/data.h"
#include "json/writer.h"
#include "platform/CCFileUtils.h"
#include "stdlib.h"
//���ļ����һЩ�����õĺ���
/**
 * ��ȡ���ŵ�����size��С
 */
inline cocos2d::Vec2 getScaleVisiableSize(cocos2d::Size oSize)
{
	auto size= cocos2d::Director::getInstance()->getVisibleSize();
	float xScale = size.width / oSize.width;
	float yScale = size.height / oSize.height;
	return cocos2d::Vec2(xScale,yScale);
}

/*
 *  sX ָwidthռvis�ı���
 */
inline cocos2d::Vec2 getScaleRatio(float sX,float sY,cocos2d::Size oSize)
{
	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	auto width0 = size.width*sX;
	auto height0= size.height*sY;
	float xScale = width0 / oSize.width;
	float yScale = height0 / oSize.height;
	return cocos2d::Vec2(xScale, yScale);
}
/**
 * ͨ����ȡjson�ļ���ȡ��ǰ�û�ӵ�е�����
 */
 inline std::vector<spriteData> getInitSprite()
{
	rapidjson::Document doc;
	std::vector<spriteData> vector;
//��ȡ����
	ssize_t size = 0;
	unsigned char* content=cocos2d::FileUtils::getInstance()->getFileData("config.json", "r", &size);
	if (content)
	{
		std::string str(reinterpret_cast<const char*>(content), size);
		doc.Parse<0>(str.c_str());
		// std::cout << doc.GetType();
		//ʹ�õ�����
		for(rapidjson::Value::ConstMemberIterator itr=doc.MemberBegin(); itr!=doc.MemberEnd();++itr)
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
 * �޸ĵ�ǰ�û����ڵ�sprite
 */
inline void insertJson(std::vector<spriteData> vector)
{
	rapidjson::Document jsonDoc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator(); //��ȡ������
	jsonDoc.SetObject();
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	//����doc
	for(spriteData s:vector)
	{
		rapidjson::Value value(rapidjson::kObjectType);
		value.AddMember("level", 1, allocator);
		rapidjson::Value valueName(rapidjson::kStringType);
		valueName.SetString(s.className.c_str(),s.className.length(),allocator);	
		jsonDoc.AddMember(valueName,value, allocator);
	}
	jsonDoc.Accept(writer);
	std::cout << buffer.GetString();
	cocos2d::FileUtils::getInstance()->writeStringToFile(buffer.GetString(), "config.json");
}
/**
 * ��ȡ���еľ���plist�ļ���Ϣ
 */
inline std::vector<plistData> getAllSpriteData()
{
	 rapidjson::Document doc;
	 std::vector<plistData> vector;
	 //��ȡ����
	 ssize_t size = 0;
	 unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData("plistJson.json", "r", &size);
	if(content)
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
			auto arrays=itr->value.GetObject()["spriteName"].GetArray();
			for(rapidjson::SizeType index=0;index<arrays.Size();++index)
			{
				// std::cout << arrays[index].GetString() << std::endl;
				d.spriteName[index] = arrays[index].GetString();
			}
			auto arrays2 = itr->value.GetObject()["spriteBack"].GetArray();
			for (rapidjson::SizeType index = 0; index<arrays.Size(); ++index)
			{
				// std::cout << arrays[index].GetString() << std::endl;
				d.spriteBack[index] = arrays[index].GetString();
			}
			vector.push_back(d);
		}
	}
	return vector;
}
//����һ����Χ����� 0---ran-1
inline int getRandom(int ran)
{
	srand(static_cast<unsigned int>(time(0))); // �������������
	return rand() % ran;
}
#endif TEMPLATECPP_UTIL_h

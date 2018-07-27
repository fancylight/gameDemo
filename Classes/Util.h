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
	//-------------------------------�����Сλ�ô���--------------------------------------
	//����漰������λ�õĻ�,��Ҫ��ê������Ϊ0 0

	/*
	*  ��ͼƬ���� x y ����Ϊ��Ļ�� sx ,sy��
	*	@sX ��ʾ����Ҫ����x��������
	*	@sY ��ʾ����Ҫ����y��������
	*	@oSize ��ʾ�����С
	*	@sprite ��ʾҪ�������ŵľ���
	*	@width ��ʾҪ���бȽϵ�width
	*	@height ��ʾҪ���бȽϵ�height
	*/

	static void setScaleRatio(float sX, float sY, cocos2d::Size oSize, cocos2d::Node* sprite, float width = cocos2d::Director::getInstance()->getVisibleSize().width, float height = cocos2d::Director::getInstance()->getVisibleSize().height)
	{
		auto width0 = width * sX;
		auto height0 = height * sY;
		float xScale = width0 / oSize.width;
		float yScale = height0 / oSize.height;
		sprite->setScale(xScale, yScale);
		// RECT_PRINT("�������ź�", cocos2d::Rect(sprite->getPosition().x, sprite->getPosition().y, sprite->getContentSize().width, sprite->getContentSize().height))
	}
	/**
	 * ������ȫ��
	*  @filePath �ļ�����
	*  @scene ����
	*/
	static void setBackGround(std::string filePath, cocos2d::Scene* sence, int zOrder = 0)
	{
		auto back = cocos2d::Sprite::create(filePath);
		//��������������ű���	
		setScaleRatio(1, 1, back->getContentSize(), back);
		back->setPosition(VisibleRect::center());
		sence->addChild(back, 0);
	}
	

	/**
	* ��������,�Ծ������12�����Ų�������λ��
	*	0-11
	*	�ı�ê���λ��
	*/
	static void get12RectByIndex(int index, cocos2d::Node* sprite)
	{
		sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		auto rect = VisibleRect::rect12ByIndex(index);
		
		setNodePostionScale(sprite, rect);
	}
	/**
	 * ���ڵ�����Ϊ�ض�λ��,���ҽ���һ������
	 */
	static void setNodePostionInScreen(cocos2d::Node* sprite, int row, cocos2d::Vec2 vec, int weightScaleToPadding,
		int heightScaleToPadding, int column)
	{
		auto rect = VisibleRect::splitScreenAsRect( row, vec, weightScaleToPadding, heightScaleToPadding, column);
		//����
		// RECT_PRINT("��ȡ������", rect)
		setNodePostionScale(sprite, rect);
	}
	/**
	 * ���ϱߺ�����Ա�����һ����Ծ���
	 */
	static void setNodePostionInRect(cocos2d::Node* sprite, int row, cocos2d::Vec2 vec, int weightScaleToPadding,
		int heightScaleToPadding, int column, cocos2d::Size size)
	{
		auto rect=VisibleRect::splitScreenAsRect(row, vec, weightScaleToPadding, heightScaleToPadding, column,size.width,size.height);
		setNodePostionScale(sprite, rect);
	}
	//��������,������λ��
private:
	static void setNodePostionScale(cocos2d::Node* sprite, cocos2d::Rect rect)
	{
		sprite->setAnchorPoint(cocos2d::Vec2(0,0));
		sprite->setPosition(rect.origin.x, rect.origin.y);
		setScaleRatio(1, 1, sprite->getContentSize(), sprite, rect.size.width, rect.size.height);
	}
public:
	//--------------------------------------io����----------------------------------------
	/**
	* ͨ����ȡjson�ļ���ȡ��ǰ�û�ӵ�е�����
	*/
	static std::vector<spriteData> getInitSprite()
	{
		rapidjson::Document doc;
		std::vector<spriteData> vector;
		//��ȡ����
		ssize_t size = 0;
		unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData("config.json", "r", &size);
		if (content)
		{
			std::string str(reinterpret_cast<const char*>(content), size);
			doc.Parse<0>(str.c_str());
			// std::cout << doc.GetType();
			//ʹ�õ�����
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
	* �޸ĵ�ǰ�û����ڵ�sprite
	*/
	static void insertJson(std::vector<spriteData> vector)
	{
		rapidjson::Document jsonDoc;
		rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator(); //��ȡ������
		jsonDoc.SetObject();
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		//����doc
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
	* ��ȡ���еľ���plist�ļ���Ϣ
	*/
	static std::vector<plistData> getAllSpriteData()
	{
		rapidjson::Document doc;
		std::vector<plistData> vector;
		//��ȡ����
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
	//-------------------------------------------------------------�㷨--------------------------------------------
	//����һ����Χ����� 0---ran-1
	static int getRandom(int ran)
	{
		srand(static_cast<unsigned int>(time(0))); // �������������
		return rand() % ran;
	}
	//�򵥵ĸ��ʻ��� 0-100
	static bool getProbability(int rate)
	{
		if (rate == 0)
			return false;
		srand(static_cast<unsigned int>(time(0))); // �������������
		const int result = (rand() % 100)+1; //1-100
		return 0 < result <= rate;
	}
};
#endif TEMPLATECPP_UTIL_h

 






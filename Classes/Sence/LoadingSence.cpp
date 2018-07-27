#include "LoadingSence.h"
#include "base/CCDirector.h"
#include "Sence/shopSence.h"
#include <iostream>
#include "Sprite/MySprite.h"
#include <Sence/Battle.h>
#include "2d/CCSpriteFrameCache.h"
USING_NS_CC;
std::string LoadingSence::loadSence;
LoadingSence::LoadingSence()
{
}


LoadingSence::~LoadingSence()
{
}

bool LoadingSence::init()
{
	
	return true;
}

void LoadingSence::onEnterTransitionDidFinish()
{
	//������Ƶ
	std::cout << loadSence;
	if (loadSence == "battle")
	{
		loadBattleData();
	}
	else if (loadSence == "shop")
	{
		loadShop();
	}
}
/**
 * ����ս������,��ֻ��һ��demo
 *	1.�����������,���Ժ�Ҫ�ŵ�battleArrayScene���д���
 *	2.�����������,���Ժ�Ҫ����
 *		a.pve ���������ļ�
 *		b.pvp ���ݶԷ��������
 *	3.����ͼƬ
 *		Ӧ�ø��������ļ���
 */
void LoadingSence::loadBattleData()
{
	//������λ
	std::vector<MySprite*> v1;
	std::vector<MySprite*> v2;
	for(int index=0;index<6;index++)
	{
		auto s = MySprite::create();
		s->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Nima1.png"));
		s->setMustNumber(baseValue(1000, 0, 50, 110, 15, 1, 1, 1.5, 1.3, 10, 10), index);
		s->retain();
		s->addHpUi();
		v1.push_back(s);

	}
	for (int index = 0; index<6; index++)
	{
		auto s = MySprite::create();
		s->setMustNumber(baseValue(1000, 0, 50, 110, 15, 1, 1, 1.5, 1.3, 10, 10), index);
		s->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Nima1.png"));
		s->retain();
		s->addHpUi();
		v2.push_back(s);
	}
	BattleSence::initBeforeData(v1, v2);

	Director::getInstance()->pushScene(BattleSence::create());
}
/**
 * �Ƿ���Խ�shop��init���صĽڵ�ŵ��˺����м���
 */
void LoadingSence::loadShop()
{
	
	Director::getInstance()->pushScene(ShopSence::create());
}



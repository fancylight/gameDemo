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
	//播放视频
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
 * 加载战斗场景,这只是一个demo
 *	1.处理玩家上阵,这以后要放到battleArrayScene类中处理
 *	2.处理敌人阵容,这以后要根据
 *		a.pve 根据配置文件
 *		b.pvp 根据对方玩家阵型
 *	3.背景图片
 *		应该根据配置文件来
 */
void LoadingSence::loadBattleData()
{
	//创建单位
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
 * 是否可以将shop中init加载的节点放到此函数中加载
 */
void LoadingSence::loadShop()
{
	
	Director::getInstance()->pushScene(ShopSence::create());
}



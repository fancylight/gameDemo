#include "LoadingSence.h"
#include "base/CCDirector.h"
#include "Sence/shopSence.h"
#include <iostream>

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
	//≤•∑≈ ”∆µ
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

void LoadingSence::loadBattleData()
{
}

void LoadingSence::loadShop()
{
	
	Director::getInstance()->pushScene(ShopSence::create());
}



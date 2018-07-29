#pragma once
#include "platform/CCPlatformMacros.h"
#include "2d/CCScene.h"

class MenuSence:public cocos2d::Scene {

public:
	MenuSence();
	~MenuSence();
	CREATE_FUNC(MenuSence)
   
	
	bool init() override;


	//回调函数
	//准备进入战斗场景
	void battle(Ref* ref);
	//商店
	void shop(Ref* ref);
	void test(Ref* ref);
};


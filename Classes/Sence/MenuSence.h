#pragma once
#include "platform/CCPlatformMacros.h"
#include "2d/CCScene.h"

class MenuSence:public cocos2d::Scene {

public:
	MenuSence();
	~MenuSence();
	CREATE_FUNC(MenuSence)
   
	
	bool init() override;


	//�ص�����
	//׼������ս������
	void battle(Ref* ref);
	//�̵�
	void shop(Ref* ref);
	void test(Ref* ref);
};


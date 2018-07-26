#pragma once
#include "2d/CCScene.h"
#include "MySence.h"

class BattleSence : public MySence
{
public:
	CREATE_FUNC(BattleSence)
	BattleSence();
	~BattleSence();
	/**
	 *  进入战斗场景前先运行加载场景,加载场景中进行创建该场景,当该场景创建完成就调用在加载场景中调用replace()
	 * 1.加载背景
	 * 2.设置上场的位置
	 */
	bool init() override;

	void update(float delta) override;
};


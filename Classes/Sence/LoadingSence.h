#pragma once
#include "Sence/MySence.h"

/**
 * 这个场景充当加载过程,可以加一个动画
 */
class LoadingSence:public MySence
{
	public:
	static std::string loadSence;	//由这个变量决定去加载哪一个场景
	CREATE_FUNC(LoadingSence)
	LoadingSence();
	~LoadingSence();
	//加载自身显示效果
	bool init() override;
	void loadBattleData();
	void loadShop();
	//此函数当场景完全加载后执行,此时我们开始加载数据
	void onEnterTransitionDidFinish() override;
};


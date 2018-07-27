#pragma once
#include "2d/CCScene.h"
#include "MySence.h"
#include <ostream>

class MySprite;
class BattleSence : public MySence
{
public:
	//应该在init函数之前进行处理
	static std::vector<MySprite*> friendSprites; //对于任意玩家来说这几张卡片都位于屏幕下方
	static std::vector<MySprite*> enemySprites;
	static std::vector<MySprite*> Sprites; 
	static std::vector<MySprite*> SpritesScreen;//表示屏幕中的位置
	
	/**
	* 无论是pve还是pvp,其本身排序都是0-5,此函数交给loadScene使用,这个就是进行攻击的牌序
	*	@friendSprites 表示先攻
	*	
	*/
	static void initBeforeData(std::vector<MySprite*>friendSprites, std::vector<MySprite*>enemySprites);
	bool isAnimation=false;
	/**
	 * 也许用的上的属性
	 */
	MySprite* runningSprite;
	MySprite* maxSneerSprite;
	MySprite* minSneerSprite;
	MySprite* maxEnemySneerSprite;
	MySprite* maxFriendSneerSprite;
	MySprite* maxHealthySprite;
	MySprite* lowSneerSprite;

	CREATE_FUNC(BattleSence)
	/**
	 *  进入战斗场景前先运行加载场景,加载场景中进行创建该场景,当该场景创建完成就调用在加载场景中调用replace()
	 * 1.加载背景
	 * 2.设置上场的位置
	 */
	bool init() override;
	void update0();
	void update(float delta) override;
	void test(Ref* f);
	//ui显示以及整理残片数据,并且该函数要做为回调函数使用
	void uiShowAndDataClean();
	//该函数要将三个static清空,对于enemySprites直接回收,对于另外两个清空就行

	void onExit() override;
};



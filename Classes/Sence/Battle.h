#pragma once
#include "2d/CCScene.h"
#include "MySence.h"
#include <ostream>

class MySprite;
class BattleSence : public MySence
{
public:
	friend MySprite;

	//----------------------------属性------------------------------------
	//应该在init函数之前进行处理
	static std::vector<MySprite*> friendSprites; //对于任意玩家来说这几张卡片都位于屏幕下方
	static std::vector<MySprite*> enemySprites;
	static std::vector<MySprite*> Sprites; 
	static std::vector<MySprite*> SpritesScreen;//表示屏幕中的位置
	std::vector<MySprite*> SpritesDamage;	//要用来伤害显示的精灵每次回开始清零
	bool isAnimation = false;
	/**
	* 无论是pve还是pvp,其本身排序都是0-5,此函数交给loadScene使用,这个就是进行攻击的牌序
	*	@friendSprites 表示先攻
	*	@enemySprites  表示后攻
	* 该函数要整理	friendSprites  enemySprites 嘲讽顺序
	* SpritesScreen  按照0-12位置排序
	* Sprites   按照出招顺序排序
	*/
	static void initBeforeData(std::vector<MySprite*>friendSprites, std::vector<MySprite*>enemySprites);
	
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

	//---------------------------回调函数------------------------------
	//ui显示以及整理残片数
	void uiShowAndDataClean();
	void test(Ref* f);
	void update0();
	void onBattleEnd(Ref* ref);
	//-------------------------- override------------------------------
	void update(float delta) override;
	//该函数要将三个static清空,对于enemySprites直接回收,对于另外两个清空就行
	void onExit() override;
	/**
	*  进入战斗场景前先运行加载场景,加载场景中进行创建该场景,当该场景创建完成就调用在加载场景中调用replace()
	* 1.加载背景
	* 2.设置上场的位置
	*/
	bool init() override;
	/**
	 * 该函数用来检查所有的动画是否正确地结束,当动画正确地结束后,才能进入下一回合
	 * BUG:
	 *	此函数用来返回damageNumber值, isAnimation=!cheackAllAimationEnd()
	 *	任然会跳到判断语句中,接着Sprites,每次调用一次内容会少一个
	 * TODO:
	 *  推理:
	 *		1.进入判断语句是因为写错了应该是isAnimation=cheackAllAimationEnd(){return damageNumber==0}
	 *		2,关于我这个Sprites-1,原因在于我insert调用在uiShowAndDataClean才调用,而这是一个回调函数,当且仅当攻击效果执行完毕,才会调用,
	 *		当判断语句出错时,并不能保证前后顺序,因此出现了问题,并不是coco本身的线程问题
	 */
	// bool cheackAllAnimationEnd();
	int damageNumber = 0;  //通过判断此值是否为0来决定是否开始下一回合	
};



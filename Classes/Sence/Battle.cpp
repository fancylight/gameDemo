#include "Battle.h"
#include <iostream>
#include "../Sprite/MySprite.h"
#include "2d/CCActionInstant.h"
#include "2d/CCMenuItem.h"
#include "Util.h"
std::vector<MySprite*> BattleSence::friendSprites;
std::vector<MySprite*> BattleSence::enemySprites; //默认应该按照嘲讽值进行排序
std::vector<MySprite*> BattleSence::Sprites; //这个就是进行攻击的牌序,排序按照位置进行
std::vector<MySprite*> BattleSence::SpritesScreen; //这才是屏幕位置
bool BattleSence::init()
{
	if(SpritesScreen.size()>0)
	{
		for(auto sprite:SpritesScreen)
		{
			Util::get12RectByIndex(sprite->get_postion(), sprite);
			addChild(sprite);
		}
	}
	auto item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(BattleSence::test, this));
	scheduleUpdate();  //该函数决定了是否会调用update
	item->setPosition(VisibleRect::center());
	auto m= Menu::create(item,nullptr);
	m->setPosition(0, 0);
	addChild(m, 1);
	//
	maxEnemySneerSprite = enemySprites[0];
	maxFriendSneerSprite = friendSprites[0];
	Scene::init();

	return true;
}

void BattleSence::update0()
{
	if(!isAnimation)
	{
		runningSprite = Sprites.at(Sprites.size() - 1);
		Sprites.pop_back();
		if(!runningSprite->isDead())
		{
			isAnimation = true;
			// for(auto s:Sprites)
			// {
			// 	std::cout << "位置"<<s->get_postion() << std::endl;
			// 	std::cout << "血量"<<s->get_base().healthy << std::endl;
			// }
			std::cout<<runningSprite->get_postion() << "出手"<<std::endl;
			if (!runningSprite->isFullMona())
			{
				runningSprite->normalAttackAnimation(this, cocos2d::CallFunc::create(CC_CALLBACK_0(BattleSence::uiShowAndDataClean, this)));
			}
			else
			{
				runningSprite->specialAttackAnimation(this, cocos2d::CallFunc::create(CC_CALLBACK_0(BattleSence::uiShowAndDataClean, this)));
			}
		}
			//如果此单位已经死亡,那么就直接放到队尾
		else
		{
			Sprites.insert(Sprites.begin(), runningSprite);
			isAnimation = false;
		}
	}
}

/**
 * 按照顺序处理
 *	1.当调用MySprite动画函数时,将isAnimation置为true
 */
void BattleSence::update(float delta)
{
	update0();
}

/**
 * 测试函数
 */
void BattleSence::test(Ref* f)
{
	update0();
}

/**
 * 修改血量显示  --->这个血量可以作为精灵的子节点
 * 只有当该函数中的动画效果结束了,才能将animation=flase
 */
void BattleSence::uiShowAndDataClean()
{
	for(auto sprite:Sprites)
	{
		float prctance = sprite->get_base().healthy / sprite->get_base().allHealthy;
		//

		sprite->setHp(prctance*100);
		if(sprite->isDead())
		{
			sprite->setVisible(false);//置为看不见
			//此处写的不好,记得改
			if(sprite==maxEnemySneerSprite)
			{
				for(auto s:enemySprites)
				{
					if (!s->isDead())
						maxEnemySneerSprite = s;
				}
			}
			if(sprite==maxFriendSneerSprite)
			{
				for (auto s : friendSprites)
				{
					if (!s->isDead())
						maxFriendSneerSprite = s;
				}
			}
		}
	}
	//将此次攻击的选手置为0位置
	Sprites.insert(Sprites.begin(),runningSprite);
	isAnimation = false;
	// std::cout << "攻击手数量" << Sprites.size();
}

void BattleSence::onExit()
{
	friendSprites.clear();
	Sprites.clear();
	for (MySprite* s : enemySprites)
	{
		// while (s != nullptr)
		// 	s->release();
	}
	enemySprites.clear();
	Scene::onExit();
}

/**
 * 正确地排放攻击顺序,以及其卡片位置
 *  攻击由我方开始
 */
void BattleSence::initBeforeData(std::vector<MySprite*> friendSpriteTemp, std::vector<MySprite*> enemySpriteTemp)
{
	//首先排个序
	std::sort(friendSpriteTemp.begin(), friendSpriteTemp.end(), [](MySprite* s1, MySprite* s2) {return s1->get_postion() < s2->get_postion(); } );//升序排列
	std::sort(enemySpriteTemp.begin(), enemySpriteTemp.end(), [](MySprite* s1, MySprite* s2) {return s1->get_postion() < s2->get_postion(); } );//升序排列
	//确定攻击顺序
	for (int index = 2; index>=0; index--)
	{
		BattleSence::Sprites.push_back(enemySpriteTemp.at(index));
		BattleSence::Sprites.push_back(friendSpriteTemp.at(index));
		
	}	
	for (int index = 5; index>=3; index--)
	{
		BattleSence::Sprites.push_back(enemySpriteTemp.at(index));
		BattleSence::Sprites.push_back(friendSpriteTemp.at(index));
	}
	//改变敌人位置
	for(MySprite* enemy: enemySpriteTemp)
	{
		int pos = enemy->get_postion();
		if (pos >= 0 && pos < 3)
			enemy->set_postion(pos + 9);
		else
			enemy->set_postion(pos + 3);
		BattleSence::enemySprites.push_back(enemy);
		SpritesScreen.push_back(enemy);

	}
	//敌人按照嘲讽值重排,降序排列
	std::sort(BattleSence::enemySprites.begin(), BattleSence::enemySprites.end(), [](MySprite* s1, MySprite* s2) {return s1->get_base().sneer> s2->get_base().sneer; });
	std::sort(BattleSence::enemySprites.begin(), BattleSence::friendSprites.end(), [](MySprite* s1, MySprite* s2) {return s1->get_base().sneer> s2->get_base().sneer; });
	//添加
	for(MySprite* fr : friendSpriteTemp)
	{
		BattleSence::friendSprites.push_back(fr);
		SpritesScreen.push_back(fr);
	}
	std::sort(SpritesScreen.begin(), SpritesScreen.end(), [](MySprite* s1, MySprite* s2) {return s1->get_postion() < s2->get_postion(); });//升序排列
}



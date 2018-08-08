#include "Battle.h"
#include <iostream>
#include "../Sprite/MySprite.h"
#include "2d/CCActionInstant.h"
#include "2d/CCMenuItem.h"
#include "Util.h"
USING_NS_CC;
std::vector<MySprite*> BattleSence::friendSprites;
std::vector<MySprite*> BattleSence::enemySprites; //默认应该按照嘲讽值进行排序
std::vector<MySprite*> BattleSence::Sprites; //这个就是进行攻击的牌序,排序按照位置进行
std::vector<MySprite*> BattleSence::SpritesScreen; //这才是屏幕位置
bool BattleSence::init()
{
	if(!SpritesScreen.empty())
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
	auto item2 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(BattleSence::onBattleEnd, this));
	item2->setPosition(VisibleRect::right());
	auto m= Menu::create(item,item2,nullptr);
	m->setPosition(0, 0);
	addChild(m, 1);
	//
	maxEnemySneerSprite = enemySprites[0];
	maxFriendSneerSprite = friendSprites[0];
	// Scene::init();

	return true;
}

//打印当前出招顺序
std::ostream& operator<<(std::ostream& os, const BattleSence& obj)
{
	os << std::endl;
	for (auto s : obj.Sprites)
	{
		os << s->get_postion()<<"  ";
	}
	return os;
}

void BattleSence::update0()
{
	if (!isAnimation&&damageNumber == 0)
	{
	//打印当前出招顺序
	std::cout << *this<<std::endl;
	SpritesDamage.clear();
	runningSprite = Sprites.at(Sprites.size() - 1);
	Sprites.pop_back();
	std::cout << "位置: " << runningSprite->get_postion()<<"攻击"<<std::endl;
	if (!runningSprite->isDead())
	{
		isAnimation = true;
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
//战斗结束,跳转到结算界面,暂时跳转到菜单
void BattleSence::onBattleEnd(Ref* ref)
{
	Director::getInstance()->popToRootScene();
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
		//血量改变
		sprite->setHp(prctance*100);
		//伤害显示
		if(sprite->isDead())
		{
			sprite->setVisible(false);//置为看不见
			
		}
		//此处写的不好,记得改,每次回合结束前,当前嘲讽对象死亡,改变当前嘲讽最大对象
	}
	if (maxEnemySneerSprite->isDead())
	{
		for (auto s : enemySprites)
		{
			if (!s->isDead())
				maxEnemySneerSprite = s;
		}
	}
	if (maxFriendSneerSprite->isDead())
	{
		for (auto s : friendSprites)
		{
			if (!s->isDead())
				maxFriendSneerSprite = s;
		}
	}
	//伤害显示
	for(auto s: SpritesDamage)
	{
		if(s->damageLbael==nullptr)
		{
			s->addDamageLabel(TTFConfig("fonts/Marker Felt.ttf"));
		}
		damageNumber++;
		if (!s->g_battle)
			s->g_battle = this;
		s->showDamage(Sequence::create(MoveBy::create(0.5, Vec2(0, 5)), CallFunc::create(CC_CALLBACK_0(MySprite::setDamagInvisible, s)), NULL));
	}
	//将此次攻击的选手置为0位置
	Sprites.insert(Sprites.begin(),runningSprite);
	isAnimation = false;  //这个设置应该要延迟到伤害显示动画...复活懂结算动画处理结束再改变
}

/**
 * 本来单个单位的攻击动画和回调函数是一对一的关系通过uiShowAndDataClean 改变一个bool变量就可以
 * 现在伤害显示回调函数是一个多对一,所以此次要检查这些精灵的动画显示
 *	//TODO
 *		现在对c++的了解我不知道如何判断该指针指向的内存是否,析构至少此处如果我主动析构,那么就会导致内存爆炸
 *		所以暂且认为coco本身会在卸载场景时,析构本身子类,虽然看源码~node ()源码只是变量childrenNode,并且调用
 *		其clear()方法,该方法也没有析构,并且我也没有找到removeAllNode()的代码
 *	//
 *	   姑且认为此处coco做了析构,所以我就不做了	
 */
void BattleSence::onExit()
{

	friendSprites.clear();
	Sprites.clear();
	enemySprites.clear();
	SpritesScreen.clear();
	SpritesDamage.clear();
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



//
// Created by fancylight on 2018/7/21.
//

#include "MySprite.h"
#include "Util.h"
#include <Sence/Battle.h>
// void MySprite::normalAttackAnimation(BattleSence* battle, cocos2d::CallFunc* callFunc)
// {
// }
/**
*  结算规则:
*  1.攻击嘲讽值最高的 根据数量来,由高到底
*  ---
*  ui相关
*  1.调整血量
*  2.显示伤害
*/
void MySprite::attackCalc(AttackType type, BattleSence* battle)
{
	int attackNumber = 0;
	int attack = 0;
	if (type == NORMAL)
	{
		attackNumber = base.normalAttackCount;
		attack = base.attack;
	}
	else
	{
		attackNumber = base.specialAttackCount;
		attack = this->base.attack*base.spacialRateValue;
	}
	//1.攻击敌人
	for(int index=0;index<attackNumber;index++)
	{
		// if (!Util::getProbability(base.evadeRate))
		{
			if (Util::getProbability(base.citRate))
				attack = attack * base.citRateValue;
			MySprite* enemy;
			if (get_postion() < 5)
				enemy = battle->maxEnemySneerSprite;
			else
				enemy = battle->maxFriendSneerSprite;
			//攻击,基础模板就从敌人中寻找对象,如果要技能影响,我们后期要改变此处的代码
			enemy->base.healthy -= attack;
			//
			std::cout << "号码" << enemy->get_postion() << "被攻击" << std::endl;
			std::cout << "号码" << enemy->get_postion() << "生命值" << enemy->get_base().healthy << std::endl;
			enemy->spriteChange.changeHealthy = -attack;
			//增加被攻击对象的怒气
			enemy->base.mona += 1;
			//发动攻击特效
			if (type == NORMAL)
				normalAttackEffect(battle, enemy);
			else
			{
				specialAttackEffect(battle, enemy);
			}
			//发动防御特效
			enemy->damagedEffect(battle);
			//3.设置死亡状态
			if (enemy->base.healthy <= 0)
				enemy->setDead(true);
		}
		//2.治疗 默认加血模式为最少生命值治疗
			//1.有其他加血模式	2.该单位是否可以加血
		 if(statusSprite.isCureUnit)
		 {
			 auto sprite = BattleSence::friendSprites[index];
			 if(!sprite->get_status_sprite().isBanHeal)
			 {
				 sprite->base.healthy += attack;
				 if (sprite->base.healthy > sprite->base.allHealthy)
					 sprite->base.healthy = sprite->base.allHealthy;
				 sprite->spriteChange.changeHealthy = attack;
			 }
		 }
		
	}
	
	
}

/*
 * 判断怒气是否大于4
 */
bool MySprite::isFullMona()
{
	return base.mona >= 4;
}

void MySprite::addHpUi()
{
	//测试
	Sprite *bgSprite = Sprite::create("box.png");
	this->addChild(bgSprite, 0, "hpBox");
	Util::setNodePostionInRect(bgSprite, 1, Vec2(0, 0), 0, 2, 15, this->getContentSize());
	Sprite *hpSprite = Sprite::create("hp.png");
	progressTimer = ProgressTimer::create(hpSprite);
	Util::setNodePostionInRect(progressTimer, 1, Vec2(0, 0), 0, 2, 15, this->getContentSize());
	progressTimer->setType(ProgressTimer::Type::BAR);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//从左到右

	//从右到左
	//    progressTimer->setMidpoint(ccp(1, 0.5));
	//    progressTimer->setBarChangeRate(ccp(1, 0));

	//从上到下
	//    progressTimer->setMidpoint(ccp(0.5, 1));
	//    progressTimer->setBarChangeRate(ccp(0, 1));

	//从下到上
	//    progressTimer->setMidpoint(ccp(0.5, 0));
	//    progressTimer->setBarChangeRate(ccp(0, 1));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	progressTimer->setMidpoint(Point(0, 0.5));
	progressTimer->setBarChangeRate(Point(1, 0));

	progressTimer->setPercentage(100);//满值 100%

	this->addChild(progressTimer, 1, "hpProgressTimer");
}

//清除
void MySprite::removeHpUi()
{
	this->removeChild(this->getChildByName("hpBox"), true);
	this->removeChild(this->getChildByName("hpProgressTimer"), true);
}

void MySprite::setHp(float rate)
{
	progressTimer->setPercentage(rate);
}

MySprite* MySprite::createByName(std::string spriteName)
{

	return NULL;
}

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
*  �������:
*  1.��������ֵ��ߵ� ����������,�ɸߵ���
*  ---
*  ui���
*  1.����Ѫ��
*  2.��ʾ�˺�
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
	//1.��������
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
			//����,����ģ��ʹӵ�����Ѱ�Ҷ���,���Ҫ����Ӱ��,���Ǻ���Ҫ�ı�˴��Ĵ���
			enemy->base.healthy -= attack;
			//
			std::cout << "����" << enemy->get_postion() << "������" << std::endl;
			std::cout << "����" << enemy->get_postion() << "����ֵ" << enemy->get_base().healthy << std::endl;
			enemy->spriteChange.changeHealthy = -attack;
			//���ӱ����������ŭ��
			enemy->base.mona += 1;
			//����������Ч
			if (type == NORMAL)
				normalAttackEffect(battle, enemy);
			else
			{
				specialAttackEffect(battle, enemy);
			}
			//����������Ч
			enemy->damagedEffect(battle);
			//3.��������״̬
			if (enemy->base.healthy <= 0)
				enemy->setDead(true);
		}
		//2.���� Ĭ�ϼ�ѪģʽΪ��������ֵ����
			//1.��������Ѫģʽ	2.�õ�λ�Ƿ���Լ�Ѫ
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
 * �ж�ŭ���Ƿ����4
 */
bool MySprite::isFullMona()
{
	return base.mona >= 4;
}

void MySprite::addHpUi()
{
	//����
	Sprite *bgSprite = Sprite::create("box.png");
	this->addChild(bgSprite, 0, "hpBox");
	Util::setNodePostionInRect(bgSprite, 1, Vec2(0, 0), 0, 2, 15, this->getContentSize());
	Sprite *hpSprite = Sprite::create("hp.png");
	progressTimer = ProgressTimer::create(hpSprite);
	Util::setNodePostionInRect(progressTimer, 1, Vec2(0, 0), 0, 2, 15, this->getContentSize());
	progressTimer->setType(ProgressTimer::Type::BAR);

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//������

	//���ҵ���
	//    progressTimer->setMidpoint(ccp(1, 0.5));
	//    progressTimer->setBarChangeRate(ccp(1, 0));

	//���ϵ���
	//    progressTimer->setMidpoint(ccp(0.5, 1));
	//    progressTimer->setBarChangeRate(ccp(0, 1));

	//���µ���
	//    progressTimer->setMidpoint(ccp(0.5, 0));
	//    progressTimer->setBarChangeRate(ccp(0, 1));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	progressTimer->setMidpoint(Point(0, 0.5));
	progressTimer->setBarChangeRate(Point(1, 0));

	progressTimer->setPercentage(100);//��ֵ 100%

	this->addChild(progressTimer, 1, "hpProgressTimer");
}

//���
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

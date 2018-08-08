//
// Created by fancylight on 2018/7/21.
//

#ifndef TEMPLATECPP_MYSPRITE_H
#define TEMPLATECPP_MYSPRITE_H


#include <cocos/2d/CCSprite.h>
#include "Data/data.h"
#include "2d/CCActionInterval.h"
#include <ostream>
#include "2d/CCProgressTimer.h"
#include <iostream>
#include "2d/CCLabel.h"

USING_NS_CC;
/**
 *  所有人物的基类
 *          void attackNormal();  //普通攻击时应该进行的行为
 *          void attackSpecial()
 *   这么一个过程:
 *      a.战斗场景加载
 *      b.每一帧调用场景的update()
 *         1.带有动画效果(顺序创建一个栈,调用结束后出栈,)
 *            按照出招顺序去调用每个精灵的动画函数,并且当该动
 *
 *
 *
 *	如果我要通过自己的方式处理,也就是设置全局的精灵对象,那么该类中要处理的就很多了
 *		1.血条我感觉要自己处理析构
 *
 *
 */
class BattleSence;
enum AttackType
{
	NORMAL,
	SPECIAL
};
struct status //关于本单位的一些状态
{
	status() = default;

	status(bool is_ban_heal, bool is_cure_unit)
		: isBanHeal(is_ban_heal),
		  isCureUnit(is_cure_unit)
	{
	}

	bool isBanHeal;
	bool isCureUnit;
	bool isDead;
	bool isAnimation=false;  //该变量用来检测多对1回调的动画
	friend std::ostream& operator<<(std::ostream& os, const status& obj)
	{
		return os
			<< "isBanHeal: " << obj.isBanHeal
			<< " isCureUnit: " << obj.isCureUnit;
	}
};
struct change
{
	change() = default;

	change(int change_mona, int change_healthy, int change_sneer, int change_attack, int change_defense)
		: changeMona(change_mona),
		  changeHealthy(change_healthy),
		  changeSneer(change_sneer),
		  changeAttack(change_attack),
		  changeDefense(change_defense)
	{
	}

	int changeMona;
	int changeHealthy;
	int changeSneer;
	int changeAttack;
	int changeDefense;

	friend std::ostream& operator<<(std::ostream& os, const change& obj)
	{
		return os
			<< "changeMona: " << obj.changeMona
			<< " changeHealthy: " << obj.changeHealthy
			<< " changeSneer: " << obj.changeSneer
			<< " changeAttack: " << obj.changeAttack
			<< " changeDefense: " << obj.changeDefense;
	}
};
struct baseValue
{
	baseValue() = default;

	baseValue(float healthy, int mona, int sneer, float attack, float defense, int normal_attack_count,
		int special_attack_count, float spacial_rate_value, float cit_rate_value, int cit_rate, int evade_rate)
		: healthy(healthy),
		  mona(mona),
		  sneer(sneer),
		  attack(attack),
		  defense(defense),
		  normalAttackCount(normal_attack_count),
		  specialAttackCount(special_attack_count),
		  spacialRateValue(spacial_rate_value),
		  citRateValue(cit_rate_value),
		  citRate(cit_rate),
		  evadeRate(evade_rate)
	{
		allHealthy = healthy;
	}

	float healthy;
	int mona;
	int sneer;//嘲讽

			  //装备vector,暂时没想好
	float attack;
	float defense;
	int normalAttackCount = 1; //普通攻击数量
	int specialAttackCount = 1; //特殊攻击数量
	float spacialRateValue = 1.3;  //表示特殊攻击/治疗的倍率
	float citRateValue = 1.1;
	//变化量 根据变化量进行战斗ui显示
	int citRate; //暴击率 0-100
	int evadeRate; //闪避率0-100
	float allHealthy;

	friend std::ostream& operator<<(std::ostream& os, const baseValue& obj)
	{
		return os
			<< "healthy: " << obj.healthy
			<< " mona: " << obj.mona
			<< " sneer: " << obj.sneer
			<< " attack: " << obj.attack
			<< " defense: " << obj.defense
			<< " normalAttackCount: " << obj.normalAttackCount
			<< " specialAttackCount: " << obj.specialAttackCount
			<< " spacialRateValue: " << obj.spacialRateValue
			<< " citRateValue: " << obj.citRateValue
			<< " citRate: " << obj.citRate
			<< " evadeRate: " << obj.evadeRate
			<< " allHealthy: " << obj.allHealthy;
	}
};
/**
 *  精灵基类
 */
class MySprite : public cocos2d::Sprite {

public:
    CREATE_FUNC(MySprite)

	MySprite() = default;

	MySprite(const baseValue& base, const change& sprite_change, const status& status_sprite)
		: base(base),
		  spriteChange(sprite_change),
		  statusSprite(status_sprite)
	{
	}
	bool isFullMona();

private:
	//---------------------基础数值--------------------------------------------------------------
	baseValue base;
	//--------------------------------战斗相关--------------------------------------------------
	change spriteChange;
	status statusSprite;
	//----------------------------------图片效果属性 位置------------------------------------
    bool animationEnd = false;// true表示当前精灵仍旧进行动画,那么出招栈不会将其弹出,并且battleSense::update() 函数就直接跳过新的动画场景,也不能进行伤害结算
	spriteData data;
	std::string spriteName; //这个名字是和图像名字相同的
	int postion = -1; //表示场上位置,默认为-1
	bool isField = false; //表示该卡牌是否在上阵中
	std::string effectPicPath;//特效图片位置
	
public:
	//---------------------------------临时加上的------------------------------------------
	BattleSence * g_battle;
	//--------------------------------精灵效果函数-------------------------------------------
	//1.这些效果函数推荐由battle的uiShowAndDataClean函数调用
	//2.添加血条,这两个函数可以交给精灵自己调用,可以交由Battle调用
	//3.这些效果图,可以构造时创建,默认设置为不可见,或者延后创建
	//4.有一个问题是,如果精灵效果动画时间过长,那么此动画也要去影响battle.isAnimation,否则必然不正确
	/**
	 *  显示血条的逻辑:
	 *		精灵上场血条永远显示,当精灵死亡,其本身被设置为不可见,复活时还原所有属性
	 *	怒气显示
	 *		怒气=0时,不显示,怒气>4时显示为 怒气X 数量
	 *	伤害显示
	 *				
	 */
	ProgressTimer * progressTimer;
	void addHpUi();
	void removeHpUi();
	void setHp(float rate);
	//同理我们可以创建精灵的怒气,以及伤害显示
	Label* damageLbael; //伤害显示
	void showDamage(ActionInterval* sqClone);	//该函数要交给battle进行,创建action的copy,使得血量显示同时进行
	void addDamageLabel(TTFConfig&config);	//该函数应该创建的时候调用
	//通过此函数创建不同的精灵对象,由该函数创建出来的精灵数量是有限的,并且不应该被析构,也就是创建出来之后调用器retain()函数
	static MySprite* createByName(std::string spriteName);
	bool isSpriteUiAinamation; //这变量在battle中要遍历检测,当任意精灵次变量为true,都不能进行下一个回合,目前showDamage会影响该变量
	//------------------------------精灵状态判断以及相关设置--------------------------------------------
	bool isDead() const
	{
		return statusSprite.isDead;

	};
	void setDead(bool dead) 
	{
		statusSprite.isDead = dead;
	}
	void setMustNumber(baseValue value, int pos)
	{
		this->base = value;
		assert(0 <= pos && pos < 6);
		this->set_postion(pos);
	};
	//--------------------------------精灵动作函数-------------------------------------------
	//CallFunc::create(CC_CALLBACK_0(ShopSence::setNextBuy,this)) 总之此处要battleSence中一个回调函数来结算伤害显示,伤害显示动画在battle中
	/**
	 *  @callFunc battle场景的ui处理回调
	 *  此函数子类要重写
	 *  此函数子类要重写
	 */
	virtual void normalAttackAnimation(BattleSence* battle, cocos2d::CallFunc* callFunc)
	{
		
		runAction(cocos2d::Sequence::create(MoveBy::create(1, Vec2(2, 3)), MoveBy::create(1, Vec2(-2, -3)), callFunc, NULL));
		//伤害结算
		attackCalc(NORMAL, battle);
	};  
	virtual void specialAttackAnimation(BattleSence* battle, cocos2d::CallFunc* callFunc)
	{
		runAction(cocos2d::Sequence::create(MoveBy::create(1, Vec2(2, 3)), MoveBy::create(1, Vec2(-2, -3)), callFunc, NULL));
		//伤害结算
		attackCalc(SPECIAL, battle);
	};
	virtual void attackCalc(AttackType type, BattleSence* battle) ;	//攻击数据处理
	//一下三个函数子类都应该继承并且有自己的实现方式
	virtual void normalAttackEffect(BattleSence* battle,MySprite* targetSprite){}; //攻击特效
	virtual void specialAttackEffect(BattleSence* battle, MySprite* targetSprite){}; //特击特效
	virtual void damagedEffect(BattleSence* battle){};     //被攻击特效
	//
	//---------------------------------回调函数-----------------------------------------------
	void setDamagInvisible();
	//---------------------------------stream-------------------------------------------------
	friend std::ostream& operator<<(std::ostream& os, const MySprite& obj)
	{
		return os
			<< " base: " << obj.base
			<< " spriteChange: " << obj.spriteChange
			<< " statusSprite: " << obj.statusSprite
			<< " animationEnd: " << obj.animationEnd
			<< " data: " << obj.data
			<< " spriteName: " << obj.spriteName
			<< " postion: " << obj.postion
			<< " isField: " << obj.isField
			<< " effectPicPath: " << obj.effectPicPath;
	}

	//----------------------------------set/get--------------------------------------------
	bool& is_animation_end()
	{
		return animationEnd;
	}

	void set_animation_end(bool animation_end)
	{
		animationEnd = animation_end;
	}

	spriteData& get_data()
	{
		return data;
	}

	void set_data(const spriteData& data)
	{
		this->data = data;
	}

	std::string& get_sprite_name()
	{
		return spriteName;
	}

	void set_sprite_name(const std::string& sprite_name)
	{
		spriteName = sprite_name;
	}

	int& get_postion()
	{
		return postion;
	}

	void set_postion(int postion)
	{
		this->postion = postion;
	}

	bool& is_is_field()
	{
		return isField;
	}

	void set_is_field(bool is_field)
	{
		isField = is_field;
	}

	std::string& get_effect_pic_path()
	{
		return effectPicPath;
	}

	void set_effect_pic_path(const std::string& effect_pic_path)
	{
		effectPicPath = effect_pic_path;
	}

	change& get_sprite_change()
	{
		return spriteChange;
	}

	void set_sprite_change(const change& sprite_change)
	{
		spriteChange = sprite_change;
	}

	status& get_status_sprite()
	{
		return statusSprite;
	}

	void set_status_sprite(const status& status_sprite)
	{
		statusSprite = status_sprite;
	}

	baseValue& get_base()
	{
		return base;
	}

	void set_base(const baseValue& base)
	{
		this->base = base;
	}
};


#endif //TEMPLATECPP_MYSPRITE_H

//
// Created by fancylight on 2018/7/21.
//

#ifndef TEMPLATECPP_MYSPRITE_H
#define TEMPLATECPP_MYSPRITE_H


#include <cocos/2d/CCSprite.h>
#include "Data/data.h"

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
 */
class BattleSence;
class MySprite : public cocos2d::Sprite {

public:
    CREATE_FUNC(MySprite)

	MySprite() = default;
	MySprite(MySprite &&sprite)
	{
	}
private:
    bool animationEnd = false;// true表示当前精灵仍旧进行动画,那么出招栈不会将其弹出,并且battleSense::update() 函数就直接跳过新的动画场景,也不能进行伤害结算
	spriteData data;

public:
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

	//进行一些必要的加载
	bool init() override;
	//通过此函数创建不同的精灵对象,由该函数创建出来的精灵数量是有限的,并且不应该被析构,也就是创建出来之后调用器retain()函数
	static MySprite* createByName(std::string spriteName);
	//当前精灵攻击时要触发的函数
	virtual void attack(BattleSence* sence);
};


#endif //TEMPLATECPP_MYSPRITE_H

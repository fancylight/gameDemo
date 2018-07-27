//
// Created by fancylight on 2018/7/23.
//

#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>
#include <VisibleRect.h>
#include <iostream>
#include "shopSence.h"
#include <cocos/2d/CCNode.h>
#include "../Sprite/MySprite.h"
#include "Util.h"
#include "Data/UserData.h"

USING_NS_CC;

//  1.初次创建精灵并且添加缓存中
bool ShopSence::init() {
	Util::setBackGround("background/shop.jpg", this);
	//初始化精灵
	mySprite = MySprite::create();
	mySprite->setPosition(VisibleRect::center());
    //创建一个菜单
    auto item= MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                     CC_CALLBACK_1(ShopSence::randomCharacter, this));
	Util::setNodePostionInScreen(item, 5, Vec2(0, 0), 3, 5, 10);
	auto menu=Menu::create(item, nullptr);
	menu->setPosition(Vec2::ZERO);
    addChild(menu,1,"randomMenu");
	addChild(mySprite, 1);
	
    return true;
}
/**
 *  动态选择一个精灵,并且添加一个动画,显示在中心
 *      要求:
 *          1.精灵随机选择,新出现的精灵添加到缓存中
 *          2.精灵动画结束前,不能点击抽卡
 * @return
 */
bool ShopSence::randomCharacter(Ref *pSender) {
    if(!animation)
    {
        //进行抽卡以及动画
        std::string name=randonName();
        auto frame=SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        if(frame&&mySprite)
        {
			mySprite->initWithSpriteFrame(frame);
			Util::setScaleRatio(0.25, 0.5, mySprite->getContentSize(), mySprite);
			mySprite->runAction(Sequence::create(ScaleTo::create(1, 0.5), CallFunc::create(CC_CALLBACK_0(ShopSence::setNextBuy, this)), NULL));
        }
        else if(frame==NULL)
        {
			std::cout << name<<"  frame is invalid";
        }
		animation = true;
    }
    return false;
}

/**
 * @return
 */
std::string ShopSence::randonName() {
    //暂时返回一个确定的
	int index = Util::getRandom(UserData::getInstance()->spriteNoBack.size());
	return UserData::getInstance()->spriteNoBack[index];
}
//设置能否进行抽卡
void ShopSence::setNextBuy()
{
	animation = false;
}

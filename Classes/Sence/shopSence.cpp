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
#include "proj.win32/UserData.h"
USING_NS_CC;

//  1.初次创建精灵并且添加缓存中
bool ShopSence::init() {
    auto back = Sprite::create("background/shop.jpg");
    //首先拉伸或者缩放背景
	auto scale= getScaleVisiableSize(back->getContentSize());
	back->setScale(scale.x, scale.y);
    back->setPosition(VisibleRect::center());
	//初始化精灵
	mySprite = MySprite::create();
	mySprite->setPosition(VisibleRect::center());
    //创建一个菜单
    auto item= MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                     CC_CALLBACK_1(ShopSence::randomCharacter, this));
    item->setPosition(VisibleRect::right());
	auto menu=Menu::create(item, nullptr);
	menu->setPosition(Vec2::ZERO);
    addChild(menu,1,"randomMenu");
    addChild(back,0,"back");
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
			auto size = getScaleRatio(0.25, 0.7, mySprite->getContentSize());
			mySprite->setScale(size.x,size.y);
			mySprite->runAction(ScaleTo::create(1, 0.5));
        }
        else
            std::cout<<"frame is invalid";
    }
    return false;
}

/**
 * 具体应该根据某张表来实现
 * @return
 */
std::string ShopSence::randonName() {
    //暂时返回一个确定的
	int index = getRandom(UserData::getInstance()->spriteNoBack.size());
	return UserData::getInstance()->spriteNoBack[index];
}

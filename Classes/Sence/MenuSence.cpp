#include "MenuSence.h"
#include "2d/CCMenuItem.h"
#include "VisibleRect.h"
#include "shopSence.h"
#include "proj.win32/LoadingSence.h"
#include "Util.h"


USING_NS_CC;
MenuSence::MenuSence()
{
}


MenuSence::~MenuSence()
{
}

/**
 * 初始化
 */
bool MenuSence::init()
{
	//创建一个菜单
	auto item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(MenuSence::battle, this));
	

	auto item2 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(MenuSence::shop, this));

	item->setPosition(VisibleRect::top());
	item2->setPosition(VisibleRect::center());
	auto menu = Menu::create(item, item2,nullptr);
	menu->setPosition(Vec2::ZERO);
	//设置背景
	Util::setBackGround("background/menu.jpg", this);
	this->addChild(menu, 1);
	return true;
}

void MenuSence::battle(Ref* ref)
{
	LoadingSence::loadSence = "battle";
	auto ls= LoadingSence::create();
	Director::getInstance()->replaceScene(ls);
}

void MenuSence::shop(Ref* ref)
{
	LoadingSence::loadSence = "shop";
	auto ls = LoadingSence::create();
	Director::getInstance()->replaceScene(ls);
}

#include "MenuSence.h"
#include "2d/CCMenuItem.h"
#include "VisibleRect.h"
#include "shopSence.h"
#include "Util.h"
#include "LoadingSence.h"
#include "proj.win32/TestScene.h"


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
	auto item3= MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(MenuSence::test, this));
	Util::setNodePostionInScreen(item, 5, Vec2(0, 0), 3, 5, 10);
	Util::setNodePostionInScreen(item2, 5, Vec2(1, 0), 3, 5, 10);
	Util::setNodePostionInScreen(item3, 5, Vec2(2, 0), 3, 5, 10);
	auto menu = Menu::create(item,item2,item3,  nullptr);
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
	Director::getInstance()->pushScene(ls);
	
}

void MenuSence::shop(Ref* ref)
{
	LoadingSence::loadSence = "shop";
	auto ls = LoadingSence::create();
	Director::getInstance()->pushScene(ls);
}

void MenuSence::test(Ref* ref)
{
	Director::getInstance()->pushScene(TestScene::create());
}

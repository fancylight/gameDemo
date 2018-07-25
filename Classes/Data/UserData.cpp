#include "UserData.h"
#include "Util.h"

/**
 * 单例模式
 */
//全局变量
UserData* UserData::user = nullptr;
UserData::UserData()
{
	
}


UserData::~UserData()
{
}

UserData* UserData::getInstance()
{
	if (user == NULL)
	{
		user = new UserData();
		user->init();
	}
	return user;
}



//加载数据,此时就缓存下精灵
void UserData::init()
{
	// initSprite();
}

void UserData::initSprite()
{
	auto spriteDatas = Util::getInitSprite();
	for (spriteData s : spriteDatas)
	{
		auto sprite = MySprite::createByName(s.className);
		sprite->set_data(s);
		std::pair<std::string, MySprite*> pair(s.className, sprite);
		my_sprites.insert(pair);
	}
}
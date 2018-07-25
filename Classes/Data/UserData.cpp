#include "UserData.h"
#include "Util.h"

/**
 * ����ģʽ
 */
//ȫ�ֱ���
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



//��������,��ʱ�ͻ����¾���
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
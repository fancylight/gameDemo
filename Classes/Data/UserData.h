#pragma once
#include <vector>
#include "Sprite/MySprite.h"

/**
 * 存放着关于玩家全局数据
 */
class UserData
{
public:
	UserData();
	~UserData();
	//当游戏加载后玩家的精灵就存放在此
	static UserData* user;
	std::map<std::string, MySprite*>  my_sprites;	//表示该玩家拥有的精灵
	std::vector<std::string> spriteNoBack;
	std::vector<std::string> spriteBack;
	static UserData* getInstance();
	int getNoBackSize() { return spriteNoBack.size(); }
	int getBackSize() { return spriteBack.size(); }
private:
	void init();
	void initSprite();
};


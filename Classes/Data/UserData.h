#pragma once
#include <vector>
#include "Sprite/MySprite.h"

/**
 * ����Ź������ȫ������
 */
class UserData
{
public:
	UserData();
	~UserData();
	//����Ϸ���غ���ҵľ���ʹ���ڴ�
	static UserData* user;
	std::map<std::string, MySprite*>  my_sprites;	//��ʾ�����ӵ�еľ���
	std::vector<std::string> spriteNoBack;
	std::vector<std::string> spriteBack;
	static UserData* getInstance();
	int getNoBackSize() { return spriteNoBack.size(); }
	int getBackSize() { return spriteBack.size(); }
private:
	void init();
	void initSprite();
};


#pragma once
#include "2d/CCScene.h"
#include "MySence.h"
#include <ostream>

class MySprite;
class BattleSence : public MySence
{
public:
	//Ӧ����init����֮ǰ���д���
	static std::vector<MySprite*> friendSprites; //�������������˵�⼸�ſ�Ƭ��λ����Ļ�·�
	static std::vector<MySprite*> enemySprites;
	static std::vector<MySprite*> Sprites; 
	static std::vector<MySprite*> SpritesScreen;//��ʾ��Ļ�е�λ��
	
	/**
	* ������pve����pvp,�䱾��������0-5,�˺�������loadSceneʹ��,������ǽ��й���������
	*	@friendSprites ��ʾ�ȹ�
	*	
	*/
	static void initBeforeData(std::vector<MySprite*>friendSprites, std::vector<MySprite*>enemySprites);
	bool isAnimation=false;
	/**
	 * Ҳ���õ��ϵ�����
	 */
	MySprite* runningSprite;
	MySprite* maxSneerSprite;
	MySprite* minSneerSprite;
	MySprite* maxEnemySneerSprite;
	MySprite* maxFriendSneerSprite;
	MySprite* maxHealthySprite;
	MySprite* lowSneerSprite;

	CREATE_FUNC(BattleSence)
	/**
	 *  ����ս������ǰ�����м��س���,���س����н��д����ó���,���ó���������ɾ͵����ڼ��س����е���replace()
	 * 1.���ر���
	 * 2.�����ϳ���λ��
	 */
	bool init() override;
	void update0();
	void update(float delta) override;
	void test(Ref* f);
	//ui��ʾ�Լ������Ƭ����,���Ҹú���Ҫ��Ϊ�ص�����ʹ��
	void uiShowAndDataClean();
	//�ú���Ҫ������static���,����enemySpritesֱ�ӻ���,��������������վ���

	void onExit() override;
};



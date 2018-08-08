#pragma once
#include "2d/CCScene.h"
#include "MySence.h"
#include <ostream>

class MySprite;
class BattleSence : public MySence
{
public:
	friend MySprite;

	//----------------------------����------------------------------------
	//Ӧ����init����֮ǰ���д���
	static std::vector<MySprite*> friendSprites; //�������������˵�⼸�ſ�Ƭ��λ����Ļ�·�
	static std::vector<MySprite*> enemySprites;
	static std::vector<MySprite*> Sprites; 
	static std::vector<MySprite*> SpritesScreen;//��ʾ��Ļ�е�λ��
	std::vector<MySprite*> SpritesDamage;	//Ҫ�����˺���ʾ�ľ���ÿ�λؿ�ʼ����
	bool isAnimation = false;
	/**
	* ������pve����pvp,�䱾��������0-5,�˺�������loadSceneʹ��,������ǽ��й���������
	*	@friendSprites ��ʾ�ȹ�
	*	@enemySprites  ��ʾ��
	* �ú���Ҫ����	friendSprites  enemySprites ����˳��
	* SpritesScreen  ����0-12λ������
	* Sprites   ���ճ���˳������
	*/
	static void initBeforeData(std::vector<MySprite*>friendSprites, std::vector<MySprite*>enemySprites);
	
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

	//---------------------------�ص�����------------------------------
	//ui��ʾ�Լ������Ƭ��
	void uiShowAndDataClean();
	void test(Ref* f);
	void update0();
	void onBattleEnd(Ref* ref);
	//-------------------------- override------------------------------
	void update(float delta) override;
	//�ú���Ҫ������static���,����enemySpritesֱ�ӻ���,��������������վ���
	void onExit() override;
	/**
	*  ����ս������ǰ�����м��س���,���س����н��д����ó���,���ó���������ɾ͵����ڼ��س����е���replace()
	* 1.���ر���
	* 2.�����ϳ���λ��
	*/
	bool init() override;
	/**
	 * �ú�������������еĶ����Ƿ���ȷ�ؽ���,��������ȷ�ؽ�����,���ܽ�����һ�غ�
	 * BUG:
	 *	�˺�����������damageNumberֵ, isAnimation=!cheackAllAimationEnd()
	 *	��Ȼ�������ж������,����Sprites,ÿ�ε���һ�����ݻ���һ��
	 * TODO:
	 *  ����:
	 *		1.�����ж��������Ϊд����Ӧ����isAnimation=cheackAllAimationEnd(){return damageNumber==0}
	 *		2,���������Sprites-1,ԭ��������insert������uiShowAndDataClean�ŵ���,������һ���ص�����,���ҽ�������Ч��ִ�����,�Ż����,
	 *		���ж�������ʱ,�����ܱ�֤ǰ��˳��,��˳���������,������coco������߳�����
	 */
	// bool cheackAllAnimationEnd();
	int damageNumber = 0;  //ͨ���жϴ�ֵ�Ƿ�Ϊ0�������Ƿ�ʼ��һ�غ�	
};



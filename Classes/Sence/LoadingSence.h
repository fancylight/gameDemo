#pragma once
#include "Sence/MySence.h"

/**
 * ��������䵱���ع���,���Լ�һ������
 */
class LoadingSence:public MySence
{
	public:
	static std::string loadSence;	//�������������ȥ������һ������
	CREATE_FUNC(LoadingSence)
	LoadingSence();
	~LoadingSence();
	//����������ʾЧ��
	bool init() override;
	void loadBattleData();
	void loadShop();
	//�˺�����������ȫ���غ�ִ��,��ʱ���ǿ�ʼ��������
	void onEnterTransitionDidFinish() override;
};


#pragma once
#include "2d/CCScene.h"
#include "MySence.h"

class BattleSence : public MySence
{
public:
	CREATE_FUNC(BattleSence)
	BattleSence();
	~BattleSence();
	/**
	 *  ����ս������ǰ�����м��س���,���س����н��д����ó���,���ó���������ɾ͵����ڼ��س����е���replace()
	 * 1.���ر���
	 * 2.�����ϳ���λ��
	 * 3.�����
	 */
	bool init() override;
};


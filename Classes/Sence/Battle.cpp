#include "Battle.h"
#include <iostream>
#include "../Sprite/MySprite.h"
#include "2d/CCActionInstant.h"
#include "2d/CCMenuItem.h"
#include "Util.h"
USING_NS_CC;
std::vector<MySprite*> BattleSence::friendSprites;
std::vector<MySprite*> BattleSence::enemySprites; //Ĭ��Ӧ�ð��ճ���ֵ��������
std::vector<MySprite*> BattleSence::Sprites; //������ǽ��й���������,������λ�ý���
std::vector<MySprite*> BattleSence::SpritesScreen; //�������Ļλ��
bool BattleSence::init()
{
	if(!SpritesScreen.empty())
	{
		for(auto sprite:SpritesScreen)
		{
			Util::get12RectByIndex(sprite->get_postion(), sprite);
			addChild(sprite);
		}
	}
	auto item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(BattleSence::test, this));
	scheduleUpdate();  //�ú����������Ƿ�����update
	item->setPosition(VisibleRect::center());
	auto item2 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(BattleSence::onBattleEnd, this));
	item2->setPosition(VisibleRect::right());
	auto m= Menu::create(item,item2,nullptr);
	m->setPosition(0, 0);
	addChild(m, 1);
	//
	maxEnemySneerSprite = enemySprites[0];
	maxFriendSneerSprite = friendSprites[0];
	// Scene::init();

	return true;
}

//��ӡ��ǰ����˳��
std::ostream& operator<<(std::ostream& os, const BattleSence& obj)
{
	os << std::endl;
	for (auto s : obj.Sprites)
	{
		os << s->get_postion()<<"  ";
	}
	return os;
}

void BattleSence::update0()
{
	if (!isAnimation&&damageNumber == 0)
	{
	//��ӡ��ǰ����˳��
	std::cout << *this<<std::endl;
	SpritesDamage.clear();
	runningSprite = Sprites.at(Sprites.size() - 1);
	Sprites.pop_back();
	std::cout << "λ��: " << runningSprite->get_postion()<<"����"<<std::endl;
	if (!runningSprite->isDead())
	{
		isAnimation = true;
		if (!runningSprite->isFullMona())
		{
			runningSprite->normalAttackAnimation(this, cocos2d::CallFunc::create(CC_CALLBACK_0(BattleSence::uiShowAndDataClean, this)));
		}
		else
		{
			runningSprite->specialAttackAnimation(this, cocos2d::CallFunc::create(CC_CALLBACK_0(BattleSence::uiShowAndDataClean, this)));
		}
	}
	//����˵�λ�Ѿ�����,��ô��ֱ�ӷŵ���β
	else
	{
		Sprites.insert(Sprites.begin(), runningSprite);
		isAnimation = false;
	}
	}
}
//ս������,��ת���������,��ʱ��ת���˵�
void BattleSence::onBattleEnd(Ref* ref)
{
	Director::getInstance()->popToRootScene();
}

/**
 * ����˳����
 *	1.������MySprite��������ʱ,��isAnimation��Ϊtrue
 */
void BattleSence::update(float delta)
{
	update0();
}

/**
 * ���Ժ���
 */
void BattleSence::test(Ref* f)
{
	update0();
}

/**
 * �޸�Ѫ����ʾ  --->���Ѫ��������Ϊ������ӽڵ�
 * ֻ�е��ú����еĶ���Ч��������,���ܽ�animation=flase
 */
void BattleSence::uiShowAndDataClean()
{
	for(auto sprite:Sprites)
	{
		float prctance = sprite->get_base().healthy / sprite->get_base().allHealthy;
		//Ѫ���ı�
		sprite->setHp(prctance*100);
		//�˺���ʾ
		if(sprite->isDead())
		{
			sprite->setVisible(false);//��Ϊ������
			
		}
		//�˴�д�Ĳ���,�ǵø�,ÿ�λغϽ���ǰ,��ǰ�����������,�ı䵱ǰ����������
	}
	if (maxEnemySneerSprite->isDead())
	{
		for (auto s : enemySprites)
		{
			if (!s->isDead())
				maxEnemySneerSprite = s;
		}
	}
	if (maxFriendSneerSprite->isDead())
	{
		for (auto s : friendSprites)
		{
			if (!s->isDead())
				maxFriendSneerSprite = s;
		}
	}
	//�˺���ʾ
	for(auto s: SpritesDamage)
	{
		if(s->damageLbael==nullptr)
		{
			s->addDamageLabel(TTFConfig("fonts/Marker Felt.ttf"));
		}
		damageNumber++;
		if (!s->g_battle)
			s->g_battle = this;
		s->showDamage(Sequence::create(MoveBy::create(0.5, Vec2(0, 5)), CallFunc::create(CC_CALLBACK_0(MySprite::setDamagInvisible, s)), NULL));
	}
	//���˴ι�����ѡ����Ϊ0λ��
	Sprites.insert(Sprites.begin(),runningSprite);
	isAnimation = false;  //�������Ӧ��Ҫ�ӳٵ��˺���ʾ����...������㶯����������ٸı�
}

/**
 * ����������λ�Ĺ��������ͻص�������һ��һ�Ĺ�ϵͨ��uiShowAndDataClean �ı�һ��bool�����Ϳ���
 * �����˺���ʾ�ص�������һ�����һ,���Դ˴�Ҫ�����Щ����Ķ�����ʾ
 *	//TODO
 *		���ڶ�c++���˽��Ҳ�֪������жϸ�ָ��ָ����ڴ��Ƿ�,�������ٴ˴��������������,��ô�ͻᵼ���ڴ汬ը
 *		����������Ϊcoco�������ж�س���ʱ,������������,��Ȼ��Դ��~node ()Դ��ֻ�Ǳ���childrenNode,���ҵ���
 *		��clear()����,�÷���Ҳû������,������Ҳû���ҵ�removeAllNode()�Ĵ���
 *	//
 *	   ������Ϊ�˴�coco��������,�����ҾͲ�����	
 */
void BattleSence::onExit()
{

	friendSprites.clear();
	Sprites.clear();
	enemySprites.clear();
	SpritesScreen.clear();
	SpritesDamage.clear();
}

/**
 * ��ȷ���ŷŹ���˳��,�Լ��俨Ƭλ��
 *  �������ҷ���ʼ
 */
void BattleSence::initBeforeData(std::vector<MySprite*> friendSpriteTemp, std::vector<MySprite*> enemySpriteTemp)
{
	//�����Ÿ���
	std::sort(friendSpriteTemp.begin(), friendSpriteTemp.end(), [](MySprite* s1, MySprite* s2) {return s1->get_postion() < s2->get_postion(); } );//��������
	std::sort(enemySpriteTemp.begin(), enemySpriteTemp.end(), [](MySprite* s1, MySprite* s2) {return s1->get_postion() < s2->get_postion(); } );//��������
	//ȷ������˳��
	for (int index = 2; index>=0; index--)
	{
		BattleSence::Sprites.push_back(enemySpriteTemp.at(index));
		BattleSence::Sprites.push_back(friendSpriteTemp.at(index));
		
	}	
	for (int index = 5; index>=3; index--)
	{
		BattleSence::Sprites.push_back(enemySpriteTemp.at(index));
		BattleSence::Sprites.push_back(friendSpriteTemp.at(index));
	}
	//�ı����λ��
	for(MySprite* enemy: enemySpriteTemp)
	{
		int pos = enemy->get_postion();
		if (pos >= 0 && pos < 3)
			enemy->set_postion(pos + 9);
		else
			enemy->set_postion(pos + 3);
		BattleSence::enemySprites.push_back(enemy);
		SpritesScreen.push_back(enemy);

	}
	//���˰��ճ���ֵ����,��������
	std::sort(BattleSence::enemySprites.begin(), BattleSence::enemySprites.end(), [](MySprite* s1, MySprite* s2) {return s1->get_base().sneer> s2->get_base().sneer; });
	std::sort(BattleSence::enemySprites.begin(), BattleSence::friendSprites.end(), [](MySprite* s1, MySprite* s2) {return s1->get_base().sneer> s2->get_base().sneer; });
	//���
	for(MySprite* fr : friendSpriteTemp)
	{
		BattleSence::friendSprites.push_back(fr);
		SpritesScreen.push_back(fr);
	}
	std::sort(SpritesScreen.begin(), SpritesScreen.end(), [](MySprite* s1, MySprite* s2) {return s1->get_postion() < s2->get_postion(); });//��������
}



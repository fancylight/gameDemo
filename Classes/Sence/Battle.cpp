#include "Battle.h"
#include <iostream>

BattleSence::BattleSence()
{
}

BattleSence::~BattleSence()
{
}

bool BattleSence::init()
{
	return true;
}

void BattleSence::update(float delta)
{
	std::cout << delta;
}

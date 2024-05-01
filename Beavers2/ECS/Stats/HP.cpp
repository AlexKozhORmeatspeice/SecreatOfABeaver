#include "HP.h"

HP::HP()
{
	maxHP = 100;
}
HP::HP(unsigned int nowMaxHP)
{
	maxHP = nowMaxHP;
}

void HP::init()
{
	nowHP = maxHP;
}

void HP::UseHP(unsigned int useHP)
{
	if (nowHP - useHP < 0)
	{
		nowHP = 0;
	}
	else
	{
		nowHP -= useHP;
	}
}

void HP::Recover()
{
	nowHP = maxHP;
}

bool HP::isDead()
{
	return (nowHP == 0);
}
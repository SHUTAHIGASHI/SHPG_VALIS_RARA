#include "EnemyChino.h"

EnemyChino::EnemyChino(VECTOR pos):
	EnemyBase("chino", pos)
{
}

EnemyChino::~EnemyChino()
{
}

void EnemyChino::Update()
{
	EnemyBase::Update();
}

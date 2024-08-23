#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(VECTOR pos, float radius)
{
	// ‰Šú‰»
	m_status.pos = pos;
	m_status.radius = radius;
}

MeleeAttack::~MeleeAttack()
{
}

void MeleeAttack::Draw()
{
	// ƒƒbƒVƒ…•`‰æ
	DrawSphere3D(m_status.pos, m_status.radius, 8, 0xffffff, 0xffffff, false);
}

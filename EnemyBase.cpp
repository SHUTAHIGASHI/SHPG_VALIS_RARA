#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"

namespace
{

}

EnemyBase::EnemyBase(VECTOR pos)
{
	// Šg‘å—¦İ’è
	m_status.scale = Game::kBaseScale;
	// À•Wİ’è
	m_status.pos = pos;
	// ‰æ‘œİ’è
	m_status.hImg = Load::GetInstance().GetHandle("enemy");
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
	// 3D•`‰æ
	//DrawSphere3D(m_status.pos, 10.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	// ‰æ‘œ•`‰æ
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit()
{
	// “–‚½‚Á‚½‚Ìˆ—
	m_status.isEnabled = false;
}

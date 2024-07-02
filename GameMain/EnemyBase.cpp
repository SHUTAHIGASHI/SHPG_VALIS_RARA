#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"

EnemyBase::EnemyBase(std::string typeName, VECTOR pos):
	ObjectBase()
{
	// ”¼Œaİ’è
	m_status.radius = kRadius;
	// ˆÚ“®‘¬“xİ’è
	m_status.moveSpeed = kSpeed;
	// Šg‘å—¦İ’è
	m_status.scale = Game::kBaseScale;
	// À•Wİ’è
	m_status.pos = pos;
	// ‰æ‘œİ’è
	m_status.hImg = Load::GetInstance().GetHandle(typeName);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	// ˆÚ“®
	m_status.dir = VGet(0.0f, 0.0f, -1.0f);
	m_status.pos = VAdd(m_status.pos, VScale(m_status.dir, m_status.moveSpeed));

	// ‰æ–ÊŠO‚Éo‚½‚ç
	if (m_status.pos.z < kStageLimitZ)
	{
		m_status.isEnabled = false;
	}
}

void EnemyBase::Draw()
{
	// ‰æ‘œ•`‰æ
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit()
{
	// “–‚½‚Á‚½‚Ìˆ—
	m_status.isEnabled = false;
}

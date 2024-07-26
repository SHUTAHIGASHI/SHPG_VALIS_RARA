#include "EnemyNeffy.h"

EnemyNeffy::EnemyNeffy(VECTOR pos):
	EnemyBase("neffy", pos)
{
}

EnemyNeffy::~EnemyNeffy()
{
}

void EnemyNeffy::Update()
{
	// ˆÚ“®
	m_status.dir = VGet(0.0f, 0.0f, -1.0f);
	m_status.pos = VAdd(m_status.pos, VScale(m_status.dir, m_status.moveSpeed));

	// ‰æ–ÊŠO‚Éo‚½‚ç
	if (m_status.pos.z < kStageLimitZ)
	{
		m_status.isEnabled = false;
		this->OnDelete();
	}
}

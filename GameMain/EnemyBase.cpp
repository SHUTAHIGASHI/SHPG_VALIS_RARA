#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"
#include "UiManager.h"

namespace
{
	// Šî€‘Ì—Í
	const int kBaseHp = 3;
}

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
	// ‘Ì—Íİ’è
	m_status.hp = kBaseHp;

	// UI‚É“G‚Ì‘Ì—Í‚ğ“o˜^
	UiManager::GetInstance().AddUI(this);
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
	// ‘Ì—Í‚ğŒ¸‚ç‚·
	m_status.hp--;
	if(m_status.hp <= 0)
	{
		// ‘Ì—Í‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
		OnDead();
	}
	else
	{
		// ƒ_ƒ[ƒW‰¹Ä¶
		SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
	}
}

void EnemyBase::OnHitPlayer()
{
	// todo ƒvƒŒƒCƒ„[‚É“–‚½‚Á‚½‚Ìˆ—
}

void EnemyBase::OnDelete()
{
	// UI‚©‚ç“G‚Ì‘Ì—Í‚ğíœ
	UiManager::GetInstance().DeleteUI(this);
}

void EnemyBase::OnDead()
{
	// ‘Ì—Í‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
	m_status.isEnabled = false;
	// €–S‰¹Ä¶
	SoundManager::GetInstance().PlaySE(SoundType::enemyDeath);
	// íœˆ—
	this->OnDelete();
}

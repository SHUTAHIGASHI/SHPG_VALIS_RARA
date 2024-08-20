#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"
#include "UiManager.h"
#include "MeleeAttack.h"

namespace
{
	// Šî€‘Ì—Í
	const int kBaseHp = 30;
}

EnemyBase::EnemyBase(std::string typeName, VECTOR pos):
	ObjectBase(),
	m_attackFrame(0)
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
	m_status.hImg = Load::GetInstance().GetImageHandle(typeName);
	// ‘Ì—Íİ’è
	m_status.hp = kBaseHp;

	// UI‚É“G‚Ì‘Ì—Í‚ğ“o˜^
	UiManager::GetInstance().AddUIBar(this);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Draw()
{
	// ‰æ‘œ•`‰æ
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit(int damage)
{	
	// ‘Ì—Í‚ğŒ¸‚ç‚·
	m_status.hp -= damage;
	if(m_status.hp <= 0)
	{
		m_status.hp = 0;
		// ‘Ì—Í‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
		OnDead();
	}
	else
	{
		// ƒ_ƒ[ƒW‰¹Ä¶
		SoundManager::GetInstance().Play3DSound(SoundType::enemyDamage, m_status.pos);
	}
}

void EnemyBase::OnHitPlayer()
{
	// todo ƒvƒŒƒCƒ„[‚É“–‚½‚Á‚½‚Ìˆ—
}

bool EnemyBase::CheckAttackCollision(ObjectBase* obj)
{
	if (m_pAttack != nullptr)
	{
		// UŒ‚”»’è
		return m_pAttack->CheckCollision(obj);
	}
	else
	{
		return false;
	}
}

void EnemyBase::OnDelete()
{
	// UI‚©‚ç“G‚Ì‘Ì—Í‚ğíœ
	UiManager::GetInstance().DeleteUIBar(this);
}

void EnemyBase::OnDead()
{
	// ‘Ì—Í‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
	m_status.isEnabled = false;
	// €–S‰¹Ä¶
	SoundManager::GetInstance().Play3DSound(SoundType::enemyDeath, m_status.pos);
	// íœˆ—
	this->OnDelete();
}

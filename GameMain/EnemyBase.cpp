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
	m_frameCount(0),
	m_drawFrame(0),
	m_attackFrame(0),
	m_pAttack(nullptr)
{
	// ”¼Œaİ’è
	m_status.radius = kRadius;
	// ˆÚ“®‘¬“xİ’è
	m_status.moveSpeed = kSpeed;
	// Šg‘å—¦İ’è
	m_status.scale = Game::kBaseScale;
	// À•Wİ’è
	m_status.pos = pos;
	// ‘Ì—Íİ’è
	m_status.hp = kBaseHp;

	// ‰æ‘œ“Ç‚İ‚İ
	m_hImgs.push_back(Load::GetInstance().GetImageHandle(typeName));
	m_hImgs.push_back(Load::GetInstance().GetImageHandle(typeName += "2"));

	// UI‚É“G‚Ì‘Ì—Í‚ğ“o˜^
	UiManager::GetInstance().AddEnemyHpBar(this);
}

EnemyBase::~EnemyBase()
{
	// ‰æ‘œƒnƒ“ƒhƒ‹‚Ì‰ğ•ú
	for (auto& hImg : m_hImgs)
	{
		DeleteGraph(hImg);
	}
	// UŒ‚ƒNƒ‰ƒX‚Ì‰ğ•ú
	if (m_pAttack != nullptr)
	{
		delete m_pAttack;
		m_pAttack = nullptr;
	}
}

void EnemyBase::Draw()
{
	// ‰æ‘œ•`‰æ
	if (m_drawFrame % 2 == 0)
	{
		DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_hImgs.front(), true);
	}
	else
	{
		DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_hImgs.back(), true);
	}

	// •`‰æƒtƒŒ[ƒ€‚ği‚ß‚é
	if (m_frameCount % 10 == 0)
	{
		m_drawFrame++;
	}
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
		SoundManager::GetInstance().Play3DSound(SoundType::enemyDamage, this);
	}
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
	UiManager::GetInstance().DeleteEnemyHpBar(this);
}

void EnemyBase::OnDead()
{
	// ‘Ì—Í‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
	m_status.isEnabled = false;
	// €–S‰¹Ä¶
	SoundManager::GetInstance().Play3DSound(SoundType::enemyDeath, this);
	// íœˆ—
	this->OnDelete();
}

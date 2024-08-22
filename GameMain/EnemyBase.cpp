#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"
#include "UiManager.h"
#include "MeleeAttack.h"

namespace
{
	// 基準体力
	const int kBaseHp = 30;
}

EnemyBase::EnemyBase(std::string typeName, VECTOR pos):
	ObjectBase(),
	m_attackFrame(0)
{
	// 半径設定
	m_status.radius = kRadius;
	// 移動速度設定
	m_status.moveSpeed = kSpeed;
	// 拡大率設定
	m_status.scale = Game::kBaseScale;
	// 座標設定
	m_status.pos = pos;
	// 画像設定
	m_status.hImg = Load::GetInstance().GetImageHandle(typeName);
	// 体力設定
	m_status.hp = kBaseHp;

	// UIに敵の体力を登録
	UiManager::GetInstance().AddEnemyHpBar(this);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Draw()
{
	// 画像描画
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit(int damage)
{	
	// 体力を減らす
	m_status.hp -= damage;
	if(m_status.hp <= 0)
	{
		m_status.hp = 0;
		// 体力が0以下になったら
		OnDead();
	}
	else
	{
		// ダメージ音再生
		SoundManager::GetInstance().Play3DSound(SoundType::enemyDamage, m_status.pos);
	}
}

bool EnemyBase::CheckAttackCollision(ObjectBase* obj)
{
	if (m_pAttack != nullptr)
	{
		// 攻撃判定
		return m_pAttack->CheckCollision(obj);
	}
	else
	{
		return false;
	}
}

void EnemyBase::OnDelete()
{
	// UIから敵の体力を削除
	UiManager::GetInstance().DeleteEnemyHpBar(this);
}

void EnemyBase::OnDead()
{
	// 体力が0以下になったら
	m_status.isEnabled = false;
	// 死亡音再生
	SoundManager::GetInstance().Play3DSound(SoundType::enemyDeath, m_status.pos);
	// 削除処理
	this->OnDelete();
}

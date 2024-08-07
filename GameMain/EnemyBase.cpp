#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"
#include "UiManager.h"

namespace
{
	// 基準体力
	const int kBaseHp = 30;
}

EnemyBase::EnemyBase(std::string typeName, VECTOR pos):
	ObjectBase()
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
	m_status.hImg = Load::GetInstance().GetHandle(typeName);
	// 体力設定
	m_status.hp = kBaseHp;

	// UIに敵の体力を登録
	UiManager::GetInstance().AddUI(this);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	// 移動
	m_status.dir = VGet(0.0f, 0.0f, -1.0f);
	m_status.pos = VAdd(m_status.pos, VScale(m_status.dir, m_status.moveSpeed));

	// 画面外に出たら
	if (m_status.pos.z < kStageLimitZ)
	{
		m_status.isEnabled = false;
	}
}

void EnemyBase::Draw()
{
	// 画像描画
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
	// 球描画
	DrawSphere3D(m_status.pos, m_status.radius, 32, 0xffffff, 0xffffff, false);
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
		SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
	}
}

void EnemyBase::OnHitPlayer()
{
	// todo プレイヤーに当たった時の処理
}

void EnemyBase::OnDelete()
{
	// UIから敵の体力を削除
	UiManager::GetInstance().DeleteUI(this);
}

void EnemyBase::OnDead()
{
	// 体力が0以下になったら
	m_status.isEnabled = false;
	// 死亡音再生
	SoundManager::GetInstance().PlaySE(SoundType::enemyDeath);
	// 削除処理
	this->OnDelete();
}

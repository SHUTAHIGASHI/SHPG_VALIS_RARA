#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"

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
}

void EnemyBase::OnHit()
{	
	// 当たった時の処理
	m_status.isEnabled = false;
	// ダメージ音再生
	SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
}

void EnemyBase::OnHitPlayer()
{
	// 当たった時の処理
	m_status.isEnabled = false;
	// ダメージ音再生
	SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
}

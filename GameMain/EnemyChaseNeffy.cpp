#include "EnemyChaseNeffy.h"
#include "ObjectBase.h"

EnemyChaseNeffy::EnemyChaseNeffy(ObjectBase* target, VECTOR pos):
	EnemyBase("chino", pos)
{
	m_pTarget = target;
}

EnemyChaseNeffy::~EnemyChaseNeffy()
{
	m_pTarget = nullptr;
}

void EnemyChaseNeffy::Update()
{
	// ターゲットの座標取得
	auto targetPos = VGet(m_pTarget->GetPos().x, 0.0f, m_pTarget->GetPos().z);
	// プレイヤーの座標までのベクトルを求める
	m_status.dir = VSub(targetPos, m_status.pos);
	// 正規化
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// 移動速度指定
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	// 移動
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}

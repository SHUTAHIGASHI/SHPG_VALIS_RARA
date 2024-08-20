#include "EnemyNeffy.h"
#include "ObjectBase.h"
#include "SoundManager.h"
#include "MeleeAttack.h"

namespace
{
	// 攻撃判定の半径
	constexpr float kAttackRadius = 64.0f;
	// 攻撃フレーム数
	constexpr int kAttackFrame = 60;
}

EnemyNeffy::EnemyNeffy(ObjectBase* target, VECTOR pos) :
	EnemyBase("neffy", pos),
	m_updateFunc(&EnemyNeffy::NormalUpdate)
{
	m_pTarget = target;
}

EnemyNeffy::~EnemyNeffy()
{
	// ターゲットの解放
	m_pTarget = nullptr;
}

void EnemyNeffy::Update()
{
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)();

	// エネミーサウンド再生
	if (!SoundManager::GetInstance().IsPlaying(SoundType::enemyBirdVoice))
	{
		//SoundManager::GetInstance().PlaySE(SoundType::enemyBirdVoice);
		SoundManager::GetInstance().Play3DSound(SoundType::enemyBirdVoice, m_status.pos);
	}
}

void EnemyNeffy::NormalUpdate()
{
	// ターゲットの座標取得
	auto targetPos = VGet(m_pTarget->GetPos().x, m_status.pos.y, m_pTarget->GetPos().z);
	// プレイヤーの座標までのベクトルを求める
	m_status.dir = VSub(targetPos, m_status.pos);
	// プレイヤーとの距離が一定以下なら攻撃状態に遷移
	if (VSize(m_status.dir) < kAttackRadius)
	{
		// 攻撃フレーム数を設定
		m_attackFrame = kAttackFrame;
		// 攻撃状態に遷移
		m_updateFunc = &EnemyNeffy::AttackUpdate;
	}

	// 正規化
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// 移動速度指定
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	// 移動
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}

void EnemyNeffy::AttackUpdate()
{
	// ターゲットの座標取得
	auto targetPos = VGet(m_pTarget->GetPos().x, m_status.pos.y, m_pTarget->GetPos().z);
	// プレイヤーの座標までのベクトルを求める
	m_status.dir = VSub(targetPos, m_status.pos);
	// 正規化
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// 移動速度指定
	m_status.dir = VScale(m_status.dir, kAttackRadius);
	// 攻撃判定の座標を設定
	VECTOR attackPos = VAdd(m_status.pos, m_status.dir);
	// 攻撃判定の生成
	m_pAttack = new MeleeAttack(attackPos, kAttackRadius);

	// 攻撃フレーム数が0以下なら通常状態に遷移
	if (m_attackFrame <= 0)
	{
		// 攻撃判定の解放
		delete m_pAttack;
		m_pAttack = nullptr;
		// 通常状態に遷移
		m_updateFunc = &EnemyNeffy::NormalUpdate;
	}
	else
	{
		// 攻撃フレーム数を減らす
		m_attackFrame--;
	}
}

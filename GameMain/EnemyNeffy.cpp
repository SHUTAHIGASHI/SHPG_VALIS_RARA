#include "EnemyNeffy.h"
#include "ObjectBase.h"
#include "SoundManager.h"
#include "MeleeAttack.h"
#include "Stage.h"

namespace
{
	// 攻撃判定の半径
	constexpr float kAttackRadius = 64.0f;
	// 攻撃フレーム数
	constexpr int kAttackFrame = 60;
}

EnemyNeffy::EnemyNeffy(ObjectBase* target, VECTOR pos, class Stage* stage) :
	EnemyBase("neffy", pos),
	m_updateFunc(&EnemyNeffy::NormalUpdate),
	m_pStage(stage)
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
	// 毎フレームカウント
	m_frameCount++;

	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)();

	// エネミーサウンド再生
	if (!SoundManager::GetInstance().IsPlaying3DSound(this))
	{
		SoundManager::GetInstance().Play3DSound(SoundType::enemyVoice, this);
	}
}

void EnemyNeffy::Draw()
{
	// 画像描画
	if (m_drawFrame % 2 == 0)
	{
		DrawBillboard3D(m_status.pos, 0.5f, 0.8f, m_status.scale, 0.0f, m_hImgs.front(), true);
	}
	else
	{
		DrawBillboard3D(m_status.pos, 0.5f, 0.8f, m_status.scale, 0.0f, m_hImgs.back(), true);
	}

	// 描画フレームを進める
	if (m_frameCount % 20 == 0)
	{
		m_drawFrame++;
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
	VECTOR nextPos = VAdd(m_status.pos, m_status.dir);
	// 移動可能かの判定
	if (CheckCanMove(nextPos))
	{
		m_status.pos = nextPos;
	}
	else
	{
		// 移動不可能な場合はランダムで移動方向を変更
		m_status.dir = VGet(static_cast<float>(GetRand(100) - 50), 0.0f, static_cast<float>(GetRand(100) - 50));
		if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
		m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	}
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

bool EnemyNeffy::CheckCanMove(VECTOR nextPos)
{
	// 移動先のタイル番号を取得
	int tileX = NULL;
	int tileZ = NULL;
	m_pStage->GetTile(nextPos, tileX, tileZ);

	// 移動先のタイルが壁じゃない場合
	if (m_pStage->GetStageData()[tileZ][tileX] == StageTile::WL)
	{
		// 移動不可能
		return false;
	}
	else if (m_pStage->GetStageData()[tileZ][tileX] == StageTile::F1)
	{
		// 移動不可能
		return false;
	}
	else if (m_pStage->GetStageData()[tileZ][tileX] == StageTile::F2)
	{
		// 移動不可能
		return false;
	}

	return true;
}

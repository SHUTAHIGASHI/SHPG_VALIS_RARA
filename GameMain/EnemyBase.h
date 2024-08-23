#pragma once
#include "ObjectBase.h"
#include <DxLib.h>
#include <string>
#include <list>

namespace
{
	// 当たり判定
	constexpr float kRadius = 48.0f;
	// 移動速度
	constexpr float kSpeed = 4.0f;
	// ステージ外範囲
	constexpr float kStageLimitZ = 0.0f;
}

class EnemyBase :
    public ObjectBase
{
public:
	EnemyBase(std::string typeName, VECTOR pos);
	virtual ~EnemyBase();

	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() override;

	// ヒット処理
	virtual void OnHit(int damage);

	// 攻撃の判定
	bool CheckAttackCollision(ObjectBase* obj);
protected:
	// 削除処理
	virtual void OnDelete();
	// 死亡時の処理
	virtual void OnDead();

protected:
	// 画像ハンドル
	std::list<int> m_hImgs;

	// 毎フレームカウント
	int m_frameCount;
	// 描画フレーム
	int m_drawFrame;

	// 攻撃フレーム
	int m_attackFrame;
	// 攻撃クラス
	class MeleeAttack* m_pAttack;
};


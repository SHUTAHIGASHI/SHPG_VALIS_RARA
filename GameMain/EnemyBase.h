#pragma once
#include "ObjectBase.h"
#include <string>
#include <DxLib.h>

namespace
{
	// 当たり判定
	constexpr float kRadius = 48.0f;
	// 移動速度
	constexpr float kSpeed = 6.0f;
	// ステージ外範囲
	constexpr float kStageLimitZ = 0.0f;
}

class EnemyBase :
    public ObjectBase
{
public:
	EnemyBase(std::string typeName, VECTOR pos);
	~EnemyBase();

	// 更新
	virtual void Update() override;
	// 描画
	virtual void Draw() override;

	// ヒット処理
	virtual void OnHit();
protected:
};


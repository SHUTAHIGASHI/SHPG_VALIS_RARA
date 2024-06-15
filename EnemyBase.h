#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

class EnemyBase :
    public ObjectBase
{
public:
	EnemyBase(VECTOR pos);
	~EnemyBase();

	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// ヒット処理
	void OnHit();
private:
};


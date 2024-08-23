#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

class MeleeAttack : public ObjectBase
{
public:
	// コンストラクタ
	MeleeAttack(VECTOR pos, float radius);
	// デストラクタ
	~MeleeAttack();

	// 描画
	void Draw() override;

private:
};


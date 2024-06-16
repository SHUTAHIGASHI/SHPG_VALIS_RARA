#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

namespace ShotParam
{
	// 弾の速度
	constexpr float kShotSpeed = 324.0f;
	// 弾の半径
	constexpr float kShotRadius = 32.0f;
	// 弾の有効時間
	constexpr int kShotTime = 60 * 2;
}

class Shot : public ObjectBase
{
public:
	Shot(VECTOR pos, VECTOR target);
	Shot(VECTOR pos, ObjectBase* targetObj);
	~Shot();

	// 更新
	void Update();
	// 描画
	void Draw();

	// 着弾時
	void OnHit();

	// 弾速設定
	void SetSpeed(float speed) { m_status.moveSpeed = speed; }
	// 弾の大きさ設定
	void SetScale(float scale);
private:
	// 生成時の初期処理
	void Init(VECTOR pos);
	// ショットの更新
	void UpdateShotAndTarget();

private:
	// 弾の有効時間
	int m_shotTime = 60;
	// ターゲットオブジェクト
	ObjectBase* m_targetObject;
};


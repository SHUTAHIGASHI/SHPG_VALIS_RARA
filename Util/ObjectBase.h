#pragma once
#include "Game.h"

class ObjectBase
{
	struct ObjectStatus
	{
		// 有効判定
		bool isEnabled = true;
		// 死亡判定
		bool isDead = false;
		// 地面判定
		bool isGround = false;
		// 座標
		VECTOR exPos = Game::kVecZero;
		VECTOR pos = Game::kVecZero;
		VECTOR dir = Game::kVecZero;
		// 注視点
		VECTOR lookPos = Game::kVecZero;
		VECTOR lookDir = Game::kVecZero;
		// 回転
		VECTOR rota = Game::kVecZero;
		VECTOR rotaDir = Game::kVecZero;
		// 速度
		float moveSpeed = 0.0f;
		// ジャンプ力
		float jumpPower = 0.0f;
		// 半径
		float radius = 0.0f;
		// 拡大率
		float scale = 1.0f;
		// データハンドル
		int hModel = 0;
		// 画像データハンドル
		int hImg = 0;
		// 体力
		int hp = 0;
		// 無敵時間
		int invTime = 0;
	};

public:
	// コンストラクタ
	ObjectBase(){};
	// デストラクタ
	virtual ~ObjectBase() {};

	// 初期化
	virtual void Init() {};
	// 更新
	virtual void Update() {};
	virtual void Update(const InputState& input) {};
	// 描画
	virtual void Draw() {};

	// 衝突判定
	bool CheckCollision(ObjectBase* obj);

	// オブジェクトのステータスを取得
	const VECTOR GetPos() const { return m_status.pos; }
	const VECTOR GetDir() const { return m_status.dir; }
	const float GetSpeed() const { return m_status.moveSpeed; }
	const float GetRadius() const { return m_status.radius; }
	const int GetHP() const { return m_status.hp; }
	const bool IsEnabled() const { return m_status.isEnabled; }
	const bool IsDead() const { return m_status.isDead; }

protected:
	// オブジェクトのステータス
	ObjectStatus m_status;
};


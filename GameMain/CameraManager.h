#pragma once
#include "Game.h"
#include <deque>
#include <memory>

// カメラ
class CameraManager
{
public:
	// コンストラクタ
	CameraManager();
	// デストラクタ
	virtual ~CameraManager();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 被ダメージ画面揺れ
	void OnDamageQuake();
	// 移動時の揺れ
	void OnMoveQuake();

	// カメラ座標セット
	void SetPosAndTarget(VECTOR pos, VECTOR target) { m_pos = pos; m_targetPos = target; }

	// カメラ座標取得
	VECTOR GetPos() { return m_pos; }

private:// メンバ関数
	// 揺れ更新
	void UpdateDamageQuake();
	// 移動時の揺れ更新
	void UpdateMoveQuake();

private:// メンバ変数
	// カメラ座標
	VECTOR m_dir;
	VECTOR m_pos;
	VECTOR m_targetPos;
	// カメラ視野角
	float m_fov;
	// カメラ回転
	float m_rotaAxisY;
	// 移動時の揺れの大きさ
	float m_moveQuakeScale;
	float m_moveQuakeNum;
	// 移動時の揺れ判定
	bool m_isMoveQuake;
	// 画面揺れの大きさ
	int m_damageQuakeScale;

	// カメラ
	std::shared_ptr<class Camera> m_pCamera;
};

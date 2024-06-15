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

	// プレイヤーポインタセット
	void SetPlayer(class Player* pPlayer) { m_pPlayer = pPlayer; }

	// 初期化
	void Init();
	// 更新
	void Update();

	// 画面揺れ
	void OnScreenQuake();

private:// メンバ関数
	// 座標更新
	void UpdatePos();
	// 揺れ更新
	void UpdateQuake();

private:// メンバ変数
	// カメラ座標
	VECTOR m_dir;
	VECTOR m_pos;
	VECTOR m_targetPos;
	// カメラ視野角
	float m_fov;
	// カメラ回転
	float m_rotaAxisY;
	// 画面揺れの大きさ
	int m_screenQuakeScale;
	// カメラ
	std::shared_ptr<class Camera> m_pCamera;
private:
	// プレイヤーポインタ
	class Player* m_pPlayer;
};

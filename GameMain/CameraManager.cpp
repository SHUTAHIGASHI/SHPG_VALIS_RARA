#include "CameraManager.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	// 被ダメージ画面揺れの大きさ
	constexpr int kDamageQuakeScaleNum = 10;
	// 移動時の画面揺れの大きさ
	constexpr float kMoveQuakeScaleNum = 2.0f;
	// 移動時の画面揺れの速度
	constexpr float kMoveQuakeSpeedNum = 0.5f;
}

// コンストラクタ
CameraManager::CameraManager():
	m_dir(Game::kVecZero),
	m_pos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_fov(0.0f),
	m_rotaAxisY(0.0f),
	m_moveQuakeScale(0.0f),
	m_moveQuakeNum(0.0f),
	m_isMoveQuake(false),
	m_damageQuakeScale(0),
	m_pCamera(std::make_shared<Camera>())
{
}

// デストラクタ
CameraManager::~CameraManager()
{
	// 処理なし
}

// 初期化
void CameraManager::Init()
{
	// カメラの視野角設定
	m_fov = CameraSetting::kFovNum;
	// カメラの回転設定
	m_rotaAxisY = DX_PI_F;
	// カメラ設定初期化
	m_pCamera->Init(CameraSetting::kCameraNear, CameraSetting::kCameraFar, m_fov);
	// カメラ座標設定
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
	// 移動時の揺れサイズ設定
	m_moveQuakeScale = 0;
	// 移動時の揺れの向き設定
	m_moveQuakeNum = kMoveQuakeSpeedNum;
}

// 更新
void CameraManager::Update()
{	
	// 画面揺れの処理
	if (m_damageQuakeScale != 0)
	{
		UpdateDamageQuake();
	}

	if(m_isMoveQuake)
	{
		UpdateMoveQuake();
	}
	
	// カメラに位置を反映
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
}

// 画面揺れ
void CameraManager::OnDamageQuake()
{
	// 揺れの大きさを設定
	m_damageQuakeScale = kDamageQuakeScaleNum;
}

void CameraManager::OnMoveQuake()
{
	// 揺れ判定
	m_isMoveQuake = true;
}

void CameraManager::UpdateDamageQuake()
{
	// 画面揺れの数値を代入
	m_targetPos.x += m_damageQuakeScale;
	m_targetPos.y += m_damageQuakeScale;
	m_pos.x += m_damageQuakeScale;
	m_pos.y += m_damageQuakeScale;

	// 画面揺れの数値が0以外の場合
	if (m_damageQuakeScale != 0)
	{
		// 揺れの大きさを減らす
		if (m_damageQuakeScale > 0)
		{
			m_damageQuakeScale--;
		}
		m_damageQuakeScale *= -1;
	}
}

void CameraManager::UpdateMoveQuake()
{
	// 画面揺れの向きを設定
	m_moveQuakeScale += m_moveQuakeNum;
	if(m_moveQuakeScale > kMoveQuakeScaleNum)
	{
		m_moveQuakeNum *= -1;
	}
	if(m_moveQuakeScale < -kMoveQuakeScaleNum)
	{
		m_moveQuakeNum *= -1;
	}
	// 画面揺れの数値を代入
	m_pos.y += m_moveQuakeScale;
	m_targetPos.y += m_moveQuakeScale;
	// 画面揺れ判定リセット
	m_isMoveQuake = false;
}

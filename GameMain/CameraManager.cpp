#include "CameraManager.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	// 画面揺れの大きさ
	constexpr int kQuakeScaleNum = 10;
}

// コンストラクタ
CameraManager::CameraManager():
	m_dir(Game::kVecZero),
	m_pos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_fov(0.0f),
	m_rotaAxisY(0.0f),
	m_screenQuakeScale(0),
	m_pCamera(std::make_shared<Camera>()),
	m_pPlayer(nullptr)
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
}

// 更新
void CameraManager::Update()
{
	// カメラ座標の更新
	UpdatePos();
	
	// 画面揺れの処理
	if (m_screenQuakeScale != 0)
	{
		UpdateQuake();
	}
	
	// カメラに位置を反映
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
}

// 画面揺れ
void CameraManager::OnScreenQuake()
{
	// 揺れの大きさを設定
	m_screenQuakeScale = kQuakeScaleNum;
}

void CameraManager::UpdatePos()
{
	// カメラに位置を反映
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
}

void CameraManager::UpdateQuake()
{
	// 画面揺れの数値を代入
	m_targetPos.x += m_screenQuakeScale;
	m_targetPos.y += m_screenQuakeScale;
	m_pos.x += m_screenQuakeScale;
	m_pos.y += m_screenQuakeScale;

	// 画面揺れの数値が0以外の場合
	if (m_screenQuakeScale != 0)
	{
		// 揺れの大きさを減らす
		if (m_screenQuakeScale > 0)
		{
			m_screenQuakeScale--;
		}
		m_screenQuakeScale *= -1;
	}
}

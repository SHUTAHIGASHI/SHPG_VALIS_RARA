#include "SceneMain.h"
// シーン関係
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "ScenePauseMenu.h"
#include "SceneGameOver.h"
#include "SceneClear.h"
#include "SceneHowTo.h"
#include "SceneFade.h"
// ゲーム関係
#include "Game.h"
#include "Player.h"
// 全般
#include "CameraController.h"
#include "EffekseerManager.h"
#include "SoundManager.h"

SceneMain::SceneMain(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneMain::StartUpdate),
	m_drawFunc(&SceneMain::StartDraw),
	m_pCamera(std::make_shared<CameraController>()),
	m_pPlayer(std::make_shared<Player>())
{
}

SceneMain::~SceneMain()
{
	// 再生中の音楽を停止
	SoundManager::GetInstance().StopBGM();
}

void SceneMain::Init()
{
	// カメラ初期化
	m_pCamera->Init();
	// プレイヤー初期化
	m_pPlayer = std::make_shared<Player>();
}

void SceneMain::Update(const InputState& input)
{
	// Update処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);

	// エフェクトの更新処理
	EffekseerManager::GetInstance().Update();
}

void SceneMain::Draw()
{
	// Draw処理のメンバ関数ポインタ
	//(this->*m_drawFunc)();

	// プレイヤーの描画
	m_pPlayer->Draw();

	// エフェクト描画
	EffekseerManager::GetInstance().Draw();

	// グリッドを表示
	for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
	{
		VECTOR start = VGet(-1000.0f, 0.0f, z);
		VECTOR end = VGet(1000.0f, 0.0f, z);
		DrawLine3D(start, end, 0x00ff00);
	}

	for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
	{
		VECTOR start = VGet(x, 0.0f, -1000.0f);
		VECTOR end = VGet(x, 0.0f, 1000.0f);
		DrawLine3D(start, end, 0xff0000);
	}
}

void SceneMain::End()
{
	// 再生中のエフェクト停止
	EffekseerManager::GetInstance().StopAllEffect();
}

void SceneMain::NormalUpdate(const InputState& input)
{
	// ポーズメニューへ移行
	if (input.IsTriggered(InputType::pause))
	{
		// BGM停止
		SoundManager::GetInstance().StopBGM();
		// ポーズメニューシーンへ移行
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}

	// 音楽再生開始
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic(MusicType::main);
	}
}

void SceneMain::StartUpdate(const InputState& input)
{
}

void SceneMain::EndUpdate(const InputState& input)
{
}

void SceneMain::NormalDraw()
{
}

void SceneMain::StartDraw()
{
	// 処理なし
}

void SceneMain::EndDraw()
{
	// 処理なし
}

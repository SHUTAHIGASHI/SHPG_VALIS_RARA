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
#include "EnemyManager.h"
// 全般
#include "CameraManager.h"
#include "EffekseerManager.h"
#include "SoundManager.h"
#include "SkyDome.h"

SceneMain::SceneMain(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneMain::StartUpdate),
	m_pCamera(std::make_shared<CameraManager>()),
	m_pPlayer(std::make_shared<Player>()),
	m_pEnemyManager(std::make_shared<EnemyManager>()),
	m_pSkyDome(std::make_shared<SkyDome>())
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
	m_pCamera->SetPlayer(m_pPlayer.get());
	m_pCamera->Init();
	// プレイヤー初期化
	m_pPlayer->SetEnemyManager(m_pEnemyManager.get());
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->Init();
	// 敵管理初期化
	m_pEnemyManager->Init();
	// スカイドームの初期化処理
	m_pSkyDome->Init(m_pPlayer->GetPos());
}

void SceneMain::Update(const InputState& input)
{
	// Update処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);

	// カメラ更新
	m_pCamera->Update();
	// プレイヤー更新
	m_pPlayer->Update(input);
	// 敵管理更新
	m_pEnemyManager->Update();
	// スカイドームの更新処理
	m_pSkyDome->Update(m_pPlayer->GetPos());

	// エフェクトの更新処理
	EffekseerManager::GetInstance().Update();
}

void SceneMain::Draw()
{
	// 敵管理描画
	m_pEnemyManager->Draw();
	// プレイヤー描画
	m_pPlayer->Draw();
	//スカイドーム描画
	//m_pSkyDome->Draw();

	// エフェクト描画
	EffekseerManager::GetInstance().Draw();

	// ステージライン描画
	DrawStageLine();
}

void SceneMain::End()
{
	// 再生中のエフェクト停止
	EffekseerManager::GetInstance().StopAllEffect();
}

void SceneMain::DrawStageLine()
{
	// グリッドを表示
	for (float z = -Game::kStageSizeZ; z <= Game::kStageSizeZ; z += 100.0f)
	{
		VECTOR start = VGet(-Game::kStageSizeX, -100.0f, z);
		VECTOR end = VGet(Game::kStageSizeX, -100.0f, z);
		DrawLine3D(start, end, 0x00ff00);
	}

	for (float x = -Game::kStageSizeX; x <= Game::kStageSizeX; x += 100.0f)
	{
		VECTOR start = VGet(x, -100.0f, -Game::kStageSizeZ);
		VECTOR end = VGet(x, -100.0f, Game::kStageSizeZ);
		DrawLine3D(start, end, 0xff0000);
	}
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

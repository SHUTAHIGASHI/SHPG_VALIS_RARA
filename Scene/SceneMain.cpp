#include "SceneMain.h"
// シーン関係
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "ScenePauseMenu.h"
#include "SceneGameOver.h"
#include "SceneResult.h"
#include "SceneHowTo.h"
#include "SceneFade.h"
// ゲーム関係
#include "Game.h"
#include "Player.h"
#include "EnemyManager.h"
// 全般
#include "CameraManager.h"
#include "SoundManager.h"
#include "UiManager.h"
#include "SkyDome.h"

SceneMain::SceneMain(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_pCamera(std::make_shared<CameraManager>()),
	m_pPlayer(std::make_shared<Player>()),
	m_pEnemyManager(std::make_shared<EnemyManager>()),
	m_pSkyDome(std::make_shared<SkyDome>())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// マウス非表示
	SetMouseDispFlag(false);
	// プレイヤー初期化
	m_pPlayer->SetEnemyManager(m_pEnemyManager.get());
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->Init();
	// 敵管理初期化
	m_pEnemyManager->SetPlayer(m_pPlayer.get());
	m_pEnemyManager->Init();
	// スカイドームの初期化処理
	m_pSkyDome->Init(m_pPlayer->GetPos());
	// カメラ初期化
	m_pCamera->Init();
	// カーソル座標固定
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
}

void SceneMain::Update(const InputState& input)
{
	// Update処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);

	// UI更新
	UiManager::GetInstance().Update();
}

void SceneMain::Draw()
{
	//スカイドーム描画
	m_pSkyDome->Draw();
	// ステージライン描画
	DrawStageLine();

	// 敵管理描画
	m_pEnemyManager->Draw();
	// プレイヤー描画
	m_pPlayer->Draw();

	// UI描画
	UiManager::GetInstance().Draw();
}

void SceneMain::End()
{
	// マウス表示
	SetMouseDispFlag(true);
	// 全UIの削除
	UiManager::GetInstance().DeleteAllUI();
}

void SceneMain::DrawStageLine()
{
	// グリッドを表示
	for (float z = -Game::kStageSizeZ; z <= Game::kStageSizeZ; z += 100.0f)
	{
		VECTOR start = VGet(-Game::kStageSizeX, -156.0, z);
		VECTOR end = VGet(Game::kStageSizeX, -156.0, z);
		DrawLine3D(start, end, 0x00ff00);
	}

	for (float x = -Game::kStageSizeX; x <= Game::kStageSizeX; x += 100.0f)
	{
		VECTOR start = VGet(x, -156.0, -Game::kStageSizeZ);
		VECTOR end = VGet(x, -156.0, Game::kStageSizeZ);
		DrawLine3D(start, end, 0xff0000);
	}
}

void SceneMain::NormalUpdate(const InputState& input)
{
	// ポーズメニューへ移行
	if (input.IsTriggered(InputType::pause))
	{
		// ポーズメニューシーンへ移行
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}

	// カーソル座標固定
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// カメラ更新
	m_pCamera->Update();
	// プレイヤー更新
	m_pPlayer->Update(input);
	// 敵管理更新
	m_pEnemyManager->Update();
	// スカイドームの更新
	m_pSkyDome->Update();
	m_pSkyDome->SetPos(m_pPlayer->GetPos());

	// ゲームオーバー
	if (m_pPlayer->IsDead())
	{
		// シーン変更
		m_Manager.PushSceneAllUpdate(new SceneResult(m_Manager));

		// 実行する更新処理変更
		m_updateFunc = &SceneMain::EndUpdate;

		return;
	}
}

void SceneMain::StartUpdate(const InputState& input)
{
	// ポーズメニューへ移行
	if (input.IsTriggered(InputType::pause))
	{
		// ポーズメニューシーンへ移行
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}
}

void SceneMain::EndUpdate(const InputState& input)
{
	// カメラ更新
	m_pCamera->Update();
	// プレイヤー更新
	m_pPlayer->UpdateGameover();
	// 敵管理更新
	m_pEnemyManager->Update();
	// スカイドームの更新
	m_pSkyDome->Update();
	m_pSkyDome->SetPos(m_pPlayer->GetPos());
}

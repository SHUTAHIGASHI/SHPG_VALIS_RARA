#include "StageManager.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "Load.h"
#include "Player.h"

namespace
{
	// ラウンド遅延時間
	constexpr int kRoundStartInterval = 60 * 5;
	constexpr int kRoundEndInterval = 60 * 3;
}

StageManager::StageManager():
	m_roundState(RoundState::ROUND_START),
	m_roundCount(1),
	m_roundInterval(0),
	m_updateFunc(&StageManager::RoundStartIntervalUpdate),
	m_pStage(std::make_shared<Stage>()),
	m_pEnemyManager(std::make_shared<EnemyManager>()),
	m_pPlayer(nullptr)
{
}

StageManager::~StageManager()
{
}

void StageManager::Init()
{
	// ステージ初期化
	m_pStage->Init();
	// 敵管理初期化
	m_pEnemyManager->SetPlayer(m_pPlayer);
	m_pEnemyManager->SetStage(m_pStage.get());
	m_pEnemyManager->Init();
	// プレイヤーにステージ情報を設定
	m_pPlayer->SetStage(m_pStage.get());
	m_pPlayer->SetEnemyManager(m_pEnemyManager.get());
}

void StageManager::Update()
{
	// ラウンド管理更新
	(this->*m_updateFunc)();

	// UI更新
	UiManager::GetInstance().SetRoundState(m_roundState);
	UiManager::GetInstance().SetRoundCount(m_roundCount);
}

void StageManager::Draw()
{
	// ステージ描画
	m_pStage->Draw();
	// 敵管理描画
	m_pEnemyManager->Draw();
}

void StageManager::OnRoundEnd()
{
	// ラウンド数カウント
	m_roundCount++;
	// ラウンドごとの難易度上昇
	m_pEnemyManager->DiffcultyUp();
}

void StageManager::RoundOnUpdate()
{
	// ステージ更新
	m_pStage->Update();
	// 敵管理更新
	m_pEnemyManager->Update();

	// 敵生成完了判定
	if (m_pEnemyManager->IsEnemyCreateEnd())
	{
		if (m_pEnemyManager->GetEnemies().size() <= 0)
		{
			// ラウンド状態変更
			m_roundState = RoundState::ROUND_END;
			// ラウンド終了
			OnRoundEnd();
			// ラウンド開始
			m_updateFunc = &StageManager::RoundEndIntervalUpdate;
		}
	}
}

void StageManager::RoundStartIntervalUpdate()
{
	// ラウンド開始遅延
	if (m_roundInterval < kRoundStartInterval)
	{
		m_roundInterval++;
	}
	else
	{
		// ラウンド状態変更
		m_roundState = RoundState::ROUND_ON;
		// ラウンド開始
		m_updateFunc = &StageManager::RoundOnUpdate;
		// 敵管理の初期化
		m_pEnemyManager->Init();
		// ラウンド遅延初期化
		m_roundInterval = 0;
	}
}

void StageManager::RoundEndIntervalUpdate()
{
	// ラウンド終了遅延
	if (m_roundInterval < kRoundEndInterval)
	{
		m_roundInterval++;
	}
	else
	{
		// ラウンド状態変更
		m_roundState = RoundState::ROUND_START;
		// ラウンド終了
		m_updateFunc = &StageManager::RoundStartIntervalUpdate;
		// ラウンド遅延初期化
		m_roundInterval = 0;
	}
}

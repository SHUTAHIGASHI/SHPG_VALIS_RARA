#include "StageManager.h"
#include "EnemyManager.h"

namespace
{
	// ラウンド遅延時間
	constexpr int kRoundStartInterval = 60 * 5;
	constexpr int kRoundEndInterval = 60 * 3;
}

StageManager::StageManager():
	m_roundCount(0),
	m_roundInterval(0),
	m_updateFunc(&StageManager::RoundStartIntervalUpdate),
	m_pEnemyManager(std::make_shared<EnemyManager>()),
	m_pPlayer(nullptr)
{
}

StageManager::~StageManager()
{
}

void StageManager::Init()
{
	// 敵管理初期化
	m_pEnemyManager->SetPlayer(m_pPlayer);
	m_pEnemyManager->Init();
}

void StageManager::Update()
{
	// ラウンド管理更新
	(this->*m_updateFunc)();
}

void StageManager::Draw()
{
	// 敵管理描画
	m_pEnemyManager->Draw();
}

void StageManager::OnRoundEnd()
{
	// ラウンド数カウント
	m_roundCount++;
}

void StageManager::RoundOnUpdate()
{
	// 敵管理更新
	m_pEnemyManager->Update();

	// 敵生成完了判定
	if (m_pEnemyManager->IsEnemyCreateEnd())
	{
		if (m_pEnemyManager->GetEnemies().size() <= 0)
		{
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
		// ラウンド終了
		m_updateFunc = &StageManager::RoundStartIntervalUpdate;
		// ラウンド遅延初期化
		m_roundInterval = 0;
	}
}

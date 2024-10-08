#include "EnemyManager.h"
#include "ObjectBase.h"
#include "EnemyBase.h"
#include "EnemyNeffy.h"
#include "EnemyNeffyKarasu.h"
#include "Game.h"
#include "Player.h"
#include "Stage.h"

namespace
{
	// 敵の生成数
	constexpr int kEnemyNum = 5;
	// 生成する座標の範囲
	constexpr int kSpawnRange = 100;
}

EnemyManager::EnemyManager():
	m_createEnemyCount(0),
	m_enemyMaxOnRound(15),
	m_enemyMaxOnScreen(kEnemyNum),
	m_isEnemyCreateEnd(false),
	m_pEnemies(),
	m_pPlayer(nullptr),
	m_pStage(nullptr)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// 敵の生成数初期化
	m_createEnemyCount = 0;
	// 敵の生成完了判定初期化
	m_isEnemyCreateEnd = false;
	// 敵の配列クリア
	m_pEnemies.clear();
}

void EnemyManager::Update()
{
	// 敵の生成
	if (m_createEnemyCount < m_enemyMaxOnRound)
	{
		// 現在の敵数が最大同時生成数より少ない場合
		if (m_pEnemies.size() < m_enemyMaxOnScreen)
		{
			// 敵を生成
			CreateEnemy();
		}
	}
	else
	{
		// 敵の生成完了
		m_isEnemyCreateEnd = true;
	}

	// 敵の更新
	for (auto& enemy : m_pEnemies)
	{
		// 更新
		enemy->Update();
		// 当たり判定
		if (enemy->CheckAttackCollision(m_pPlayer))
		{
			// プレイヤーのダメージ処理
			m_pPlayer->OnDamage(10);
		}
	}
	// 敵の削除
	m_pEnemies.remove_if([](EnemyBase* obj) { return !obj->IsEnabled(); });
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_pEnemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::DiffcultyUp()
{
	// 敵の最大生成数を増加
	m_enemyMaxOnRound += 5;
	// 敵の最大同時生成数を増加
	m_enemyMaxOnScreen += 2;
}

void EnemyManager::CreateEnemy()
{
	// 敵生成数カウント
	m_createEnemyCount++;
	// 敵生成
	m_pEnemies.push_back(GetRandomEnemy());
	m_pEnemies.back()->Init();
}

VECTOR EnemyManager::GetSpawnPos()
{
	VECTOR spawnPos = Game::kVecZero;
	// 生成する座標の順番をランダムで取得
	int spawnPointNum = GetRand(m_pStage->GetSpawnPointNum() - 1);
	// 生成する中心座標を取得
	VECTOR centerPos = m_pStage->GetSpawnPoint(spawnPointNum);
	// 生成する座標をランダムで取得
	spawnPos = VAdd(centerPos, VGet(static_cast<float>(GetRand(kSpawnRange)), 
		0.0f,
		static_cast<float>(GetRand(kSpawnRange))));

	return spawnPos;
}

EnemyBase* EnemyManager::GetRandomEnemy()
{
	int index = GetRand(static_cast<int>(2));

	//todo 生成する敵の種類を変更する
	if(index == 0)
	{
		return new EnemyNeffyKarasu(m_pPlayer, GetSpawnPos());
	}
	else
	{
		return new EnemyNeffy(m_pPlayer, GetSpawnPos(), m_pStage);
	}

	return nullptr;
}

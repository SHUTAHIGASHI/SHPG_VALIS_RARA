#include "EnemyManager.h"
#include "ObjectBase.h"
#include "EnemyBase.h"
#include "EnemyNeffy.h"
#include "EnemyChaseNeffy.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// 敵の生成数
	constexpr int kEnemyNum = 5;
	// 敵の生成範囲
	constexpr float kEnemySpawnRange = 1000.0f;
}

EnemyManager::EnemyManager():
	m_createEnemyCount(0),
	m_enemyMaxOnRound(15),
	m_enemyMaxOnScreen(kEnemyNum),
	m_isEnemyCreateEnd(false),
	m_spawnCenterPos(Game::kVecZero),
	m_pEnemies(),
	m_pPlayer(nullptr)
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
		if (enemy->CheckCollision(m_pPlayer))
		{
			// 敵のダメージ処理
			enemy->OnHitPlayer();
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
	m_enemyMaxOnScreen += 1;
}

void EnemyManager::CreateEnemy()
{
	// 敵生成数カウント
	m_createEnemyCount++;
	// 敵生成
	m_pEnemies.push_back(GetRandomEnemy());
	m_pEnemies.back()->Init();
}

VECTOR EnemyManager::GetRandomPos()
{
	VECTOR result;

	// 指定した位置を中心に指定した範囲でランダムな位置を返す
	result.x = static_cast<float>(m_spawnCenterPos.x + GetRand(static_cast<int>(Game::kStageSizeX)) + kEnemySpawnRange);
	result.y = 0.0f;
	result.z = static_cast<float>(m_spawnCenterPos.z + GetRand(static_cast<int>(Game::kStageSizeZ)) - (kEnemySpawnRange / 2));

	return result;
}

EnemyBase* EnemyManager::GetRandomEnemy()
{
	int index = GetRand(static_cast<int>(2));

	return new EnemyChaseNeffy(m_pPlayer, GetRandomPos());

	//todo 生成する敵の種類を変更する
	if(index == 0)
	{
		return new EnemyChaseNeffy(m_pPlayer, GetRandomPos());
	}
	else
	{
		return new EnemyNeffy(GetRandomPos());
	}

	return nullptr;
}

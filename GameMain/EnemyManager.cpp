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
}

EnemyManager::EnemyManager():
	m_pEnemies(),
	m_pPlayer(nullptr)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (int i = 0; i < kEnemyNum; i++)
	{
		CreateEnemy();
	}
}

void EnemyManager::Update()
{
	// 敵の生成
	if (m_pEnemies.size() < kEnemyNum)
	{
		CreateEnemy();
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
			enemy->OnHit();
			// プレイヤーのダメージ処理
			m_pPlayer->OnHit();
		}
	}

	// 敵の削除
	m_pEnemies.remove_if([](ObjectBase* obj) { return !obj->IsEnabled(); });
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_pEnemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::CreateEnemy()
{
	m_pEnemies.push_back(GetRandomEnemy());
	m_pEnemies.back()->Init();
}

VECTOR EnemyManager::GetRandomPos()
{
	VECTOR result;

	result.x = static_cast<float>(GetRand(static_cast<int>(Game::kStageSizeX)) - 500);
	result.y = 0.0f;
	result.z = static_cast<float>(GetRand(static_cast<int>(Game::kStageSizeZ)) + Game::kStageSizeZ);

	return result;
}

EnemyBase* EnemyManager::GetRandomEnemy()
{
	int index = GetRand(static_cast<int>(2));

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

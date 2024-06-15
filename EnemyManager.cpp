#include "EnemyManager.h"
#include "ObjectBase.h"
#include "EnemyBase.h"
#include "Game.h"

namespace
{
	// “G‚Ì¶¬”
	constexpr int kEnemyNum = 2;
}

EnemyManager::EnemyManager():
	m_pEnemies()
{
	for (int i = 0; i < kEnemyNum; i++)
	{
		CreateEnemy();
	}
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (auto& enemy : m_pEnemies)
	{
		enemy->Init();
	}
}

void EnemyManager::Update()
{
	// “G‚Ì¶¬
	if (m_pEnemies.size() < kEnemyNum)
	{
		CreateEnemy();
	}

	// “G‚ÌXV
	for (auto& enemy : m_pEnemies)
	{
		enemy->Update();
	}

	// “G‚Ìíœ
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
	m_pEnemies.push_back(new EnemyBase(GetRandomPos()));
	m_pEnemies.back()->Init();
}

VECTOR EnemyManager::GetRandomPos()
{
	VECTOR result;

	result.x = GetRand(Game::kStageSizeX) - 500;
	result.y = GetRand(Game::kStageSizeY);
	result.z = GetRand(Game::kStageSizeZ) - 500;

	return result;
}

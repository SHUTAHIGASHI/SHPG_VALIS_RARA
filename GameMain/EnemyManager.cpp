#include "EnemyManager.h"
#include "ObjectBase.h"
#include "EnemyBase.h"
#include "EnemyNeffy.h"
#include "EnemyChaseNeffy.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// “G‚Ì¶¬”
	constexpr int kEnemyNum = 5;
}

EnemyManager::EnemyManager():
	m_createEnemyCount(0),
	m_enemyMaxOnRound(15),
	m_enemyMaxOnScreen(kEnemyNum),
	m_isEnemyCreateEnd(false),
	m_pEnemies(),
	m_pPlayer(nullptr)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// “G‚Ì¶¬”‰Šú‰»
	m_createEnemyCount = 0;
	// “G‚Ì¶¬Š®—¹”»’è‰Šú‰»
	m_isEnemyCreateEnd = false;
	// “G‚Ì”z—ñƒNƒŠƒA
	m_pEnemies.clear();
}

void EnemyManager::Update()
{
	// “G‚Ì¶¬
	if (m_createEnemyCount < m_enemyMaxOnRound)
	{
		// Œ»İ‚Ì“G”‚ªÅ‘å“¯¶¬”‚æ‚è­‚È‚¢ê‡
		if (m_pEnemies.size() < m_enemyMaxOnScreen)
		{
			// “G‚ğ¶¬
			CreateEnemy();
		}
	}
	else
	{
		// “G‚Ì¶¬Š®—¹
		m_isEnemyCreateEnd = true;
	}

	// “G‚ÌXV
	for (auto& enemy : m_pEnemies)
	{
		// XV
		enemy->Update();
		// “–‚½‚è”»’è
		if (enemy->CheckCollision(m_pPlayer))
		{
			// “G‚Ìƒ_ƒ[ƒWˆ—
			enemy->OnHitPlayer();
			// ƒvƒŒƒCƒ„[‚Ìƒ_ƒ[ƒWˆ—
			m_pPlayer->OnDamage(10);
		}
	}
	// “G‚Ìíœ
	m_pEnemies.remove_if([](EnemyBase* obj) { return !obj->IsEnabled(); });
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_pEnemies)
	{
		enemy->Draw();
	}

	// “G‚Ì¶¬”•\¦
	DrawFormatString(0, 0, 0xffffff, "¶¬”:%d", m_createEnemyCount);
}

void EnemyManager::CreateEnemy()
{
	// “G¶¬”ƒJƒEƒ“ƒg
	m_createEnemyCount++;
	// “G¶¬
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

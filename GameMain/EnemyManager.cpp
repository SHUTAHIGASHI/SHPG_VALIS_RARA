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
	// “G‚Ì¶¬”
	constexpr int kEnemyNum = 5;
	// ¶¬‚·‚éÀ•W‚Ì”ÍˆÍ
	constexpr int kSpawnRange = 100;
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
		if (enemy->CheckAttackCollision(m_pPlayer))
		{
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
}

void EnemyManager::DiffcultyUp()
{
	// “G‚ÌÅ‘å¶¬”‚ğ‘‰Á
	m_enemyMaxOnRound += 5;
	// “G‚ÌÅ‘å“¯¶¬”‚ğ‘‰Á
	m_enemyMaxOnScreen += 1;
}

void EnemyManager::CreateEnemy()
{
	// “G¶¬”ƒJƒEƒ“ƒg
	m_createEnemyCount++;
	// “G¶¬
	m_pEnemies.push_back(GetRandomEnemy());
	m_pEnemies.back()->Init();
}

VECTOR EnemyManager::GetSpawnPos()
{
	VECTOR spawnPos = Game::kVecZero;
	// ¶¬‚·‚éÀ•W‚Ì‡”Ô‚ğƒ‰ƒ“ƒ_ƒ€‚Åæ“¾
	int spawnPointNum = GetRand(m_pStage->GetSpawnPointNum() - 1);
	// ¶¬‚·‚é’†SÀ•W‚ğæ“¾
	VECTOR centerPos = m_pStage->GetSpawnPoint(spawnPointNum);
	// ¶¬‚·‚éÀ•W‚ğƒ‰ƒ“ƒ_ƒ€‚Åæ“¾
	spawnPos = VAdd(centerPos, VGet(static_cast<float>(GetRand(kSpawnRange)), 
		0.0f,
		static_cast<float>(GetRand(kSpawnRange))));

	return spawnPos;
}

EnemyBase* EnemyManager::GetRandomEnemy()
{
	int index = GetRand(static_cast<int>(2));

	//todo ¶¬‚·‚é“G‚Ìí—Ş‚ğ•ÏX‚·‚é
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

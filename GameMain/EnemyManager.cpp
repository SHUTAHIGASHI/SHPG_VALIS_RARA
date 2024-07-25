#include "EnemyManager.h"
#include "ObjectBase.h"
#include "EnemyBase.h"
#include "EnemyNeffy.h"
#include "EnemyChaseNeffy.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// �G�̐�����
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
	// �G�̐���
	if (m_pEnemies.size() < kEnemyNum)
	{
		CreateEnemy();
	}

	// �G�̍X�V
	for (auto& enemy : m_pEnemies)
	{
		// �X�V
		enemy->Update();
		// �����蔻��
		if (enemy->CheckCollision(m_pPlayer))
		{
			// �G�̃_���[�W����
			enemy->OnHit();
			// �v���C���[�̃_���[�W����
			m_pPlayer->OnHit();
		}
	}

	// �G�̍폜
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

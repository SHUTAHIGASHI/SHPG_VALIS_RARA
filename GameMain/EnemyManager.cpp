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
	// �G�̐�����������
	m_createEnemyCount = 0;
	// �G�̐����������菉����
	m_isEnemyCreateEnd = false;
	// �G�̔z��N���A
	m_pEnemies.clear();
}

void EnemyManager::Update()
{
	// �G�̐���
	if (m_createEnemyCount < m_enemyMaxOnRound)
	{
		// ���݂̓G�����ő哯����������菭�Ȃ��ꍇ
		if (m_pEnemies.size() < m_enemyMaxOnScreen)
		{
			// �G�𐶐�
			CreateEnemy();
		}
	}
	else
	{
		// �G�̐�������
		m_isEnemyCreateEnd = true;
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
			enemy->OnHitPlayer();
			// �v���C���[�̃_���[�W����
			m_pPlayer->OnDamage(10);
		}
	}
	// �G�̍폜
	m_pEnemies.remove_if([](EnemyBase* obj) { return !obj->IsEnabled(); });
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_pEnemies)
	{
		enemy->Draw();
	}

	// �G�̐������\��
	DrawFormatString(0, 0, 0xffffff, "������:%d", m_createEnemyCount);
}

void EnemyManager::CreateEnemy()
{
	// �G�������J�E���g
	m_createEnemyCount++;
	// �G����
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

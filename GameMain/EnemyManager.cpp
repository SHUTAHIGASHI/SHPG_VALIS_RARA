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
	// �G�̐�����
	constexpr int kEnemyNum = 5;
	// ����������W�͈̔�
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
		if (enemy->CheckAttackCollision(m_pPlayer))
		{
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
}

void EnemyManager::DiffcultyUp()
{
	// �G�̍ő吶�����𑝉�
	m_enemyMaxOnRound += 5;
	// �G�̍ő哯���������𑝉�
	m_enemyMaxOnScreen += 1;
}

void EnemyManager::CreateEnemy()
{
	// �G�������J�E���g
	m_createEnemyCount++;
	// �G����
	m_pEnemies.push_back(GetRandomEnemy());
	m_pEnemies.back()->Init();
}

VECTOR EnemyManager::GetSpawnPos()
{
	VECTOR spawnPos = Game::kVecZero;
	// ����������W�̏��Ԃ������_���Ŏ擾
	int spawnPointNum = GetRand(m_pStage->GetSpawnPointNum() - 1);
	// �������钆�S���W���擾
	VECTOR centerPos = m_pStage->GetSpawnPoint(spawnPointNum);
	// ����������W�������_���Ŏ擾
	spawnPos = VAdd(centerPos, VGet(static_cast<float>(GetRand(kSpawnRange)), 
		0.0f,
		static_cast<float>(GetRand(kSpawnRange))));

	return spawnPos;
}

EnemyBase* EnemyManager::GetRandomEnemy()
{
	int index = GetRand(static_cast<int>(2));

	//todo ��������G�̎�ނ�ύX����
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

#include "StageManager.h"
#include "EnemyManager.h"

namespace
{
	// ���E���h�x������
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
	// �G�Ǘ�������
	m_pEnemyManager->SetPlayer(m_pPlayer);
	m_pEnemyManager->Init();
}

void StageManager::Update()
{
	// ���E���h�Ǘ��X�V
	(this->*m_updateFunc)();
}

void StageManager::Draw()
{
	// �G�Ǘ��`��
	m_pEnemyManager->Draw();
}

void StageManager::OnRoundEnd()
{
	// ���E���h���J�E���g
	m_roundCount++;
}

void StageManager::RoundOnUpdate()
{
	// �G�Ǘ��X�V
	m_pEnemyManager->Update();

	// �G������������
	if (m_pEnemyManager->IsEnemyCreateEnd())
	{
		if (m_pEnemyManager->GetEnemies().size() <= 0)
		{
			// ���E���h�I��
			OnRoundEnd();
			// ���E���h�J�n
			m_updateFunc = &StageManager::RoundEndIntervalUpdate;
		}
	}
}

void StageManager::RoundStartIntervalUpdate()
{
	// ���E���h�J�n�x��
	if (m_roundInterval < kRoundStartInterval)
	{
		m_roundInterval++;
	}
	else
	{
		// ���E���h�J�n
		m_updateFunc = &StageManager::RoundOnUpdate;
		// �G�Ǘ��̏�����
		m_pEnemyManager->Init();
		// ���E���h�x��������
		m_roundInterval = 0;
	}
}

void StageManager::RoundEndIntervalUpdate()
{
	// ���E���h�I���x��
	if (m_roundInterval < kRoundEndInterval)
	{
		m_roundInterval++;
	}
	else
	{
		// ���E���h�I��
		m_updateFunc = &StageManager::RoundStartIntervalUpdate;
		// ���E���h�x��������
		m_roundInterval = 0;
	}
}

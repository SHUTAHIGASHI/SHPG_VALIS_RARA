#include "StageManager.h"
#include "EnemyManager.h"
#include "UiManager.h"

namespace
{
	// ���E���h�x������
	constexpr int kRoundStartInterval = 60 * 5;
	constexpr int kRoundEndInterval = 60 * 3;
}

StageManager::StageManager():
	m_roundState(RoundState::ROUND_START),
	m_roundCount(1),
	m_roundInterval(0),
	m_updateFunc(&StageManager::RoundStartIntervalUpdate),
	m_pEnemyManager(std::make_shared<EnemyManager>()),
	m_pPlayer(nullptr)
{
	// UI�}�l�[�W���ɃX�e�[�W��ݒ�
	UiManager::GetInstance().SetStage(this);
}

StageManager::~StageManager()
{
	// UI�}�l�[�W���ɃX�e�[�W������
	UiManager::GetInstance().DeleteStage();
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

	// �X�e�[�W��ԕ`��
	DrawFormatString(0, 40, GetColor(255, 255, 255), "Round:%d", m_roundCount);
}

void StageManager::OnRoundEnd()
{
	// ���E���h���J�E���g
	m_roundCount++;
	// ���E���h���Ƃ̓�Փx�㏸
	m_pEnemyManager->DiffcultyUp();
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
			// ���E���h��ԕύX
			m_roundState = RoundState::ROUND_END;
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
		// ���E���h��ԕύX
		m_roundState = RoundState::ROUND_ON;
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
		// ���E���h��ԕύX
		m_roundState = RoundState::ROUND_START;
		// ���E���h�I��
		m_updateFunc = &StageManager::RoundStartIntervalUpdate;
		// ���E���h�x��������
		m_roundInterval = 0;
	}
}

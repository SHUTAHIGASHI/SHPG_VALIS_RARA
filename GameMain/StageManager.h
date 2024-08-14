#pragma once
#include <memory>

enum class RoundState
{
	// ���E���h�J�n
	ROUND_START,
	// ���E���h��
	ROUND_ON,
	// ���E���h�I��
	ROUND_END
};

class StageManager
{
public:
	// �R���X�g���N�^
	StageManager();
	// �f�X�g���N�^
	~StageManager();

	// �v���C���[�|�C���^�ݒ�
	void SetPlayer(class Player* Player) { m_pPlayer = Player; }

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// ���E���h��Ԏ擾
	RoundState GetRoundState() { return m_roundState; }
	// ���E���h���擾
	int GetRoundCount() { return m_roundCount; }

private:
	// ���E���h�I�����̏���
	void OnRoundEnd();

	// �����o�֐��|�C���^(���E���h�Ǘ�)
	using m_tUpdateFunc = void (StageManager::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void RoundOnUpdate();				// �ʏ�̍X�V����
	void RoundStartIntervalUpdate();	// �Q�[���X�^�[�g���̍X�V����
	void RoundEndIntervalUpdate();		// �Q�[���I�[�o�[���̍X�V����

private:
	// ���E���h���
	RoundState m_roundState;
	// ���E���h���J�E���g
	int m_roundCount;
	// ���E���h�̒x������
	int m_roundInterval;

	// �X�e�[�W
	std::shared_ptr<class Stage> m_pStage;
	// �G�Ǘ�
	std::shared_ptr<class EnemyManager> m_pEnemyManager;
	// �v���C���[�|�C���^
	class Player* m_pPlayer;
};


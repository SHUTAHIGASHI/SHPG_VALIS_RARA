#pragma once
#include <memory>

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

	// �G�擾
	std::shared_ptr<class EnemyManager> GetEnemy() { return m_pEnemyManager; }

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
	// ���E���h���J�E���g
	int m_roundCount;
	// ���E���h�̒x������
	int m_roundInterval;

	// �G�Ǘ�
	std::shared_ptr<class EnemyManager> m_pEnemyManager;
	// �v���C���[�|�C���^
	class Player* m_pPlayer;
};


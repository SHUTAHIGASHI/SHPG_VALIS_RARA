#pragma once
#include <list>
#include <DxLib.h>



/// <summary>
/// �X�e�[�W�̓G�Ǘ��N���X
/// </summary>
class EnemyManager
{
public:
	// �R���X�g���N�^
	EnemyManager();
	// �f�X�g���N�^
	~EnemyManager();

	// �v���C���[�|�C���^�ݒ�
	void SetPlayer(class Player* Player) { m_pPlayer = Player; }

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// �G�擾
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

private:
	// ���E���h�I�����̏���
	void OnRoundEnd();
	// �G����
	void CreateEnemy();
	// �������W�����_���擾
	VECTOR GetRandomPos();
	// �����_���œG��擾
	class EnemyBase* GetRandomEnemy();

	// �����o�֐��|�C���^(���E���h�Ǘ�)
	using m_tUpdateFunc = void (EnemyManager::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void RoundOnUpdate();     // �ʏ�̍X�V����
	void RoundStartIntervalUpdate();      // �Q�[���X�^�[�g���̍X�V����
	void RoundEndIntervalUpdate();        // �Q�[���I�[�o�[���̍X�V����

private:
	// ���E���h���J�E���g
	int m_roundCount;

	// �G�z��
	std::list<class EnemyBase*> m_pEnemies;
	// �v���C���[�|�C���^
	class Player* m_pPlayer;
};


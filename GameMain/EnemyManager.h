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
	// �X�e�[�W�|�C���^�ݒ�
	void SetStage(class Stage* Stage) { m_pStage = Stage; }

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// ��Փx�A�b�v
	void DiffcultyUp();

	// �G������������
	bool IsEnemyCreateEnd() { return m_isEnemyCreateEnd; }

	// �G�擾
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

private:
	// �G����
	void CreateEnemy();
	// �������W���擾
	VECTOR GetSpawnPos();
	// �����_���œG��擾
	class EnemyBase* GetRandomEnemy();

private:
	// ���������G��
	int m_createEnemyCount;
	// �G�ő吶����
	int m_enemyMaxOnRound;
	// �G�ő哯��������
	int m_enemyMaxOnScreen;
	// �G�̐�����������
	bool m_isEnemyCreateEnd;

	// �G�z��
	std::list<class EnemyBase*> m_pEnemies;
	// �v���C���[�|�C���^
	class Player* m_pPlayer;
	// �X�e�[�W�̃|�C���^
	class Stage* m_pStage;
};


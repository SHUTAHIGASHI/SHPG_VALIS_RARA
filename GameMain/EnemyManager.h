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

	// ��Փx�A�b�v
	void DiffcultyUp();

	// �G������������
	bool IsEnemyCreateEnd() { return m_isEnemyCreateEnd; }

	// �G�擾
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

	// �������钆�S�ʒu�w��
	void SetSpawnCenterPos(VECTOR pos) { m_spawnCenterPos = pos; }

private:
	// �G����
	void CreateEnemy();
	// �������W�����_���擾
	VECTOR GetRandomPos();
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

	// �G�������S���W
	VECTOR m_spawnCenterPos;

	// �G�z��
	std::list<class EnemyBase*> m_pEnemies;
	// �v���C���[�|�C���^
	class Player* m_pPlayer;
};


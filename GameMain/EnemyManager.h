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

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// �G�擾
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

private:
	// �G����
	void CreateEnemy();
	// �������W�����_���擾
	VECTOR GetRandomPos();
	// �����_���œG��擾
	class EnemyBase* GetRandomEnemy();

private:
	// �G�z��
	std::list<class EnemyBase*> m_pEnemies;
};


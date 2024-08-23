#pragma once
#include "ObjectBase.h"
#include <DxLib.h>
#include <string>
#include <list>

namespace
{
	// �����蔻��
	constexpr float kRadius = 48.0f;
	// �ړ����x
	constexpr float kSpeed = 4.0f;
	// �X�e�[�W�O�͈�
	constexpr float kStageLimitZ = 0.0f;
}

class EnemyBase :
    public ObjectBase
{
public:
	EnemyBase(std::string typeName, VECTOR pos);
	virtual ~EnemyBase();

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() override;

	// �q�b�g����
	virtual void OnHit(int damage);

	// �U���̔���
	bool CheckAttackCollision(ObjectBase* obj);
protected:
	// �폜����
	virtual void OnDelete();
	// ���S���̏���
	virtual void OnDead();

protected:
	// �摜�n���h��
	std::list<int> m_hImgs;

	// ���t���[���J�E���g
	int m_frameCount;
	// �`��t���[��
	int m_drawFrame;

	// �U���t���[��
	int m_attackFrame;
	// �U���N���X
	class MeleeAttack* m_pAttack;
};


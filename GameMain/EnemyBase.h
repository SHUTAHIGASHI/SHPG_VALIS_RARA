#pragma once
#include "ObjectBase.h"
#include <string>
#include <DxLib.h>

namespace
{
	// �����蔻��
	constexpr float kRadius = 48.0f;
	// �ړ����x
	constexpr float kSpeed = 6.0f;
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
	// �v���C���[�Ƃ̃q�b�g����
	virtual void OnHitPlayer();

	// �U���̔���
	bool CheckAttackCollision(ObjectBase* obj);
protected:
	// �폜����
	virtual void OnDelete();
	// ���S���̏���
	virtual void OnDead();

protected:
	// �U���t���[��
	int m_attackFrame;

	// �U���N���X
	class MeleeAttack* m_pAttack;
};


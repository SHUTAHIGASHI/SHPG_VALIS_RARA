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
	virtual void Update() override;
	// �`��
	virtual void Draw() override;

	// �q�b�g����
	virtual void OnHit();
	// �v���C���[�Ƃ̃q�b�g����
	virtual void OnHitPlayer();
protected:

	// ���S���̏���
	virtual void OnDead();
};


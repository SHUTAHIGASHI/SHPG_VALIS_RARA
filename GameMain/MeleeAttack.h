#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

class MeleeAttack : public ObjectBase
{
public:
	// �R���X�g���N�^
	MeleeAttack(VECTOR pos, float radius);
	// �f�X�g���N�^
	~MeleeAttack();

	// �`��
	void Draw() override;

private:
};


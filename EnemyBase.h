#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

class EnemyBase :
    public ObjectBase
{
public:
	EnemyBase(VECTOR pos);
	~EnemyBase();

	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �q�b�g����
	void OnHit();
private:
};


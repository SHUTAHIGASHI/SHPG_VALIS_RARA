#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

class Shot : public ObjectBase
{
public:
	Shot(VECTOR pos, VECTOR target);
	~Shot();

	// �X�V
	void Update();
	// �`��
	void Draw();

	// ���e��
	void OnHit();

	// �e���ݒ�
	void SetSpeed(float speed) { m_status.moveSpeed = speed; }
	// �e�̑傫���ݒ�
	void SetScale(float scale);
private:
	// �e�̗L������
	int m_shotTime = 60;
};


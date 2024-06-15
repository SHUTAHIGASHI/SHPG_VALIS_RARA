#pragma once
#include "ObjectBase.h"
#include <DxLib.h>

class Shot : public ObjectBase
{
public:
	Shot(VECTOR pos, VECTOR target);
	Shot(VECTOR pos, ObjectBase* targetObj);
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
	// �������̏�������
	void Init(VECTOR pos);
	// �V���b�g�̍X�V
	void UpdateShotAndTarget();

private:
	// �e�̗L������
	int m_shotTime = 60;
	// �^�[�Q�b�g�I�u�W�F�N�g
	ObjectBase* m_targetObject;
};

#include "ObjectBase.h"

bool ObjectBase::CheckCollision(ObjectBase* obj)
{
	bool result = false;

	// 2�̃I�u�W�F�N�g�̒��S�Ԃ̃x�N�g��
	VECTOR n = VSub(m_status.pos, obj->GetPos());
	// 2�̃I�u�W�F�N�g�̒��S�Ԃ̋���
	float tR = obj->m_status.radius + m_status.radius;
	// 2�̃I�u�W�F�N�g�̒��S�Ԃ̋��������a�̘a��菬�����ꍇ
	if (VSize(n) < tR)
	{
		// �Փ˂��Ă���
		result = true;
	}

	// ���ʂ�Ԃ�
	return result;
}

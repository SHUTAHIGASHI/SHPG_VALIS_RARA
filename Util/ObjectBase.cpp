#include "ObjectBase.h"

bool ObjectBase::CheckCollision(ObjectBase* obj)
{
	// 2�̃I�u�W�F�N�g�̒��S�Ԃ̃x�N�g��
	VECTOR n = VSub(m_status.pos, obj->GetPos());
	// 2�̃I�u�W�F�N�g�̒��S�Ԃ̋���
	float tR = obj->m_status.radius + m_status.radius;
	// 2�̃I�u�W�F�N�g�̒��S�Ԃ̋��������a�̘a��菬�����ꍇ
	if (VSize(n) < tR)
	{
		// �Փ˂��Ă���
		return true;
	}

	// 1�O�̍��W�擾
	VECTOR prevPos = VSub(m_status.pos, m_status.dir);
	auto prevN = VSub(m_status.pos, prevPos);
	auto tSize = VSize(prevN);
	while (tSize >= m_status.radius)
	{
		// 1�O�̍��W���猻�݂̍��W�܂ł̃x�N�g��
		auto prevDir = VSub(m_status.pos, prevPos);
		// �x�N�g���̐��K��
		if (VSize(prevDir) > 0) prevDir = VNorm(prevDir);
		// �x�N�g���̃X�P�[�����O
		prevDir = VScale(prevDir, m_status.radius);
		// 2�̃I�u�W�F�N�g�̒��S�Ԃ̃x�N�g��
		VECTOR n = VSub(prevPos, obj->GetPos());
		// 2�̃I�u�W�F�N�g�̒��S�Ԃ̋��������a�̘a��菬�����ꍇ
		if (VSize(n) < tR)
		{
			// �Փ˂��Ă���
			return true;
		}

		prevPos = VAdd(prevPos, prevDir);
		prevN = VSub(m_status.pos, prevPos);
		tSize = VSize(prevN);
	}

	// �Փ˂��Ă��Ȃ�
	return false;
}

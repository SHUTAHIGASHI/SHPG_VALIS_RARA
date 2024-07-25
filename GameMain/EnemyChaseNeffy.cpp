#include "EnemyChaseNeffy.h"
#include "ObjectBase.h"

EnemyChaseNeffy::EnemyChaseNeffy(ObjectBase* target, VECTOR pos):
	EnemyBase("chino", pos)
{
	m_pTarget = target;
}

EnemyChaseNeffy::~EnemyChaseNeffy()
{
	m_pTarget = nullptr;
}

void EnemyChaseNeffy::Update()
{
	// �^�[�Q�b�g�̍��W�擾
	auto targetPos = VGet(m_pTarget->GetPos().x, 0.0f, m_pTarget->GetPos().z);
	// �v���C���[�̍��W�܂ł̃x�N�g�������߂�
	m_status.dir = VSub(targetPos, m_status.pos);
	// ���K��
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// �ړ����x�w��
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	// �ړ�
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}

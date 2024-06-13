#include "Shot.h"
#include "EffekseerManager.h"

namespace
{
	// �e�̑��x
	constexpr float kShotSpeed = 160.0f;
	// �e�̔��a
	constexpr float kShotRadius = 64.0f;
	// �e�̗L������
	constexpr int kShotTime = 60 * 15;
}

Shot::Shot(VECTOR pos, VECTOR target):
	ObjectBase(),
	m_shotTime()
{
	// �V���b�g�̏�����
	m_status.moveSpeed = kShotSpeed;
	m_status.radius = kShotRadius;
	// �L������
	m_shotTime = kShotTime;
	// �V���b�g�̈ʒu�ƕ���
	m_status.pos = pos;
	m_status.dir = VSub(target, pos);
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
}

Shot::~Shot()
{
	// �V���b�g�̍폜
	EffekseerManager::GetInstance().StopEffectTargetObj(this);
}

void Shot::Update()
{
	// �e�̗L������
	m_shotTime--;
	if (m_shotTime <= 0)
	{
		// �L�����Ԃ��I��������폜
		m_status.isEnabled = false;
	}
	// �e�̈ړ�
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}

void Shot::Draw()
{
	// DrawSphere3D(m_status.pos, m_status.radius, 16, 0xe3e3e3, 0xe3e3e3, false);
}

void Shot::OnHit()
{
	// �����������̏���
	m_status.isEnabled = false;
}

void Shot::SetScale(float scale)
{
	// �e�̊g�嗦��ύX
	if (scale > 0)
	{
		m_status.radius = kShotRadius * scale;
	}
	else
	{
		m_status.radius = kShotRadius;
	}
}

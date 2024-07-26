#include "Shot.h"
#include "Load.h"

using namespace ShotParam;

Shot::Shot(VECTOR pos, VECTOR target):
	ObjectBase(),
	m_shotTime(),
	m_targetObject(nullptr)
{
	// �V���b�g�̏�����
	Init(pos);
	m_status.dir = VSub(target, m_status.pos);
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
}

Shot::Shot(VECTOR pos, ObjectBase* targetObj):
	ObjectBase(),
	m_shotTime(),
	m_targetObject(targetObj)
{
	// �V���b�g�̏�����
	Init(pos);
	// �V���b�g�ǔ���X�V
	UpdateShotAndTarget();
}

Shot::~Shot()
{
	// �摜�폜
	m_status.hImg = -1;
}

void Shot::Update()
{
	// �V���b�g�̍X�V
	UpdateShotAndTarget();

	// �e�̗L������
	m_shotTime--;
	if (m_shotTime <= 0)
	{
		// �L�����Ԃ��I��������폜
		m_status.isEnabled = false;
	}
}

void Shot::Draw()
{
	// �摜�`��
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
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

void Shot::Init(VECTOR pos)
{
	// �摜�ǂݍ���
	m_status.hImg = Load::GetInstance().GetHandle("shot");
	// �V���b�g�̏�����
	m_status.moveSpeed = kShotSpeed;
	m_status.radius = kShotRadius;
	m_status.scale = Game::kBaseScale;
	// �L������
	m_shotTime = kShotTime;
	// �V���b�g�̈ʒu�ƕ���
	m_status.pos = pos;
}

void Shot::UpdateShotAndTarget()
{
	// �V���b�g�ǔ���X�V
	if (m_targetObject != nullptr)
	{
		if (m_targetObject->IsEnabled())
		{
			m_status.dir = VSub(m_targetObject->GetPos(), m_status.pos);
			if(VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
			m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
		}
	}
	
	// �e�̈ړ�
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}

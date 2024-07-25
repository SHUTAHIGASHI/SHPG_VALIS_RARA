#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"

EnemyBase::EnemyBase(std::string typeName, VECTOR pos):
	ObjectBase()
{
	// ���a�ݒ�
	m_status.radius = kRadius;
	// �ړ����x�ݒ�
	m_status.moveSpeed = kSpeed;
	// �g�嗦�ݒ�
	m_status.scale = Game::kBaseScale;
	// ���W�ݒ�
	m_status.pos = pos;
	// �摜�ݒ�
	m_status.hImg = Load::GetInstance().GetHandle(typeName);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
	// �ړ�
	m_status.dir = VGet(0.0f, 0.0f, -1.0f);
	m_status.pos = VAdd(m_status.pos, VScale(m_status.dir, m_status.moveSpeed));

	// ��ʊO�ɏo����
	if (m_status.pos.z < kStageLimitZ)
	{
		m_status.isEnabled = false;
	}
}

void EnemyBase::Draw()
{
	// �摜�`��
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit()
{	
	// �����������̏���
	m_status.isEnabled = false;
	// �_���[�W���Đ�
	SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
}

void EnemyBase::OnHitPlayer()
{
	// �����������̏���
	m_status.isEnabled = false;
	// �_���[�W���Đ�
	SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
}

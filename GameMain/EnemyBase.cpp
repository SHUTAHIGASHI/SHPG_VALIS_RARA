#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"
#include "SoundManager.h"
#include "UiManager.h"

namespace
{
	// ��̗�
	const int kBaseHp = 30;
}

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
	m_status.hImg = Load::GetInstance().GetImageHandle(typeName);
	// �̗͐ݒ�
	m_status.hp = kBaseHp;

	// UI�ɓG�̗̑͂�o�^
	UiManager::GetInstance().AddUIBar(this);
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
	// ���`��
	DrawSphere3D(m_status.pos, m_status.radius, 32, 0xffffff, 0xffffff, false);
}

void EnemyBase::OnHit(int damage)
{	
	// �̗͂����炷
	m_status.hp -= damage;
	if(m_status.hp <= 0)
	{
		m_status.hp = 0;
		// �̗͂�0�ȉ��ɂȂ�����
		OnDead();
	}
	else
	{
		// �_���[�W���Đ�
		SoundManager::GetInstance().Play3DSound(SoundType::enemyDamage, m_status.pos);
	}
}

void EnemyBase::OnHitPlayer()
{
	// todo �v���C���[�ɓ����������̏���
}

void EnemyBase::OnDelete()
{
	// UI����G�̗̑͂��폜
	UiManager::GetInstance().DeleteUIBar(this);
}

void EnemyBase::OnDead()
{
	// �̗͂�0�ȉ��ɂȂ�����
	m_status.isEnabled = false;
	// ���S���Đ�
	SoundManager::GetInstance().Play3DSound(SoundType::enemyDeath, m_status.pos);
	// �폜����
	this->OnDelete();
}

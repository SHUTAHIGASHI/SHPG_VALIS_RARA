#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"

namespace
{

}

EnemyBase::EnemyBase(VECTOR pos)
{
	// �g�嗦�ݒ�
	m_status.scale = Game::kBaseScale;
	// ���W�ݒ�
	m_status.pos = pos;
	// �摜�ݒ�
	m_status.hImg = Load::GetInstance().GetHandle("enemy");
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
	// 3D�`��
	//DrawSphere3D(m_status.pos, 10.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	// �摜�`��
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit()
{
	// �����������̏���
	m_status.isEnabled = false;
}

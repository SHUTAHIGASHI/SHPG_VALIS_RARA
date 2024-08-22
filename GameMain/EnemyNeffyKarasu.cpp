#include "EnemyNeffyKarasu.h"
#include "ObjectBase.h"
#include "SoundManager.h"
#include "MeleeAttack.h"

namespace
{
	// �U������̔��a
	constexpr float kAttackRadius = 120.0f;
	// �U���t���[����
	constexpr int kAttackFrame = 60;
}

EnemyNeffyKarasu::EnemyNeffyKarasu(ObjectBase* target, VECTOR pos):
	EnemyBase("neffyKarasu", pos),
	m_updateFunc(&EnemyNeffyKarasu::NormalUpdate)
{
	m_pTarget = target;
	m_status.pos.y = 120.0f;
}

EnemyNeffyKarasu::~EnemyNeffyKarasu()
{
	// �^�[�Q�b�g�̉��
	m_pTarget = nullptr;
}

void EnemyNeffyKarasu::Update()
{
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)();

	// �G�l�~�[�T�E���h�Đ�
	if (!SoundManager::GetInstance().IsPlaying(SoundType::enemyBirdVoice))
	{
		//SoundManager::GetInstance().PlaySE(SoundType::enemyBirdVoice);
		SoundManager::GetInstance().Play3DSound(SoundType::enemyBirdVoice, m_status.pos);
	}
}

void EnemyNeffyKarasu::NormalUpdate()
{
	// �^�[�Q�b�g�̍��W�擾
	auto targetPos = VGet(m_pTarget->GetPos().x, m_status.pos.y, m_pTarget->GetPos().z);
	// �v���C���[�̍��W�܂ł̃x�N�g�������߂�
	m_status.dir = VSub(targetPos, m_status.pos);
	// �v���C���[�Ƃ̋��������ȉ��Ȃ�U����ԂɑJ��
	if (VSize(m_status.dir) < kAttackRadius)
	{
		// �U���t���[������ݒ�
		m_attackFrame = kAttackFrame;
		// �U����ԂɑJ��
		m_updateFunc = &EnemyNeffyKarasu::AttackUpdate;
	}

	// ���K��
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// �ړ����x�w��
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	// �ړ�
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}

void EnemyNeffyKarasu::AttackUpdate()
{
	// �^�[�Q�b�g�̍��W�擾
	auto targetPos = VGet(m_pTarget->GetPos().x, m_status.pos.y, m_pTarget->GetPos().z);
	// �v���C���[�̍��W�܂ł̃x�N�g�������߂�
	m_status.dir = VSub(targetPos, m_status.pos);
	// ���K��
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// �ړ����x�w��
	m_status.dir = VScale(m_status.dir, kAttackRadius);
	// �U������̍��W��ݒ�
	VECTOR attackPos = VAdd(m_status.pos, m_status.dir);
	// �U������̐���
	m_pAttack = new MeleeAttack(attackPos, kAttackRadius);

	// �U���t���[������0�ȉ��Ȃ�ʏ��ԂɑJ��
	if (m_attackFrame <= 0)
	{
		// �U������̉��
		delete m_pAttack;
		m_pAttack = nullptr;
		// �ʏ��ԂɑJ��
		m_updateFunc = &EnemyNeffyKarasu::NormalUpdate;
	}
	else
	{
		// �U���t���[���������炷
		m_attackFrame--;
	}
}

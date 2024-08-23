#include "EnemyNeffy.h"
#include "ObjectBase.h"
#include "SoundManager.h"
#include "MeleeAttack.h"
#include "Stage.h"

namespace
{
	// �U������̔��a
	constexpr float kAttackRadius = 64.0f;
	// �U���t���[����
	constexpr int kAttackFrame = 60;
}

EnemyNeffy::EnemyNeffy(ObjectBase* target, VECTOR pos, class Stage* stage) :
	EnemyBase("neffy", pos),
	m_updateFunc(&EnemyNeffy::NormalUpdate),
	m_pStage(stage)
{
	m_pTarget = target;
}

EnemyNeffy::~EnemyNeffy()
{
	// �^�[�Q�b�g�̉��
	m_pTarget = nullptr;
}

void EnemyNeffy::Update()
{
	// ���t���[���J�E���g
	m_frameCount++;

	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)();

	// �G�l�~�[�T�E���h�Đ�
	if (!SoundManager::GetInstance().IsPlaying3DSound(this))
	{
		SoundManager::GetInstance().Play3DSound(SoundType::enemyVoice, this);
	}
}

void EnemyNeffy::Draw()
{
	// �摜�`��
	if (m_drawFrame % 2 == 0)
	{
		DrawBillboard3D(m_status.pos, 0.5f, 0.8f, m_status.scale, 0.0f, m_hImgs.front(), true);
	}
	else
	{
		DrawBillboard3D(m_status.pos, 0.5f, 0.8f, m_status.scale, 0.0f, m_hImgs.back(), true);
	}

	// �`��t���[����i�߂�
	if (m_frameCount % 20 == 0)
	{
		m_drawFrame++;
	}
}

void EnemyNeffy::NormalUpdate()
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
		m_updateFunc = &EnemyNeffy::AttackUpdate;
	}

	// ���K��
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	// �ړ����x�w��
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	// �ړ�
	VECTOR nextPos = VAdd(m_status.pos, m_status.dir);
	// �ړ��\���̔���
	if (CheckCanMove(nextPos))
	{
		m_status.pos = nextPos;
	}
	else
	{
		// �ړ��s�\�ȏꍇ�̓����_���ňړ�������ύX
		m_status.dir = VGet(static_cast<float>(GetRand(100) - 50), 0.0f, static_cast<float>(GetRand(100) - 50));
		if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
		m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	}
}

void EnemyNeffy::AttackUpdate()
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
		m_updateFunc = &EnemyNeffy::NormalUpdate;
	}
	else
	{
		// �U���t���[���������炷
		m_attackFrame--;
	}
}

bool EnemyNeffy::CheckCanMove(VECTOR nextPos)
{
	// �ړ���̃^�C���ԍ����擾
	int tileX = NULL;
	int tileZ = NULL;
	m_pStage->GetTile(nextPos, tileX, tileZ);

	// �ړ���̃^�C�����ǂ���Ȃ��ꍇ
	if (m_pStage->GetStageData()[tileZ][tileX] == StageTile::WL)
	{
		// �ړ��s�\
		return false;
	}
	else if (m_pStage->GetStageData()[tileZ][tileX] == StageTile::F1)
	{
		// �ړ��s�\
		return false;
	}
	else if (m_pStage->GetStageData()[tileZ][tileX] == StageTile::F2)
	{
		// �ړ��s�\
		return false;
	}

	return true;
}

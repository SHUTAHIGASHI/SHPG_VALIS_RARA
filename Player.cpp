#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Load.h"
#include "CameraManager.h"

namespace
{
	// �摜�g�嗦
	constexpr float kScale = 100.0f;
	// ���b�N�I���͈�
	constexpr float kLockRange = 50.0f;
	// �V���b�g�A�ˑ��x
	constexpr int kShotRate = 10;
}

Player::Player():
	ObjectBase(),
	m_hLockCursorImg(-1),
	m_shotDelay(kShotRate),
	m_isLockOn(false),
	m_cursorPos(Game::kVecZero),
	m_lockObjPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pEnemyManager(nullptr)
{
	// �摜�ǂݍ���
	m_status.hImg = Load::GetInstance().GetHandle("player");
	m_hLockCursorImg = Load::GetInstance().GetHandle("lockCursor");
	// �摜�g�嗦�ݒ�
	m_status.scale = kScale;
}

Player::~Player()
{
	// �摜�폜
	m_status.hImg = -1;
	m_hLockCursorImg = -1;
}

void Player::Init()
{
}

void Player::Update(const InputState& input)
{
	// �J�[�\���X�V
	UpdateCursor(input);

	// �V���b�g�Ǘ�
	ControllShot(input);
	// �V���b�g�X�V
	UpdateShot();
}

void Player::Draw()
{
	// �V���b�g�`��
	for (auto& shot : m_pShots)
	{
		shot->Draw();
	}

	// 2D�`��
	Draw2D();
}

void Player::ControllShot(const InputState& input)
{
	// �V���b�g�A�ˑ��x
	m_shotDelay--;
	if (m_shotDelay < 0)
	{
		m_shotDelay = 0;
	}

	// �ˌ��{�^���������ꂽ��
	if (input.IsPressed(InputType::shot))
	{
		if (m_shotDelay <= 0)
		{
			// �V���b�g����
			CreateShot();
		}
	}

	// �X�y�V�����V���b�g�{�^���������ꂽ��
	if (input.IsTriggered(InputType::sprShot))
	{
		// �X�y�V�����V���b�g����
		CreateSprShot();
	}
}

void Player::CreateShot()
{
	// �^�[�Q�b�g�ʒu
	VECTOR targetPos = ConvScreenPosToWorldPos(VGet(m_cursorPos.x, m_cursorPos.y, 0.0f));
	// ���e�n�_�̍��W
	VECTOR targetDir = VSub(targetPos, m_pCamera->GetPos());
	if (VSize(targetDir) > 0) targetDir = VNorm(targetDir);
	targetDir = VScale(targetDir, ShotParam::kShotSpeed);
	targetPos = VAdd(m_pCamera->GetPos(), VScale(targetDir, ShotParam::kShotTime));
	// �V���b�g����
	m_pShots.push_back(new Shot(m_status.pos, targetPos));

	// �V���b�g�A�ˑ��x������
	if (m_shotDelay <= 0)
	{
		m_shotDelay = kShotRate;
	}
}

void Player::CreateSprShot()
{
	// �V���b�g����
	m_pShots.push_back(new Shot(m_status.pos, m_pTargetObj->GetPos()));

	// �V���b�g�A�ˑ��x������
	if (m_shotDelay <= 0)
	{
		m_shotDelay = kShotRate;
	}
}

void Player::UpdateShot()
{
	// �V���b�g�X�V
	for (auto& shot : m_pShots)
	{
		shot->Update();
		// �G�Ƃ̓����蔻��
		for (auto& obj : m_pEnemyManager->GetEnemies())
		{
			if (shot->CheckCollision(obj))
			{
				// �G�q�b�g����
				obj->OnHit();
				// �V���b�g�폜
				shot->OnHit();
			}
		}
	}

	// �V���b�g�폜
	m_pShots.remove_if([](Shot* shot) {return !shot->IsEnabled(); });
}

void Player::UpdateCursor(const InputState& input)
{
	// �J�[�\�����W�擾
	m_cursorPos.x = input.GetMousePosX();
	m_cursorPos.y = input.GetMousePosY();

	// ���W�Ɣ��胊�Z�b�g
	m_lockObjPos = Game::kVecZero;
	m_isLockOn = false;
	// ���b�N�I���J�[�\�����W�擾
	for (auto& obj : m_pEnemyManager->GetEnemies())
	{
		if (obj->IsEnabled())
		{
			VECTOR objPos = obj->GetPos();
			VECTOR screenPos = ConvWorldPosToScreenPos(objPos);

			// �J�[�\���ƃI�u�W�F�N�g�̋������v�Z
			float distance = VSize(VSub(screenPos, m_cursorPos));

			// �J�[�\���ƃI�u�W�F�N�g�̋��������͈͓��Ȃ�
			if (distance < kLockRange)
			{
				// ���b�N�I���J�[�\�����W�ݒ�
				m_lockObjPos = objPos;
				// ���b�N�I���t���OON
				m_isLockOn = true;
				// ���b�N�I���I�u�W�F�N�g�ݒ�
				m_pTargetObj = obj;
				break;
			}
		}
	}
}

void Player::Draw2D()
{
	// �摜�`��
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
	// ���b�N�I���J�[�\���`��
	if (m_isLockOn)
	{
		VECTOR lockCursorPos = ConvWorldPosToScreenPos(m_lockObjPos);
		DrawRotaGraphF(lockCursorPos.x, lockCursorPos.y, 1.0f, 0.0f, m_hLockCursorImg, true);
	}
}

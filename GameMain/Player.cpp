#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Load.h"
#include "CameraManager.h"
#include "SoundManager.h"

namespace
{
	// �摜�g�嗦
	constexpr float kScale = 100.0f;

	// �ړ����x
	constexpr float kPlayerMoveSpeed = 2.0f;

	// �v���C���[���_�ړ����x
	constexpr float kPovMoveSpeed = 4.0f;
	// �v���C���[����J�����܂ł̋���
	constexpr float kLookPosDistance = 120.0f;

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
	m_playerAngleAxisX(0.0f),
	m_playerAngleAxisY(0.0f),
	m_cursorPos(Game::kVecZero),
	m_lockObjPos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pEnemyManager(nullptr),
	m_pCamera(nullptr)
{
	// �摜�ǂݍ���
	m_status.hImg = Load::GetInstance().GetHandle("player");
	m_hLockCursorImg = Load::GetInstance().GetHandle("lockCursor");
	// �摜�g�嗦�ݒ�
	m_status.scale = kScale;
	// �ړ����x�ݒ�
	m_status.moveSpeed = kPlayerMoveSpeed;
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
	// �ړ�����
	ControllMove(input);
	// ���_����
	ControllView(input);
	// ���_�X�V
	UpdateView();

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

	// ���[�U�[�`��
	DrawLine3D(m_status.pos, m_targetPos, 0xff0000);
	// 2D�`��
	Draw2D();

	DrawSphere3D(m_status.pos, 10.0f, 16, 0xff0000, 0xff0000, true);
	DrawSphere3D(m_status.lookPos, 10.0f, 16, 0xff0000, 0xff0000, true);
}

void Player::ControllView(const InputState& input)
{
	// �E���_�ړ�
	if (input.IsPressed(InputType::lookRight))
	{
		m_playerAngleAxisY += kPovMoveSpeed;
	}
	// �����_�ړ�
	else if (input.IsPressed(InputType::lookLeft))
	{
		m_playerAngleAxisY += -kPovMoveSpeed;
	}
	// �㎋�_�ړ�
	if (input.IsPressed(InputType::lookUp))
	{
		m_playerAngleAxisX += -kPovMoveSpeed;
	}
	// �����_�ړ�
	else if (input.IsPressed(InputType::lookDown))
	{
		m_playerAngleAxisX += kPovMoveSpeed;
	}
}

void Player::UpdateView()
{
	// �����_�������̏���
	{
		// �����_�̊p�x�̌��E���w��
		if (m_playerAngleAxisY > 360.0f)
		{
			m_playerAngleAxisY = 0;
		}
		if (m_playerAngleAxisY < 0)
		{
			m_playerAngleAxisY = 360.0f;
		}

		// �p�x�����W�A���ɕϊ�
		float rad = m_playerAngleAxisY * (DX_PI_F / 180.0f);

		// ���S�ʒu���甼�a�����ƂɋO�����v�Z
		m_status.lookDir.x = sin(rad) * kLookPosDistance;
		m_status.lookDir.z = cos(rad) * kLookPosDistance;

		// ���S�ʒu�̑��
		m_status.lookPos = m_status.pos;
		// �x�N�g�����ʒu�ɉ��Z
		m_status.lookPos = VAdd(m_status.lookPos, m_status.lookDir);
	}

	// �����_�c�����̏���
	{
		// �����_�̊p�x�̌��E���w��
		if (m_playerAngleAxisX > 180.0f)
		{
			m_playerAngleAxisX = 180.0f;
		}
		if (m_playerAngleAxisX < 0.0f)
		{
			m_playerAngleAxisX = 0.0f;
		}

		// �p�x�����W�A���ɕϊ�
		float rad = m_playerAngleAxisX * (DX_PI_F / 180.0f);

		// ���S�ʒu���甼�a�����ƂɋO�����v�Z
		m_status.lookDir.y = cos(rad) * kLookPosDistance;

		// �x�N�g�����ʒu�ɉ��Z
		m_status.lookPos = VAdd(m_status.lookPos, m_status.lookDir);
	}

	// �J�����ʒu�ݒ�
	m_pCamera->SetPosAndTarget(m_status.pos, m_status.lookPos);
}

void Player::ControllMove(const InputState& input)
{
	VECTOR moveDir = Game::kVecZero;

	// �O���ړ�����
	if (input.IsPressed(InputType::moveForward))
	{
		moveDir = VSub(m_status.lookPos, m_status.pos);
		moveDir.y = 0.0f;
		if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
		moveDir = VScale(moveDir, m_status.moveSpeed);
		m_status.pos = VAdd(m_status.pos, moveDir);
	}
	// ����ړ�����
	if (input.IsPressed(InputType::moveBehind))
	{
		moveDir = VSub(m_status.lookPos, m_status.pos);
		moveDir.y = 0.0f;
		if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
		moveDir = VScale(moveDir, -m_status.moveSpeed);
		m_status.pos = VAdd(m_status.pos, moveDir);
	}
	// �E�ړ�����
	if (input.IsPressed(InputType::moveRight))
	{
		moveDir = VSub(m_status.lookPos, m_status.pos);
		moveDir.y = 0.0f;
		if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
		moveDir = VScale(moveDir, m_status.moveSpeed);
		// �i�s�����E��90�x��]
		MATRIX mtx = MGetRotY(DX_PI_F / 2);
		moveDir = VTransform(moveDir, mtx);
		m_status.pos = VAdd(m_status.pos, moveDir);
	}
	// ���ړ�����
	if (input.IsPressed(InputType::moveLeft))
	{
		moveDir = VSub(m_status.lookPos, m_status.pos);
		moveDir.y = 0.0f;
		if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
		moveDir = VScale(moveDir, m_status.moveSpeed);
		// �i�s��������90�x��]
		MATRIX mtx = MGetRotY(-DX_PI_F / 2);
		moveDir = VTransform(moveDir, mtx);
		m_status.pos = VAdd(m_status.pos, moveDir);
	}

}

void Player::ControllShot(const InputState& input)
{
	// �^�[�Q�b�g�ʒu
	VECTOR targetPos = ConvScreenPosToWorldPos(VGet(m_cursorPos.x, m_cursorPos.y, 0.0f));
	// ���e�n�_�̍��W
	VECTOR targetDir = VSub(targetPos, m_pCamera->GetPos());
	if (VSize(targetDir) > 0) targetDir = VNorm(targetDir);
	targetDir = VScale(targetDir, ShotParam::kShotSpeed);
	m_targetPos = VAdd(m_pCamera->GetPos(), VScale(targetDir, ShotParam::kShotTime));

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
		if (m_isLockOn)
		{
			// �X�y�V�����V���b�g����
			CreateSprShot();
		}
	}

	// �V���b�g�T�E���h�Đ�
	SoundManager::GetInstance().PlaySE(SoundType::shot);
}

void Player::CreateShot()
{
	// �V���b�g����
	m_pShots.push_back(new Shot(m_status.pos, m_targetPos));

	// �V���b�g�A�ˑ��x������
	if (m_shotDelay <= 0)
	{
		m_shotDelay = kShotRate;
	}
}

void Player::CreateSprShot()
{
	// �V���b�g����
	m_pShots.push_back(new Shot(m_status.pos, m_pTargetObj));

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

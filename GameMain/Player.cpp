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
	constexpr float kPlayerMoveSpeed = 12.0f;
	// �_�b�V����
	constexpr float kDashRate = 2.0f;
	// �d��
	constexpr float kGravity = 0.5f;
	// �W�����v��
	constexpr float kJumpPower = 12.0f;

	// �}�E�X���x
	constexpr float kMouseSensitivity = 0.09f;
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
	m_hCursorImg(-1),
	m_hLockCursorImg(-1),
	m_shotDelay(kShotRate),
	m_isLockOn(false),
	m_playerAngleY(0.0f),
	m_playerAngleX(0.0f),
	m_lockObjPos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pEnemyManager(nullptr),
	m_pCamera(nullptr)
{
	// �摜�ǂݍ���
	m_hFpsHand = Load::GetInstance().GetHandle("fpsHand");
	m_hCursorImg = Load::GetInstance().GetHandle("cursor");
	m_hLockCursorImg = Load::GetInstance().GetHandle("lockCursor");
	// �摜�T�C�Y�擾
	GetGraphSize(m_hFpsHand, &m_HandSizeX, &m_HandSizeY);
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
	// 2D�`��
	Draw2D();
}

void Player::OnHit()
{
	// �J�����h�ꏈ��
	m_pCamera->OnScreenQuake();
}

void Player::ControllView(const InputState& input)
{
	m_playerAngleX += input.GetMouseMoveX() * kMouseSensitivity;
	m_playerAngleY -= input.GetMouseMoveY() * kMouseSensitivity;

	// �E���_�ړ�
	if (input.IsPressed(InputType::lookRight))
	{
		m_playerAngleX += kPovMoveSpeed;
	}
	// �����_�ړ�
	else if (input.IsPressed(InputType::lookLeft))
	{
		m_playerAngleX += -kPovMoveSpeed;
	}
	// �㎋�_�ړ�
	if (input.IsPressed(InputType::lookUp))
	{
		m_playerAngleY += kPovMoveSpeed;
	}
	// �����_�ړ�
	else if (input.IsPressed(InputType::lookDown))
	{
		m_playerAngleY += -kPovMoveSpeed;
	}
}

void Player::UpdateView()
{
	// �����_�������̏���
	{
		// �����_�̊p�x�̌��E���w��
		if (m_playerAngleX > 360.0f)
		{
			m_playerAngleX = 0;
		}
		if (m_playerAngleX < 0)
		{
			m_playerAngleX = 360.0f;
		}

		// �p�x�����W�A���ɕϊ�
		float rad = m_playerAngleX * (DX_PI_F / 180.0f);

		// ���S�ʒu���甼�a�����ƂɋO�����v�Z
		m_status.lookDir.x = sin(rad);
		m_status.lookDir.z = cos(rad);
	}

	// �����_�c�����̏���
	{
		// �����_�̊p�x�̌��E���w��
		if (m_playerAngleY > 89.0f)
		{
			m_playerAngleY = 89.0f;
		}
		if (m_playerAngleY < -89.0f)
		{
			m_playerAngleY = -89.0f;
		}

		// �p�x�����W�A���ɕϊ�
		float rad = m_playerAngleY * (DX_PI_F / 180.0f);

		// ���S�ʒu���甼�a�����ƂɋO�����v�Z
		m_status.lookDir.y = tan(rad);
	}

	// ���K��
	if (VSize(m_status.lookDir) > 0) m_status.lookDir = VNorm(m_status.lookDir);
	m_status.lookDir = VScale(m_status.lookDir, kLookPosDistance);
	// ���S�ʒu�̑��
	m_status.lookPos = m_status.pos;
	// �x�N�g�����ʒu�ɉ��Z
	m_status.lookPos = VAdd(m_status.lookPos, m_status.lookDir);

	// �J�����ʒu�ݒ�
	m_pCamera->SetPosAndTarget(m_status.pos, m_status.lookPos);
}

void Player::ControllMove(const InputState& input)
{
	// �n�ʔ���`�F�b�N
	if (m_status.pos.y <= 0.0f)
	{
		// �n�ʔ���
		m_status.isGround = true;
	}
	else
	{
		// �󒆔���
		m_status.isGround = false;
	}

	// �ړ��x�N�g��
	VECTOR moveDir = Game::kVecZero;

	// �_�b�V������
	if (input.IsPressed(InputType::dash))
	{
		m_status.moveSpeed = kPlayerMoveSpeed * kDashRate;
	}
	else
	{
		m_status.moveSpeed = kPlayerMoveSpeed;
	}

	// �O���ړ�����
	if (input.IsPressed(InputType::moveForward))
	{
		VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
		tempDir.y = 0.0f;
		moveDir = VAdd(moveDir, tempDir);
	}
	// ����ړ�����
	if (input.IsPressed(InputType::moveBehind))
	{
		VECTOR tempDir = VSub(m_status.pos, m_status.lookPos);
		tempDir.y = 0.0f;
		moveDir = VAdd(moveDir, tempDir);
	}
	// �E�ړ�����
	if (input.IsPressed(InputType::moveRight))
	{
		VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
		tempDir.y = 0.0f;
		// �i�s�����E��90�x��]
		MATRIX mtx = MGetRotY(DX_PI_F / 2);
		tempDir = VTransform(tempDir, mtx);
		moveDir = VAdd(moveDir, tempDir);
	}
	// ���ړ�����
	if (input.IsPressed(InputType::moveLeft))
	{
		VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
		tempDir.y = 0.0f;
		// �i�s��������90�x��]
		MATRIX mtx = MGetRotY(-DX_PI_F / 2);
		tempDir = VTransform(tempDir, mtx);
		moveDir = VAdd(moveDir, tempDir);
	}
	// �ʏ�̈ړ�����
	if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
	moveDir = VScale(moveDir, m_status.moveSpeed);
	m_status.pos = VAdd(m_status.pos, moveDir);

	// �W�����v����
	if (m_status.isGround)
	{
		// �W�����v�͏�����
		m_status.jumpPower = 0.0f;
		if (input.IsTriggered(InputType::jump))
		{
			// �W�����v����
			m_status.jumpPower += kJumpPower;
		}
	}
	else
	{
		// �d�͉��Z
		m_status.jumpPower -= kGravity;
	}
	// �W�����v���������W�ɉ��Z
	m_status.pos.y += m_status.jumpPower;
}

void Player::ControllShot(const InputState& input)
{
	// �^�[�Q�b�g�ʒu
	VECTOR targetPos = m_status.lookPos;
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
}

void Player::CreateShot()
{
	// �V���b�g�T�E���h�Đ�
	SoundManager::GetInstance().PlaySE(SoundType::shot);

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
	// �V���b�g�T�E���h�Đ�
	SoundManager::GetInstance().PlaySE(SoundType::sprShot);

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
			float distance = VSize(VSub(screenPos, Game::kScreenCenter));

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
	// �N���X�w�A�`��
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0f, 0.0f, m_hCursorImg, true);
	// ���b�N�I���J�[�\���`��
	if (m_isLockOn)
	{
		VECTOR lockCursorPos = ConvWorldPosToScreenPos(m_lockObjPos);
		DrawRotaGraphF(lockCursorPos.x, lockCursorPos.y, 1.0f, 0.0f, m_hLockCursorImg, true);
	}
	// FPS�n���h�`��
	DrawRotaGraphF(static_cast<float>(Game::kScreenWidth - (m_HandSizeX * 10.0f)),
		static_cast<float>(Game::kScreenHeight - (m_HandSizeY * 10.0f) / 2),
		10.0f, 0.0f, m_hFpsHand, true);
}

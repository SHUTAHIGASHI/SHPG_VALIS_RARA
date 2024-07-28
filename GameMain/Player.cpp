#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Load.h"
#include "CameraManager.h"
#include "SoundManager.h"
#include "UiManager.h"

namespace
{
	// �摜�g�嗦
	constexpr float kScale = 100.0f;

	// �ړ����x
	constexpr float kPlayerMoveSpeed = 10.0f;
	// �_�b�V�����x��
	constexpr float kDashRate = 1.5f;
	// �X���C�f�B���O���x��
	constexpr float kSlideRate = 2.5f;
	// �d��
	constexpr float kGravity = 0.5f;
	// �W�����v��
	constexpr float kJumpPower = 12.0f;

	// �p�����Ƃ̍���
	constexpr float kStandHeight = 0.0f;
	constexpr float kCrouchHeight = -70.0f;

	// �X���C�f�B���O����
	constexpr int kSlideTime = 20;

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
	// �V���b�g�̃_���[�W
	constexpr int kShotDamage = 10;

	// �̗�
	constexpr int kMaxHp = 100;
	// ���G����
	constexpr int kInvTime = 60;
}

Player::Player():
	ObjectBase(),
	m_posture(PostureType::stand),
	m_hFpsHand(-1),
	m_hCursorImg(-1),
	m_hLockCursorImg(-1),
	m_HandSizeX(0),
	m_HandSizeY(0),
	m_shotDelay(kShotRate),
	m_slideTime(0),
	m_invTime(0),
	m_isMove(false),
	m_isDash(false),
	m_isLockOn(false),
	m_eyeHeight(kStandHeight),
	m_playerAngleY(0.0f),
	m_playerAngleX(0.0f),
	m_slideVec(Game::kVecZero),
	m_lockObjPos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pEnemyManager(nullptr),
	m_pCamera(nullptr)
{
}

Player::~Player()
{
	// �摜�폜
	m_status.hImg = -1;
	m_hLockCursorImg = -1;
}

void Player::Init()
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
	// �̗͐ݒ�
	m_status.hp = kMaxHp;
	// ���_�X�V
	UpdateView();
}

void Player::Update(const InputState& input)
{
	// ���G���Ԍ���
	if (m_invTime > 0) m_invTime--;

	// �ړ�����
	ControllMove(input);
	// �p���X�V
	UpdatePosture(input);

	// ���_����
	ControllView(input);
	// ���_�X�V
	UpdateView();

	// �ړ����̉�ʗh�ꏈ��
	if (m_isMove)
	{
		m_pCamera->OnMoveQuake();
	}

	// �J�[�\���X�V
	UpdateCursor(input);
	// �V���b�g�Ǘ�
	ControllShot(input);
	// �V���b�g�X�V
	UpdateShot();

	// UI�Ƀv���C���[���W�𑗐M
	UiManager::GetInstance().SetPlayerPos(m_status.pos);
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
	// ���G���Ԓ��Ȃ�
	if (m_invTime > 0) return;

	// �̗͌���
	m_status.hp -= 10;
	// �J�����h�ꏈ��
	m_pCamera->OnDamageQuake();
	// ���G���Ԑݒ�
	m_invTime = kInvTime;
}

void Player::ControllView(const InputState& input)
{
	// �}�E�X���x�ɂ�鎋�_�ړ�
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
	// �ړ����t���O
	m_isMove = false;

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

	// �_�b�V������
	if (input.IsPressed(InputType::dash))
	{
		// �_�b�V�����t���OON
		m_isDash = true;
		// �_�b�V�����͑��x�Q�{
		m_status.moveSpeed = kPlayerMoveSpeed * kDashRate;
	}
	else
	{
		// �_�b�V�����t���OOFF
		m_isDash = false;
		// �ʏ푬�x
		m_status.moveSpeed = kPlayerMoveSpeed;
	}

	// �n�ʂɂ���Ƃ��݈̂ړ�����
	if (m_status.isGround)
	{
		// �ړ��x�N�g��������
		m_status.dir = Game::kVecZero;
		// �O���ړ�����
		if (input.IsPressed(InputType::moveForward))
		{
			VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
			tempDir.y = 0.0f;
			m_status.dir = VAdd(m_status.dir, tempDir);
			// �ړ����t���OON
			m_isMove = true;
		}
		// ����ړ�����
		if (input.IsPressed(InputType::moveBehind))
		{
			VECTOR tempDir = VSub(m_status.pos, m_status.lookPos);
			tempDir.y = 0.0f;
			m_status.dir = VAdd(m_status.dir, tempDir);
			// �ړ����t���OON
			m_isMove = true;
		}
		// �E�ړ�����
		if (input.IsPressed(InputType::moveRight))
		{
			VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
			tempDir.y = 0.0f;
			// �i�s�����E��90�x��]
			MATRIX mtx = MGetRotY(DX_PI_F / 2);
			tempDir = VTransform(tempDir, mtx);
			m_status.dir = VAdd(m_status.dir, tempDir);
			// �ړ����t���OON
			m_isMove = true;
		}
		// ���ړ�����
		if (input.IsPressed(InputType::moveLeft))
		{
			VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
			tempDir.y = 0.0f;
			// �i�s��������90�x��]
			MATRIX mtx = MGetRotY(-DX_PI_F / 2);
			tempDir = VTransform(tempDir, mtx);
			m_status.dir = VAdd(m_status.dir, tempDir);
			// �ړ����t���OON
			m_isMove = true;
		}
	}
	// �ʏ�̈ړ�����
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	m_status.pos = VAdd(m_status.pos, m_status.dir);

	// �W�����v����
	if (m_status.isGround)
	{
		// �W�����v�͏�����
		m_status.jumpPower = 0.0f;
		if (input.IsTriggered(InputType::jump))
		{
			if (m_posture == PostureType::stand)
			{
				// �W�����v����
				m_status.jumpPower += kJumpPower;
				// �󒆔���
				m_status.isGround = false;
			}
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

void Player::UpdatePosture(const InputState& input)
{
	// �X���C�f�B���O����
	if (m_posture == PostureType::slide)
	{
		UpdateSlide();
		return;
	}

	// ���Ⴊ�ݔ���
	if (input.IsTriggered(InputType::crouch))
	{
		// �_�b�V����
		if (m_isDash)
		{
			// �X���C�f�B���O����
			OnSlide();

			return;
		}

		// �����p���Ȃ�
		if(m_posture == PostureType::stand)
		{
			// ���Ⴊ�ݎp��
			m_posture = PostureType::crouch;
		}
		// ���Ⴊ�ݎp���Ȃ�
		else if(m_posture == PostureType::crouch)
		{
			// �����p��
			m_posture = PostureType::stand;
		}

		// ���Ⴊ�ݎp��
		if (m_posture == PostureType::stand)
		{
			m_eyeHeight = kStandHeight;
		}
		// �����p��
		else if (m_posture == PostureType::crouch)
		{
			m_eyeHeight = kCrouchHeight;
		}
	}

	// �p���ɂ����W����
	if (m_status.isGround)
	{
		m_status.pos.y = m_eyeHeight;
	}
}

void Player::UpdateSlide()
{
	// �X���C�f�B���O����
	if(m_slideTime > 0)
	{
		// �X���C�f�B���O���Ԍ���
		m_slideTime--;
		// �X���C�f�B���O���W���Z
		m_status.pos = VAdd(m_status.pos, m_slideVec);
	}
	else
	{
		// �����p��
		m_posture = PostureType::stand;
		// �����w��
		m_eyeHeight = kStandHeight;
		// �X���C�f�B���O���x������
		m_slideVec = Game::kVecZero;
	}

	// �������f
	m_status.pos.y = m_eyeHeight;
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
		// ���b�N�I�����Ȃ�
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
				obj->OnHit(kShotDamage);
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

void Player::OnSlide()
{
	// �X���C�f�B���O�p��
	m_posture = PostureType::slide;
	// �X���C�f�B���O���Ԑݒ�
	m_slideTime = kSlideTime;
	// �����w��
	m_eyeHeight = kCrouchHeight;
	// �i�s�����x�N�g���擾
	m_slideVec = VSub(m_status.lookPos, m_status.pos);
	m_slideVec.y = 0.0f;
	// ���K��
	if (VSize(m_slideVec) > 0) m_slideVec = VNorm(m_slideVec);
	// ���x�ݒ�
	m_slideVec = VScale(m_slideVec, kPlayerMoveSpeed * kSlideRate);
}

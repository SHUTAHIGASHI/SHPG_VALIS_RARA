#include "CameraManager.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	// ��_���[�W��ʗh��̑傫��
	constexpr int kDamageQuakeScaleNum = 10;
	// �ړ����̉�ʗh��̑傫��
	constexpr float kMoveQuakeScaleNum = 2.0f;
	// �ړ����̉�ʗh��̑��x
	constexpr float kMoveQuakeSpeedNum = 0.5f;
}

// �R���X�g���N�^
CameraManager::CameraManager():
	m_dir(Game::kVecZero),
	m_pos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_fov(0.0f),
	m_rotaAxisY(0.0f),
	m_moveQuakeScale(0.0f),
	m_moveQuakeNum(0.0f),
	m_isMoveQuake(false),
	m_damageQuakeScale(0),
	m_pCamera(std::make_shared<Camera>())
{
}

// �f�X�g���N�^
CameraManager::~CameraManager()
{
	// �����Ȃ�
}

// ������
void CameraManager::Init()
{
	// �J�����̎���p�ݒ�
	m_fov = CameraSetting::kFovNum;
	// �J�����̉�]�ݒ�
	m_rotaAxisY = DX_PI_F;
	// �J�����ݒ菉����
	m_pCamera->Init(CameraSetting::kCameraNear, CameraSetting::kCameraFar, m_fov);
	// �J�������W�ݒ�
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
	// �ړ����̗h��T�C�Y�ݒ�
	m_moveQuakeScale = 0;
	// �ړ����̗h��̌����ݒ�
	m_moveQuakeNum = kMoveQuakeSpeedNum;
}

// �X�V
void CameraManager::Update()
{	
	// ��ʗh��̏���
	if (m_damageQuakeScale != 0)
	{
		UpdateDamageQuake();
	}

	if(m_isMoveQuake)
	{
		UpdateMoveQuake();
	}
	
	// �J�����Ɉʒu�𔽉f
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
}

// ��ʗh��
void CameraManager::OnDamageQuake()
{
	// �h��̑傫����ݒ�
	m_damageQuakeScale = kDamageQuakeScaleNum;
}

void CameraManager::OnMoveQuake()
{
	// �h�ꔻ��
	m_isMoveQuake = true;
}

void CameraManager::UpdateDamageQuake()
{
	// ��ʗh��̐��l����
	m_targetPos.x += m_damageQuakeScale;
	m_targetPos.y += m_damageQuakeScale;
	m_pos.x += m_damageQuakeScale;
	m_pos.y += m_damageQuakeScale;

	// ��ʗh��̐��l��0�ȊO�̏ꍇ
	if (m_damageQuakeScale != 0)
	{
		// �h��̑傫�������炷
		if (m_damageQuakeScale > 0)
		{
			m_damageQuakeScale--;
		}
		m_damageQuakeScale *= -1;
	}
}

void CameraManager::UpdateMoveQuake()
{
	// ��ʗh��̌�����ݒ�
	m_moveQuakeScale += m_moveQuakeNum;
	if(m_moveQuakeScale > kMoveQuakeScaleNum)
	{
		m_moveQuakeNum *= -1;
	}
	if(m_moveQuakeScale < -kMoveQuakeScaleNum)
	{
		m_moveQuakeNum *= -1;
	}
	// ��ʗh��̐��l����
	m_pos.y += m_moveQuakeScale;
	m_targetPos.y += m_moveQuakeScale;
	// ��ʗh�ꔻ�胊�Z�b�g
	m_isMoveQuake = false;
}

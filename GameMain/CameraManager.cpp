#include "CameraManager.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	// ��ʗh��̑傫��
	constexpr int kQuakeScaleNum = 10;
	// �����_�萔
	static const VECTOR kTargetPos = VGet(0.0f, 100.0f, 500.0f);
}

// �R���X�g���N�^
CameraManager::CameraManager():
	m_dir(Game::kVecZero),
	m_pos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_fov(0.0f),
	m_rotaAxisY(0.0f),
	m_screenQuakeScale(0),
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
}

// �X�V
void CameraManager::Update()
{
	// �J�������W�̍X�V
	UpdatePos();
	
	// ��ʗh��̏���
	if (m_screenQuakeScale != 0)
	{
		UpdateQuake();
	}
	
	// �J�����Ɉʒu�𔽉f
	m_pCamera->SetPosAndTarget(m_pos, m_targetPos);
}

// ��ʗh��
void CameraManager::OnScreenQuake()
{
	// �h��̑傫����ݒ�
	m_screenQuakeScale = kQuakeScaleNum;
}

void CameraManager::UpdatePos()
{
	// �����_���W�̐ݒ�
	m_targetPos = VAdd(m_pPlayer->GetPos(), kTargetPos);
	// �J�����̍��W��ݒ�
	m_pos = VGet(m_pPlayer->GetPos().x,
		m_pPlayer->GetPos().y + 100.0f,
		m_pPlayer->GetPos().z - 200.0f);
}

void CameraManager::UpdateQuake()
{
	// ��ʗh��̐��l����
	m_targetPos.x += m_screenQuakeScale;
	m_targetPos.y += m_screenQuakeScale;
	m_pos.x += m_screenQuakeScale;
	m_pos.y += m_screenQuakeScale;

	// ��ʗh��̐��l��0�ȊO�̏ꍇ
	if (m_screenQuakeScale != 0)
	{
		// �h��̑傫�������炷
		if (m_screenQuakeScale > 0)
		{
			m_screenQuakeScale--;
		}
		m_screenQuakeScale *= -1;
	}
}

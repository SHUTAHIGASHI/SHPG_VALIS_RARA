#include "CameraController.h"
#include "Camera.h"

namespace
{
	// �X�^�[�g���̃J�������o
	// Y���𒆐S�Ƃ����J�����̈ړ����x
	constexpr float kMoveSpeedAxisY = 0.03f;
	// �X�^�[�g���o��Y��
	constexpr float kStartPosY = 0.0f;
	// �J�����ʒu�������l
	constexpr float kReposCameraY = 300.0f;
	constexpr float kReposCameraZ = 1000.0f;
	// �J�����ʒu�܂ł̑��x
	constexpr float kCameraMoveSpeed = 92.0f;
	// ����p�ϓ����x
	constexpr float kFovExpandSpeed = 0.5f;
	constexpr float kFovReductionSpeed = -0.5f;
	// ��ʗh��̑傫��
	constexpr int kQuakeScaleNum = 10;
	// �ۑ����钍���_�̃t���[����
	constexpr int kSaveLookPosNum = 5;
}

// �R���X�g���N�^
CameraController::CameraController():
	m_dir(Game::kVecZero),
	m_pos(Game::kVecZero),
	m_lookPos(Game::kVecZero),
	m_fov(0.0f),
	m_rotaAxisY(0.0f),
	m_startPosY(kStartPosY),
	m_screenQuakeScale(0),
	m_isCameraSet(false),
	m_pCamera(std::make_shared<Camera>())
{
}

// �f�X�g���N�^
CameraController::~CameraController()
{
	// �����Ȃ�
}

// ������
void CameraController::Init()
{
	// �J�����̎���p�ݒ�
	m_fov = CameraSetting::kFovNum;
	// �J�����̉�]�ݒ�
	m_rotaAxisY = DX_PI_F;
	// �J�����ݒ菉����
	m_pCamera->Init(CameraSetting::kCameraNear, CameraSetting::kCameraFar, m_fov);

	// �J�����̈ʒu�ݒ�
	// �v���C���[�̈ʒu��Ǐ]
	m_pos = Game::kVecZero;
	m_pos.y += kReposCameraY;
	m_pos.z += 500.0f;
	// �J�����̌�����Y���𒆐S�ɔ��]������
	MATRIX mtxRotaY = MGetRotY(m_rotaAxisY);
	m_pos = VTransform(m_pos, mtxRotaY);
	// �J�����̒����_�ݒ�
	m_lookPos = Game::kVecZero;
	m_lookPos.z += 5000.0f;
	// �J�������W�ݒ�
	m_pCamera->SetPosAndTarget(m_pos, m_lookPos);
}

// �X�V
void CameraController::Update()
{
	// ���t���[���O�܂ł̃J�������W�̕ۑ��ƍ폜���s��
	UpdateCameraPos();
	
	// ��ʗh��̏���
	if (m_screenQuakeScale != 0)
	{
		UpdateCameraQuake();
	}

	// �J�����̌�����Z���𒆐S�ɔ��]������
	MATRIX mtx = MGetRotZ(DX_PI_F);
	VECTOR cameraUpVec = VTransform(m_pos, mtx);

	// �J�����Ɉʒu�𔽉f
	m_pCamera->SetPosAndTarget(m_pos, m_lookPos);
}

void CameraController::UpdateCameraPos()
{
	// �J�����ʒu�̐ݒ�
	VECTOR cameraPos = Game::kVecZero;
	m_dir = VSub(cameraPos, m_pos);
	m_dir = VNorm(m_dir);
	m_dir = VScale(m_dir, kCameraMoveSpeed);
	m_pos = VAdd(m_pos, m_dir);

	// �����_�̐ݒ�
	m_lookPos = Game::kVecZero;
}

void CameraController::UpdateCameraQuake()
{
	// ��ʗh��̐��l����
	m_lookPos.x += m_screenQuakeScale;
	m_lookPos.y += m_screenQuakeScale;
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

// �V�[�����C���J�n���̉��o�p�X�V����
void CameraController::StartUpdate()
{
	// ���t���[���J������]
	m_rotaAxisY -= kMoveSpeedAxisY;
	if (m_rotaAxisY < 0.0f)
	{
		m_rotaAxisY = 0.0f;
		m_isCameraSet = true;
	}
	// �v���C���[�̈ʒu��Ǐ]
	m_pos = Game::kVecZero;
	// �J�����̌�����Y���𒆐S�ɔ��]������
	MATRIX mtxRotaY = MGetRotY(m_rotaAxisY);
	m_pos = VTransform(m_pos, mtxRotaY);

	// �v���C���[��̈ʒu�𒍎�����
	m_startPosY += 5.0f;
	if (m_startPosY > kReposCameraY) m_startPosY = kReposCameraY;
	m_lookPos = Game::kVecZero;

	// �J�����Ɉʒu�𔽉f
	m_pCamera->SetPosAndTarget(m_pos, m_lookPos);
}

void CameraController::EndUpdate()
{
	// ���t���[���J������]
	m_rotaAxisY += kMoveSpeedAxisY;
	if (m_rotaAxisY > DX_PI_F)
	{
		m_rotaAxisY = DX_PI_F;
	}
	// �v���C���[�̈ʒu��Ǐ]
	/*m_pos = VGet(m_pPlayer->GetPos().x * kCameraCenterDistance,
		m_pPlayer->GetPos().y * kCameraCenterDistance,
		m_pPlayer->GetPos().z - kReposCameraZ);*/
	// �J�����̌�����Y���𒆐S�ɔ��]������
	MATRIX mtxRotaY = MGetRotY(DX_PI_F);
	m_pos = VTransform(m_pos, mtxRotaY);

	// �����_�ݒ�
	m_lookPos = Game::kVecZero;

	// �J�����Ɉʒu�𔽉f.
	m_pCamera->SetPosAndTarget(m_pos, m_lookPos);
}

void CameraController::ResultUpdate()
{
	// �v���C���[�̈ʒu��Ǐ]
	m_pos = Game::kVecZero;

	// �����_�ݒ�
	m_lookPos = Game::kVecZero;

	// �J�����Ɉʒu�𔽉f.
	m_pCamera->SetPosAndTarget(m_pos, m_lookPos);
}

// ��ʗh��
void CameraController::OnScreenQuake()
{
	// �h��̑傫����ݒ�
	m_screenQuakeScale = kQuakeScaleNum;
}

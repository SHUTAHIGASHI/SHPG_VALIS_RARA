#include "Camera.h"

Camera::Camera():
	m_cameraPos(VGet(0.0f, 0.0f, 0.0f)),
	m_targetPos(VGet(0.0f, 0.0f, 0.0f)),
	m_cameraUpVec(VGet(0.0f, 0.0f, 0.0f)),
	m_fov(0.0f),
	m_changeFrame(0),
	m_quakeScale(0)
{
}

Camera::~Camera()
{
}

void Camera::Init(float near_, float far_, float fov)
{
	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	// ���ʃ|���S����\�����Ȃ�
	SetUseBackCulling(true);
	// �j�A/�t�@�[�̐ݒ�
	SetCameraNearFar(near_, far_);
	// ����p������
	SetCameraFov(fov);
}

void Camera::Update()
{
	// �J�����ړ��̃t���[����
	if (m_changeFrame > 0) m_changeFrame--;

	// �J�����h��̍X�V����
	CameraQuakeUpdate();
}

void Camera::SetPosAndTarget(VECTOR cameraPos, VECTOR targetPos)
{
	// ���W�ݒ�
	m_cameraPos = cameraPos;
	m_targetPos = targetPos;
	// �J�����Ɉʒu�𔽉f
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos);
}

void Camera::SetPosAndTargetAndUpVec(VECTOR cameraPos, VECTOR targetPos, VECTOR cameraUpVec)
{
	// ���W�ݒ�
	m_cameraPos = cameraPos;
	m_targetPos = targetPos;
	m_cameraUpVec = cameraUpVec;
	// �J�����Ɉʒu�𔽉f
	SetCameraPositionAndTargetAndUpVec(m_cameraPos, m_targetPos, cameraUpVec);
}

void Camera::SetNextCameraPosAndFrame(VECTOR cameraPos, int frame)
{
	m_changeFrame = frame;
}

void Camera::SetNextTargetPosAndFrame(VECTOR targetPos, int frame)
{
	m_changeFrame = frame;
}

void Camera::SetNextCameraPosAndTargetPosAndFrame(VECTOR cameraPos, VECTOR targetPos, int frame)
{
	m_changeFrame = frame;
}

void Camera::SetCameraFov(float fov)
{
	// ����p�̐ݒ�
	m_fov = fov;
	SetupCamera_Perspective(m_fov * DX_PI_F / 180.0f);
}

void Camera::CameraQuakeUpdate()
{
	// ��ʗh��̐��l����
	m_cameraPos.x += m_quakeScale;
	m_cameraPos.y += m_quakeScale;
	m_targetPos.x += m_quakeScale;
	m_targetPos.y += m_quakeScale;

	// ��ʗh��̐��l��0�ȊO�̏ꍇ
	if (m_quakeScale != 0)
	{
		// �h��̑傫�������炷
		if (m_quakeScale > 0)
		{
			m_quakeScale--;
		}
		m_quakeScale *= -1;
	}
}

#pragma once
#include "Game.h"

namespace CameraSetting
{
	// Near/Far
	constexpr float kCameraNear = 100.0f;
	constexpr float kCameraFar = 12800.0f;
	// ����p�萔
	constexpr float kFovNum = 80.0f;
}

class Camera
{
public:
	// �R���X�g���N�^
	Camera();
	// �f�X�g���N�^
	virtual ~Camera();

	// �J�����̏�����
	void Init(float near_, float far_, float fov);
	// �X�V����
	void Update();

	// �J�����ʒu�ƃ^�[�Q�b�g�ʒu�̐ݒ�
	void SetPosAndTarget(VECTOR cameraPos, VECTOR targetPos);
	// �J�����ʒu�ƃ^�[�Q�b�g�ʒu�̐ݒ�
	void SetPosAndTargetAndUpVec(VECTOR cameraPos, VECTOR targetPos, VECTOR cameraUpVec);

	// �w�肵���t���[���ŃJ�����ʒu��ύX
	void SetNextCameraPosAndFrame(VECTOR cameraPos, int frame);
	// �w�肵���t���[���Ń^�[�Q�b�g�ʒu��ύX
	void SetNextTargetPosAndFrame(VECTOR targetPos, int frame);
	// �w�肵���t���[���ŃJ�����ʒu�ƃ^�[�Q�b�g�ʒu��ύX
	void SetNextCameraPosAndTargetPosAndFrame(VECTOR cameraPos, VECTOR targetPos, int frame);

	// �J�����̎���p�ύX
	void SetCameraFov(float fov);
	// �J�����̗h��
	void SetCameraQuake(int quakeScale) { m_quakeScale = quakeScale; }

private:
	// �J�����h��̍X�V����
	void CameraQuakeUpdate();

private:
	// �J�������W
	VECTOR m_cameraPos;
	// �^�[�Q�b�g���W
	VECTOR m_targetPos;
	// �J����������̃x�N�g��
	VECTOR m_cameraUpVec;
	// �J�����̎���p
	float m_fov;

	// ���W�ϊ��̃t���[����
	int m_changeFrame;
	// �J�����h��̑傫��
	int m_quakeScale;
};


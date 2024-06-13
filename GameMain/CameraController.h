#pragma once
#include "Game.h"
#include <deque>
#include <memory>

class Camera;

// �J����
class CameraController
{
public:
	// �R���X�g���N�^
	CameraController();
	// �f�X�g���N�^
	virtual ~CameraController();

	// �J����������
	void Init();
	// �J�����X�V
	void Update();
	// �J�����ʒu�X�V
	void UpdateCameraPos();
	// �J�����̗h��L�����̍X�V
	void UpdateCameraQuake();
	// �V�[�����C���J�n���̉��o�p�X�V����
	void StartUpdate();
	// �V�[�����C���I�����̉��o�p�X�V����
	void EndUpdate();
	// �V�[�����C���J�n���̉��o�p�X�V����
	void ResultUpdate();
	// ��ʗh��
	void OnScreenQuake();
	// �|�W�V������Getter
	const VECTOR& GetPos() const { return m_pos; }
	// �J������]���擾
	const float GetRotaAxisY() const { return m_rotaAxisY; }
	// �X�^�[�g���o�I������
	const bool IsCameraSet() const { return m_isCameraSet; }

private:
	// �J�������W
	VECTOR m_dir;
	VECTOR m_pos;
	VECTOR m_lookPos;
	// �J��������p
	float m_fov;
	// �J������]
	float m_rotaAxisY;
	// �J�n���o���̃J����Y��
	float m_startPosY;
	// ��ʗh��̑傫��
	int m_screenQuakeScale;
	// �X�^�[�g���o�I������
	bool m_isCameraSet;
	// �J����
	std::shared_ptr<Camera> m_pCamera;

private:
};

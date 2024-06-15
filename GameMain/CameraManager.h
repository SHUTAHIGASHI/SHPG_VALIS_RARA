#pragma once
#include "Game.h"
#include <deque>
#include <memory>

// �J����
class CameraManager
{
public:
	// �R���X�g���N�^
	CameraManager();
	// �f�X�g���N�^
	virtual ~CameraManager();

	// �v���C���[�|�C���^�Z�b�g
	void SetPlayer(class Player* pPlayer) { m_pPlayer = pPlayer; }

	// ������
	void Init();
	// �X�V
	void Update();

	// ��ʗh��
	void OnScreenQuake();

private:// �����o�֐�
	// ���W�X�V
	void UpdatePos();
	// �h��X�V
	void UpdateQuake();

private:// �����o�ϐ�
	// �J�������W
	VECTOR m_dir;
	VECTOR m_pos;
	VECTOR m_targetPos;
	// �J��������p
	float m_fov;
	// �J������]
	float m_rotaAxisY;
	// ��ʗh��̑傫��
	int m_screenQuakeScale;
	// �J����
	std::shared_ptr<class Camera> m_pCamera;
private:
	// �v���C���[�|�C���^
	class Player* m_pPlayer;
};

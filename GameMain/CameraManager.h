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

	// ������
	void Init();
	// �X�V
	void Update();
	// ��_���[�W��ʗh��
	void OnDamageQuake();
	// �ړ����̗h��
	void OnMoveQuake();

	// �J�������W�Z�b�g
	void SetPosAndTarget(VECTOR pos, VECTOR target) { m_pos = pos; m_targetPos = target; }

	// �J�������W�擾
	VECTOR GetPos() { return m_pos; }

private:// �����o�֐�
	// �h��X�V
	void UpdateDamageQuake();
	// �ړ����̗h��X�V
	void UpdateMoveQuake();

private:// �����o�ϐ�
	// �J�������W
	VECTOR m_dir;
	VECTOR m_pos;
	VECTOR m_targetPos;
	// �J��������p
	float m_fov;
	// �J������]
	float m_rotaAxisY;
	// �ړ����̗h��̑傫��
	float m_moveQuakeScale;
	float m_moveQuakeNum;
	// �ړ����̗h�ꔻ��
	bool m_isMoveQuake;
	// ��ʗh��̑傫��
	int m_damageQuakeScale;

	// �J����
	std::shared_ptr<class Camera> m_pCamera;
};

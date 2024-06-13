#pragma once
#include "Game.h"

class Model
{
public:
	// �R���X�g���N�^
	Model(int handle);
	// �f�X�g���N�^
	virtual ~Model();

	// �X�V(�A�j���[�V�����g�p���̂�)
	void Update();
	// �`��
	void Draw();

	// �e���̐ݒ�
	void SetModelLocalPos(VECTOR pos);					// ���f���̃��[�J�����W����
	void SetPosition(VECTOR pos);								// ���W
	void SetScale(float size);									// �g��
	void SetMotionType(int);									// ���[�V�����^�C�v
	void SetDirectionAxisY(VECTOR lookPos, float rota);			// ����
	void SetDirectionAxisZ(VECTOR lookPos, float rota);			// ����
	void SetRotation(VECTOR);									// ��]
	void SetOutline(int materialIndex, float width, float r, float g, float b, float a);	// �֊s��

	/* getter */
	VECTOR GetPos() { return m_pos; }// ���W

private:
	// ���f���n���h��
	int m_hModel;

	// �A�j���[�V����
	int m_AnimNo;
	int m_AnimIndex;
	float m_AnimTotalTime;
	float m_AnimPlayTime;

	// ���f���̃��[�J�����W�̒������W
	VECTOR m_localPos;
	// �\���ʒu���W
	VECTOR m_pos;
	// ��]
	VECTOR m_rotation;
};


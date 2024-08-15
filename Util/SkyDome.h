#pragma once
#include<memory>
#include "Game.h"

class Model;

class SkyDome
{
public:
	// �R���X�g���N�^
	SkyDome();
	// �f�X�g���N�^
	~SkyDome();
	// ������
	void Init(VECTOR pos);
	// �X�V
	void Update();
	// �`��
	void Draw();

	// �e��ݒ�
	void SetPos(VECTOR pos);
	void SetScale(float scale);

private:
	// ���f��
	std::shared_ptr<Model> m_pModel;
	// �n���h��
	int m_handle;
	// �T�C�Y
	float m_scale;
	// ��]�p�x
	float m_rot;
};


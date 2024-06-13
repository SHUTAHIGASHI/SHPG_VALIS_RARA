#pragma once
#include "ObjectBase.h"

class Player :
	public ObjectBase
{
public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	virtual ~Player();

	// ������
	void Init() override;
	// �X�V
	void Update(const InputState& input) override;
	// �`��
	void Draw() override;

	// �V���b�g����
	void CreateShot();

private:
	// �摜�n���h��
	int m_hImg;
};


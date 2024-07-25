#pragma once
#include "Game.h"

class ObjectBase
{
	struct ObjectStatus
	{
		// �L������
		bool isEnabled = true;
		// ���S����
		bool isDead = false;
		// �n�ʔ���
		bool isGround = false;
		// ���W
		VECTOR exPos = Game::kVecZero;
		VECTOR pos = Game::kVecZero;
		VECTOR dir = Game::kVecZero;
		// �����_
		VECTOR lookPos = Game::kVecZero;
		VECTOR lookDir = Game::kVecZero;
		// ��]
		VECTOR rota = Game::kVecZero;
		VECTOR rotaDir = Game::kVecZero;
		// ���x
		float moveSpeed = 0.0f;
		// �W�����v��
		float jumpPower = 0.0f;
		// ���a
		float radius = 0.0f;
		// �g�嗦
		float scale = 1.0f;
		// �f�[�^�n���h��
		int hModel = 0;
		// �摜�f�[�^�n���h��
		int hImg = 0;
		// �̗�
		int hp = 0;
		// ���G����
		int invTime = 0;
	};

public:
	// �R���X�g���N�^
	ObjectBase(){};
	// �f�X�g���N�^
	virtual ~ObjectBase() {};

	// ������
	virtual void Init() {};
	// �X�V
	virtual void Update() {};
	virtual void Update(const InputState& input) {};
	// �`��
	virtual void Draw() {};

	// �Փ˔���
	bool CheckCollision(ObjectBase* obj);

	// �I�u�W�F�N�g�̃X�e�[�^�X���擾
	const VECTOR GetPos() const { return m_status.pos; }
	const VECTOR GetDir() const { return m_status.dir; }
	const float GetSpeed() const { return m_status.moveSpeed; }
	const float GetRadius() const { return m_status.radius; }
	const int GetHP() const { return m_status.hp; }
	const bool IsEnabled() const { return m_status.isEnabled; }
	const bool IsDead() const { return m_status.isDead; }

protected:
	// �I�u�W�F�N�g�̃X�e�[�^�X
	ObjectStatus m_status;
};


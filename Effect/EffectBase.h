#pragma once
#include "Game.h"

// �G�t�F�N�g�̎��
enum class EffectType
{
	EngineFire,
	Dead,
	Damage,
	BossDamage,
	Shot,
	EnemyShot,
	Charge,
	ChargeShot,
	Heal,
	Avoid
};

// �G�t�F�N�g�x�[�X
class EffectBase
{
public:
	// �R���X�g���N�^
	EffectBase(EffectType type, int handle, bool loop);
	EffectBase(EffectType type, int handle, bool loop, class ObjectBase* obj);
	// �f�X�g���N�^
	virtual ~EffectBase();

	// �X�V����
	void Update();
	// �G�t�F�N�g��~
	void StopCurrentEffect();
	// �G�t�F�N�g�쐬
	void CreateEffect();

	// �G�t�F�N�g�̊e��ݒ�
	void SetPosition(VECTOR pos);
	void SetPositionOnlyZ(float posZ);
	void SetEffectPlayingSpeed(float speed);
	void SetEffectColor(int r, int g, int b, int a);
	void SetTracking(bool isTracking) { m_isTracking = isTracking; }
	void SetRota(VECTOR rota);
	void SetScale(float scale);
	void SetEnable(bool isEnable) { m_isEnable = isEnable; }

	// �G�t�F�N�g�L������擾
	bool IsEnable() { return m_isEnable; }
	// �G�t�F�N�g�^�C�v�擾
	EffectType GetEffectType() { return m_type; }
	// �ǔ����̃I�u�W�F�N�g�擾
	class ObjectBase* GetTrackingObject() 
	{ 
		// �ǔ����̃I�u�W�F�N�g�����݂���ꍇ�͂��̃I�u�W�F�N�g��Ԃ�
		if(m_trackingObject != nullptr) return m_trackingObject; 
		else return nullptr;
	}

protected:
	// �G�t�F�N�g���L�����ǂ���
	bool m_isEnable;
	// �G�t�F�N�g���ǔ����邩�ǂ���
	bool m_isTracking;
	// �G�t�F�N�g�����[�v���邩�ǂ���
	bool m_isLoop;
	// �G�t�F�N�g�^�C�v
	EffectType m_type;
	// �G�t�F�N�g�̃n���h��
	int m_hEffectResource;
	int m_currentPlayingEffect;
	// �`����W
	VECTOR m_pos;
	// �ǔ�����I�u�W�F�N�g
	ObjectBase* m_trackingObject = nullptr;
};


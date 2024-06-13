#include "EffectBase.h"
#include "ObjectBase.h"

EffectBase::EffectBase(EffectType type, int handle, bool loop) :
	m_isEnable(true),
	m_type(type),
	m_isLoop(loop),
	m_isTracking(false),
	m_hEffectResource(handle),
	m_currentPlayingEffect(-1),
	m_pos(Game::kVecZero),
	m_trackingObject(nullptr)
{
	// �G�t�F�N�g�̐���
	CreateEffect();
}

EffectBase::EffectBase(EffectType type, int handle, bool loop, ObjectBase* obj) :
	m_isEnable(true),
	m_type(type),
	m_isLoop(loop),
	m_isTracking(true),
	m_hEffectResource(handle),
	m_currentPlayingEffect(-1),
	m_pos(obj->GetPos()),
	m_trackingObject(obj)
{
	// �G�t�F�N�g�̐���
	CreateEffect();
}

EffectBase::~EffectBase()
{
	// �G�t�F�N�g�̒�~
	StopCurrentEffect();
}

void EffectBase::SetPosition(VECTOR pos)
{
	m_pos = pos;
}

void EffectBase::SetPositionOnlyZ(float posZ)
{
	m_pos.z = posZ;
}

void EffectBase::SetEffectPlayingSpeed(float speed)
{
	SetSpeedPlayingEffekseer3DEffect(m_currentPlayingEffect, speed);
}

void EffectBase::SetEffectColor(int r, int g, int b, int a)
{
	SetColorPlayingEffekseer3DEffect(m_currentPlayingEffect, r, g, b, a);
}

void EffectBase::SetRota(VECTOR rota)
{
	// �G�t�F�N�g�̉�]
	SetRotationPlayingEffekseer3DEffect(m_currentPlayingEffect, rota.x, rota.y, rota.z);
}

void EffectBase::SetScale(float scale)
{
	if(scale <= 0.0f) return;
	SetScalePlayingEffekseer3DEffect(m_currentPlayingEffect, scale, scale, scale);
}

void EffectBase::Update()
{
	// �G�t�F�N�g���Đ������ǂ���
	if (IsEffekseer3DEffectPlaying(m_currentPlayingEffect) != 0)
	{
		if (m_isLoop)
		{
			// ���[�v�Đ�
			m_currentPlayingEffect = PlayEffekseer3DEffect(m_hEffectResource);
		}
		else
		{
			// ������
			m_isEnable = false;
		}
	}

	// �ǔ��I�u�W�F�N�g���L�����ǂ���
	if (m_isTracking)
	{
		if (m_trackingObject != nullptr)
		{
			m_pos = m_trackingObject->GetPos();
		}
	}

	// �G�t�F�N�g�̍��W�ݒ�
	SetPosPlayingEffekseer3DEffect(m_currentPlayingEffect, m_pos.x, m_pos.y, m_pos.z);
}

void EffectBase::StopCurrentEffect()
{
	// ���łɒ�~���Ă���ꍇ�͉������Ȃ�
	if(!m_isEnable) m_isEnable = true;
	// �G�t�F�N�g�̒�~
	int result = 0;
	if (IsEffekseer3DEffectPlaying(m_currentPlayingEffect) == 0)
	{
		result = StopEffekseer3DEffect(m_currentPlayingEffect);
	}
	assert(result == 0);
}

void EffectBase::CreateEffect()
{
	// �G�t�F�N�g�̍Đ�
	m_currentPlayingEffect = PlayEffekseer3DEffect(m_hEffectResource);
	assert(m_hEffectResource != -1);
	// �G�t�F�N�g�̍��W�ݒ�
	SetPosPlayingEffekseer3DEffect(m_currentPlayingEffect, m_pos.x, m_pos.y, m_pos.z);
}


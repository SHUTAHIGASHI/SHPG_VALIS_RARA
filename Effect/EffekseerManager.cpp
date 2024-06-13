#include "EffekseerManager.h"
#include "EffectBase.h"

EffekseerManager::EffekseerManager() :
	m_EffectHandle(),
	m_pEffects()
{
	// �G�t�F�N�g�̓ǂݍ���
	LoadData();
}

EffekseerManager::~EffekseerManager()
{
	// �G�t�F�N�g�̍폜
	m_pEffects.clear();
	// �G�t�F�N�g�̔j��
	for (auto& efc : m_EffectHandle)
	{
		// �G�t�F�N�g�f�[�^�̍폜
		DeleteEffekseerEffect(efc.second);
	}
	// �G�t�F�N�g�n���h���̃N���A
	m_EffectHandle.clear();
}

void EffekseerManager::Update()
{
	// �G�t�F�N�V�A��3D�ݒ���X�V
	Effekseer_Sync3DSetting();
	// �G�t�F�N�V�A�̍X�V
	for (auto& effects : m_pEffects)
	{
		effects->Update();
	}
	// �����ɂȂ����G�t�F�N�g�͍폜
	DeleteDisableEffect();
	// �G�t�F�N�g�̍X�V
	UpdateEffekseer3D();
}

void EffekseerManager::Draw()
{
	// �G�t�F�N�g�̕`��
	DrawEffekseer3D();
}

void EffekseerManager::CreateEffect(EffectType type, bool loop, ObjectBase* obj)
{
	// �G�t�F�N�g�̐���
	m_pEffects.push_back(std::make_shared<EffectBase>(type, m_EffectHandle[type], loop, obj));
}

void EffekseerManager::CreateEffectAndSetScale(EffectType type, bool loop, ObjectBase* obj, float scale)
{
	// �G�t�F�N�g�̐���
	m_pEffects.push_back(std::make_shared<EffectBase>(type, m_EffectHandle[type], loop, obj));
	// �G�t�F�N�g�̊g�嗦�ݒ�
	m_pEffects.back()->SetScale(scale);
}

void EffekseerManager::CreateEffect(EffectType type, bool loop, VECTOR pos)
{
	// �G�t�F�N�g�̐���
	m_pEffects.push_back(std::make_shared<EffectBase>(type, m_EffectHandle[type], loop));
	// �G�t�F�N�g�̍��W�ݒ�
	m_pEffects.back()->SetPosition(pos);
}

void EffekseerManager::StopAllEffect()
{
	for (auto& effects : m_pEffects)
	{
		// �G�t�F�N�g�̖�����
		effects->SetEnable(false);
	}
	// �����ɂȂ����G�t�F�N�g�͍폜
	DeleteDisableEffect();
	// �G�t�F�N�g�̍X�V
	UpdateEffekseer3D();
}

void EffekseerManager::StopEffect(EffectType type)
{
	for (auto& efc : m_pEffects)
	{
		// �G�t�F�N�g�̎�ނ���v������
		if (efc->GetEffectType() == type)
		{
			// �G�t�F�N�g�̒�~
			efc->StopCurrentEffect();
		}
	}
}

void EffekseerManager::StopEffectTargetObj(class ObjectBase* obj)
{
	for (auto& efc : m_pEffects)
	{
		// �ǔ����̃I�u�W�F�N�g����v������
		if (efc->GetTrackingObject() == obj)
		{
			// �G�t�F�N�g�̒�~
			efc->StopCurrentEffect();
		}
	}
}

void EffekseerManager::DeleteDisableEffect()
{
	// �K�v�Ȃ��Ȃ����G�t�F�N�g�͏��Ԃɍ폜
	auto rmIt = std::remove_if(m_pEffects.begin(), m_pEffects.end(),
		[](const std::shared_ptr<EffectBase>& efc)
		{
			return !efc->IsEnable();
		});

	// ���ۂɔ͈͂��w�肵�č폜
	m_pEffects.erase(rmIt, m_pEffects.end());
}

void EffekseerManager::SetEffectPosition(EffectType type, VECTOR pos)
{
	for (auto& efc : m_pEffects)
	{
		// �G�t�F�N�g�̎�ނ���v������
		if (efc->GetEffectType() == type)
		{
			// �G�t�F�N�g�̍��W�ݒ�
			efc->SetPosition(pos);
		}
	}
}

void EffekseerManager::SetEffectRota(EffectType type, VECTOR rota)
{
	for (auto& efc : m_pEffects)
	{
		// �G�t�F�N�g�̎�ނ���v������
		if (efc->GetEffectType() == type)
		{
			// �G�t�F�N�g�̉�]�ݒ�
			efc->SetRota(rota);
		}
	}
}

bool EffekseerManager::IsPlayingEffect(EffectType type)
{
	for (auto& efc : m_pEffects)
	{
		// �G�t�F�N�g�̎�ނ���v������
		if (efc->GetEffectType() == type)
		{
			// �G�t�F�N�g���Đ������ǂ���
			return true;
		}
	}
	return false;
}

EffectBase* EffekseerManager::GetEffect(EffectType type)
{
	for (auto& efc : m_pEffects)
	{
		// �G�t�F�N�g�̎�ނ���v������
		if (efc->GetEffectType() == type)
		{
			// �G�t�F�N�g��Ԃ�
			return efc.get();
		}
	}
	return nullptr;
}

void EffekseerManager::LoadData()
{
	// �G�t�F�N�g�̓ǂݍ���
	m_EffectHandle[EffectType::EngineFire] = LoadEffekseerEffect("Data/EffectData/EngineFire.efkefc", 10.0f);
	m_EffectHandle[EffectType::Dead] = LoadEffekseerEffect("Data/EffectData/DeadGameOverEffect.efkefc", 100.0f);
	m_EffectHandle[EffectType::Damage] = LoadEffekseerEffect("Data/EffectData/Explosion.efkefc", 100.0f);
	m_EffectHandle[EffectType::BossDamage] = LoadEffekseerEffect("Data/EffectData/BossExplosion.efkefc", 100.0f);
	m_EffectHandle[EffectType::Shot] = LoadEffekseerEffect("Data/EffectData/Shot.efkefc", 10.0f);
	m_EffectHandle[EffectType::EnemyShot] = LoadEffekseerEffect("Data/EffectData/EnemyShot.efkefc", 10.0f);
	m_EffectHandle[EffectType::Heal] = LoadEffekseerEffect("Data/EffectData/Heal.efkefc", 25.0f);
	m_EffectHandle[EffectType::Charge] = LoadEffekseerEffect("Data/EffectData/Charge.efkefc", 25.0f);
	m_EffectHandle[EffectType::ChargeShot] = LoadEffekseerEffect("Data/EffectData/ChargeShot.efkefc", 10.0f);
	m_EffectHandle[EffectType::Avoid] = LoadEffekseerEffect("Data/EffectData/Avoid.efkefc", 25.0f);
}

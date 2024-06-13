#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include "Game.h"
#include "EffectBase.h"

class EffectBase;

/// <summary>
/// �G�t�F�N�V�A�̊Ǘ����s���V���O���g���N���X
/// </summary>
class EffekseerManager
{
public:
	// �f�X�g���N�^
	~EffekseerManager();
	// EffekseerManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	static EffekseerManager& GetInstance()
	{
		// �B��̎���
		static EffekseerManager instance;
		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	// �X�V
	void Update();
	// �`��
	void Draw();
	// �e��G�t�F�N�g�̐���
	void CreateEffect(EffectType type, bool loop, class ObjectBase* obj);
	void CreateEffectAndSetScale(EffectType type, bool loop, class ObjectBase* obj, float scale);
	void CreateEffect(EffectType type, bool loop, VECTOR pos);
	// ���ׂẴG�t�F�N�g�̒�~
	void StopAllEffect();
	// �I�񂾃G�t�F�N�g�̒�~
	void StopEffect(EffectType type);
	void StopEffectTargetObj(class ObjectBase* obj);
	// ����������Ă���G�t�F�N�g�̍폜
	void DeleteDisableEffect();
	// �w�肵���G�t�F�N�g�̍��W��ݒ�
	void SetEffectPosition(EffectType type, VECTOR pos);
	// �w�肵���G�t�F�N�g�̉�]��ݒ�
	void SetEffectRota(EffectType type, VECTOR rota);
	// �w�肵���G�t�F�N�g���Đ������ǂ���
	bool IsPlayingEffect(EffectType type);
	// �w�肵���G�t�F�N�g�擾
	EffectBase* GetEffect(EffectType type);

private:
	// �G�t�F�N�g�̓ǂݍ���
	void LoadData();

private:
	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	EffekseerManager();
	// �R�s�[��������֎~����
	EffekseerManager(const EffekseerManager&) = delete;		// �R�s�[�R���X�g���N�^
	void operator = (const EffekseerManager&) = delete;		// ������֎~

private:
	// �G�t�F�N�g�n���h���̃}�b�v
	std::unordered_map<EffectType, int> m_EffectHandle;
	// �G�t�F�N�g
	std::vector<std::shared_ptr<EffectBase>> m_pEffects;
};
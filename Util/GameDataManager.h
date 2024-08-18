#pragma once
#include <unordered_map>
#include <string>
#include <DxLib.h>

/// <summary>
/// �Q�[���f�[�^�̊Ǘ����s���V���O���g���N���X
/// </summary>
class GameDataManager
{
public:
	~GameDataManager();
	/// <summary>
	/// GameDataManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static GameDataManager& GetInstance()
	{
		// �B��̎���
		static GameDataManager instance;
		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	// �L�����N�^�[�f�[�^�̈ꎞ�ۑ�
	void SaveTempData(struct charaState data);
	// �L�����N�^�[�f�[�^�̎擾
	void SetData(struct charaState& data);

private:
	// �L�����N�^�[�f�[�^�̕ۑ�
	void SaveCharacterData();
	// �L�����N�^�[�f�[�^�̓ǂݍ���
	void LoadCharacterData();

	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	GameDataManager();
	// �R�s�[��������֎~����
	GameDataManager(const GameDataManager&) = delete;		// �R�s�[�R���X�g���N�^
	void operator = (const GameDataManager&) = delete;		// ������֎~

private:
};
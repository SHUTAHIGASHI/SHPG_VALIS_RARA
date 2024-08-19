#pragma once

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

	// �}�E�X���x�̎擾
	float GetMouseSensitivity() const { return m_mouseSensitivity; }
	// �}�E�X���x�̐ݒ�
	void SetMouseSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }

private:
	// �ύX�����T�E���h�����t�@�C���ɏ�������
	struct GameConfigInfo
	{
		char signature[5];			// "SET_"
		float version;				// 1.0
		float mouseSensitivity;		// �}�E�X���x
	};

	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	GameDataManager();
	// �R�s�[��������֎~����
	GameDataManager(const GameDataManager&) = delete;		// �R�s�[�R���X�g���N�^
	void operator = (const GameDataManager&) = delete;		// ������֎~

	// �Q�[���f�[�^�ۑ�
	void SaveCharacterData();
	// �Q�[���f�[�^�ǂݍ���
	void LoadCharacterData();

private:
	// �}�E�X���x
	float m_mouseSensitivity;
};
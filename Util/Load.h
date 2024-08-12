#pragma once
#include <unordered_map>
#include <string>

class Load
{
public:
	~Load();
	/// <summary>
	/// Load�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static Load& GetInstance()
	{
		// �B��̎���
		static Load instance;

		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	/// <summary>
	/// �S�Ẵf�[�^�����[�h����
	/// </summary>
	void AllLoadData();

	/// <summary>
	/// �S�Ẵf�[�^���폜����
	/// </summary>
	void DeleteAllData();

	/// <summary>
	/// �n���h�����擾����
	/// </summary>
	/// <param name="key">���[�h�f�[�^�̃L�[</param>
	/// <returns>�n���h��</returns>
	int GetImageHandle(std::string key)
	{
		return m_imageData[key];
	}

	/// <summary>
	/// 3D���f���̃n���h�����擾����
	/// </summary>
	/// <param name="key">���[�h�f�[�^�̃L�[</param>
	/// <returns>�n���h��</returns>
	int GetModelHandle(std::string key)
	{
		return m_modelData[key];
	}
private:
	//���[�h�f�[�^��unordered_map�ŊǗ�
	std::unordered_map<std::string, int> m_imageData;
	std::unordered_map<std::string, int> m_modelData;

	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	Load() {};

	// �R�s�[��������֎~����
	Load(const Load&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const Load&) = delete;		// ������֎~
};


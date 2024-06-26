#pragma once
#include <unordered_map>
#include <string>
#include <vector>

enum class SoundType
{
	select,
};

/// <summary>
/// SE�̊Ǘ����s���V���O���g���N���X
/// </summary>
class SoundManager
{
public:
	~SoundManager();
	/// <summary>
	/// SoundManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		// �B��̎���
		static SoundManager instance;

		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	// BGM�̍X�V
	void UpdateBGM();

	/// <summary>
	/// �w��̃T�E���h��炷
	/// </summary>
	/// <param name="name">�T�E���h��</param>
	void PlaySE(SoundType sound);

	/// <summary>
	/// SE�̃{�����[����ݒ肷��
	/// </summary>
	/// <param name="volume"></param>
	void SetSEVolume(int volume);
	int GetSEVolume() const;

	/// <summary>
	/// BGM�̃{�����[����ݒ肷��
	/// </summary>
	/// <param name="volume"></param>
	void SetBGMVolume(int volume);
	int GetBGMVolume() const;

	/// <summary>
	/// BGM�̌��݂̖炷���ʂ̊���
	/// </summary>
	/// <param name="rate">���ʂ̊���(�ꎞ�I�Ȃ���0.0�`1.0)</param>
	void SetBGMRate(float rate);

	// �T�E���h�����Z�[�u
	void SaveSoundConfig();
private:
	// �T�E���h�f�[�^
	struct SoundData
	{
		SoundData(int h, SoundType t) :
			soundHandle(h),
			soundType(t)
		{}

		int soundHandle = -1;
		SoundType soundType;
	};

	// �ύX�����T�E���h�����t�@�C���ɏ�������
	struct SoundConfigInfo
	{
		char signature[5];			// "SND_"
		float version;				// 1.0
		unsigned short volumeSE;	// 0�`255	
		unsigned short volumeBGM;	// 0�`255
	};

	// ���ʉ��Ɖ��y�̉���
	int m_volumeSE = 100;
	int m_volumeBGM = 40;

	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	SoundManager();
	// �R�s�[��������֎~����
	SoundManager(const SoundManager&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const SoundManager&) = delete;		// ������֎~

	// �I�������T�E���h�^�C�v�̃n���h����Ԃ�
	int GetCurrentSoundHandle(SoundType sound);

	// ���f�[�^�Ǎ�
	void LoadData();

	// ���̐ݒ��Ǎ�
	void LoadSoundConfig();

private:
	// ���f�[�^
	std::vector<SoundData> m_soundData;

	// �~���[�W�b�N�f�[�^�n���h��
	int m_hMusic;
};
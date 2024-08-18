#include "SoundManager.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �T�E���h�ݒ�t�@�C�����
	constexpr char sound_file_signature[] = "SND_";
	constexpr char sound_config_file_path[] = "./sound.conf";
	constexpr float sound_config_version = 1.0f;
	// 1���[�g�������̋���
	constexpr float kMetreDistance = 16.0f;
	// 3D�T�E���h�f�[�^�̕������鋗��
	constexpr float k3DSoundDistance = 1800.0f;
}

void SoundManager::LoadSoundConfig()
{
	SoundConfigInfo conf = {};
	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "rb");
	if (fp)
	{
		fread(&conf, sizeof(conf), 1, fp);
		fclose(fp);
		m_volumeBGM = conf.volumeBGM;
		m_volumeSE = conf.volumeSE;
	}
}

void SoundManager::SaveSoundConfig()
{
	SoundConfigInfo conf = {};
	memcpy_s(conf.signature, sizeof(conf.signature), sound_file_signature, sizeof(sound_file_signature));

	conf.version = sound_config_version;
	conf.volumeSE = m_volumeSE;
	conf.volumeBGM = m_volumeBGM;

	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "wb");
	if (fp)
	{
		fwrite(&conf, sizeof(conf), 1, fp);
		fclose(fp);
	}
}

SoundManager::~SoundManager()
{
	SaveSoundConfig();

	// ���ʉ��f�[�^
	for (auto& soundData : m_soundData)
	{
		DeleteSoundMem(soundData.second);
	}
	m_soundData.clear();

	// �ȃf�[�^
	DeleteSoundMem(m_hMusic);
}

void SoundManager::UpdateBGM()
{
	if (CheckSoundMem(m_hMusic) == 0)
	{
		int volumePal = (255 / 100) * m_volumeBGM;
		ChangeVolumeSoundMem(volumePal, m_hMusic);
		PlaySoundMem(m_hMusic, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::Set3DSoundListener(VECTOR pos, VECTOR frontPos)
{
	Set3DSoundListenerPosAndFrontPos_UpVecY(pos, frontPos);
}

void SoundManager::Play3DSound(SoundType sound, VECTOR pos)
{
	int volumePal = (255 / 100) * m_volumeSE;
	ChangeVolumeSoundMem(m_volumeSE, m_soundData[sound]);
	// �����������鋗����ݒ肷��
	SetNextPlay3DRadiusSoundMem(k3DSoundDistance, m_soundData[sound]);
	// 3D�T�E���h���Đ�����ʒu���w��
	SetNextPlay3DPositionSoundMem(pos, m_soundData[sound]);
	// �w�肵���T�E���h���Đ�
	PlaySoundMem(m_soundData[sound], DX_PLAYTYPE_BACK);
}

void SoundManager::PlaySE(SoundType sound)
{
	int volumePal = (255 / 100) * m_volumeSE;
	ChangeVolumeSoundMem(m_volumeSE, m_soundData[sound]);
	PlaySoundMem(m_soundData[sound], DX_PLAYTYPE_BACK);
}

bool SoundManager::IsPlaying(SoundType sound)
{
	return CheckSoundMem(m_soundData[sound]);
}

void SoundManager::SetSEVolume(int volume)
{
	m_volumeSE = volume;
}

int SoundManager::GetSEVolume() const
{
	return m_volumeSE;
}

void SoundManager::SetBGMVolume(int volume)
{
	m_volumeBGM = volume;
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hMusic);
}

int SoundManager::GetBGMVolume() const
{
	return m_volumeBGM;
}

void SoundManager::SetBGMRate(float rate)
{
	assert(0.0f <= rate && rate <= 1.0f);
	ChangeVolumeSoundMem(static_cast<int>(static_cast<float>(m_volumeBGM) * rate), m_hMusic);
}

SoundManager::SoundManager() :
	m_soundData(),
	m_hMusic(-1)
{
	// �T�E���h�ݒ�̓ǂݍ���
	LoadSoundConfig();
	// �f�[�^�̓ǂݍ���
	LoadData();
	// �P���[�g���ɑ�������l��ݒ肷��
	Set3DSoundOneMetre(kMetreDistance);
}

void SoundManager::LoadData()
{
	// �~���[�W�b�N
	m_hMusic = LoadSoundMem("Data/MusicData/Getsurin_Meikyuu.mp3");
	// 2D�T�E���h
	m_soundData[SoundType::select] = LoadSoundMem("Data/SoundData/SELECT.wav");
	m_soundData[SoundType::shot] = LoadSoundMem("Data/SoundData/RINGO.wav");
	m_soundData[SoundType::sprShot] = LoadSoundMem("Data/SoundData/RINGO2.wav");
	m_soundData[SoundType::shotHit] = LoadSoundMem("Data/SoundData/SHOTHIT.mp3");
	m_soundData[SoundType::zakkirin] = LoadSoundMem("Data/SoundData/ZAKKIRIN.wav");
	// 3D�T�E���h
	SetCreate3DSoundFlag(true);
	m_soundData[SoundType::enemyVoice] = LoadSoundMem("Data/SoundData/NEFFY_NORMAL.wav");
	m_soundData[SoundType::enemyDamage] = LoadSoundMem("Data/SoundData/NEFFY_DAMAGE01.wav");
	m_soundData[SoundType::enemyDeath] = LoadSoundMem("Data/SoundData/NEFFY_DAMAGE02.wav");
	m_soundData[SoundType::enemyBirdVoice] = LoadSoundMem("Data/SoundData/NEFFY_KARASU.wav");
	SetCreate3DSoundFlag(false);
}

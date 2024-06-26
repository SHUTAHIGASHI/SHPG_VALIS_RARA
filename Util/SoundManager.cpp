#include "SoundManager.h"
#include "Game.h"
#include <cassert>

namespace
{
	constexpr char sound_file_signature[] = "SND_";
	constexpr char sound_config_file_path[] = "./sound.conf";
	constexpr float sound_config_version = 1.0f;
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

	// 効果音データ
	for (auto& soundData : m_soundData)
	{
		DeleteSoundMem(soundData.soundHandle);
	}
	m_soundData.clear();

	// 曲データ
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

void SoundManager::PlaySE(SoundType sound)
{
	int volumePal = (255 / 100) * m_volumeSE;
	ChangeVolumeSoundMem(m_volumeSE, GetCurrentSoundHandle(sound));
	PlaySoundMem(GetCurrentSoundHandle(sound), DX_PLAYTYPE_BACK);
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
	LoadSoundConfig();
	LoadData();
}

int SoundManager::GetCurrentSoundHandle(SoundType sound)
{
	int currentSound = -1;

	for (auto& soundData : m_soundData)
	{
		if (soundData.soundType == sound)
		{
			currentSound = soundData.soundHandle;
			break;
		}
	}

	return currentSound;
}

void SoundManager::LoadData()
{
	// サウンド
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/Select.wav"), SoundType::select));

	// ミュージック
	m_hMusic = LoadSoundMem("Data/MusicData/Getsurin_Meikyuu.mp3");
}

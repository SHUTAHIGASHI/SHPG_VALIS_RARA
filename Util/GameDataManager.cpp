#include "GameDataManager.h"
#include "Game.h"
#include <iostream>
#include <fstream>

namespace
{
	// ゲーム設定ファイル情報
	constexpr char file_signature[] = "SET_";
	constexpr char config_file_path[] = "./setting.conf";
	constexpr float config_version = 1.0f;
}

GameDataManager::~GameDataManager()
{
	// ゲームデータ保存
	SaveCharacterData();
}

void GameDataManager::SaveCharacterData()
{
	GameConfigInfo conf = {};
	memcpy_s(conf.signature, sizeof(conf.signature), file_signature, sizeof(file_signature));

	conf.version = config_version;
	conf.mouseSensitivity = m_mouseSensitivity;

	FILE* fp = nullptr;
	fopen_s(&fp, config_file_path, "wb");
	if (fp)
	{
		fwrite(&conf, sizeof(conf), 1, fp);
		fclose(fp);
	}
}

void GameDataManager::LoadCharacterData()
{
	GameConfigInfo conf = {};
	FILE* fp = nullptr;
	fopen_s(&fp, config_file_path, "rb");
	if (fp)
	{
		fread(&conf, sizeof(conf), 1, fp);
		fclose(fp);
		m_mouseSensitivity = conf.mouseSensitivity;
	}
}

GameDataManager::GameDataManager() :
	m_mouseSensitivity(1.0f)
{
	// ゲームデータ読み込み
	LoadCharacterData();
}
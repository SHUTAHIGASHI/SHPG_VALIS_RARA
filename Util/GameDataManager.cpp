#include "GameDataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

GameDataManager::~GameDataManager()
{
	// キャラクターデータ保存
	SaveCharacterData();
	// キャラクターデータ削除
	delete m_charaState;
}

void GameDataManager::SaveTempData(charaState data)
{
	// 一時データに保存
	m_charaState->level = data.level;
	m_charaState->exp = data.exp;
	m_charaState->hunger = data.hunger;
	m_charaState->happy = data.happy;
	m_charaState->sleep = data.sleep;
}

void GameDataManager::SetData(charaState& data)
{
	// キャラクターの状態
	data.level = m_charaState->level;
	data.exp = m_charaState->exp;
	data.hunger = m_charaState->hunger;
	data.happy = m_charaState->happy;
	data.sleep = m_charaState->sleep;
}

void GameDataManager::SaveCharacterData()
{
	// CSVファイルに書き込む
	std::ofstream file(Game::kGameDataFileName);	// CSVファイルを開く
	// ファイルが開けたか確認
	if (file.is_open())
	{
		// ヘッダー書き込み
		file << "レベル,経験値,空腹,幸福,眠気," << std::endl;
		// キャラクターの状態書き込み
		file << m_charaState->level << "," << m_charaState->exp << "," << m_charaState->hunger << "," << m_charaState->happy << "," << m_charaState->sleep << "," << std::endl;
		// ファイルを閉じる
		file.close();
	}
	else
	{
		// ステージデータ読み込みエラー処理
		MessageBox(NULL, "ステージデータ読み込み失敗", "", MB_OK);
	}
}

void GameDataManager::LoadCharacterData()
{
	std::ifstream file(Game::kGameDataFileName);	// CSVファイルを開く
	std::string line;								// 1行分の文字列
	std::vector<std::string> tempData;			// 一時ステージデータ
	int lineCount = 0;								// 行数
	int strFirst = 0, strLast = 0;					// 文字列の最初と最後

	// ファイルが開けたか確認
	if (file.is_open())
	{
		// ファイルから行を読み込む
		while (getline(file, line))
		{
			// 1行目はスキップ
			if (lineCount != 0)
			{
				// 区切り文字で文字列を分割
				strFirst = 0, strLast = 0;
				// 一時ステージデータリセット
				tempData.clear();
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == ',')
					{
						// 区切り文字で文字列を分割
						strLast = i;
						// 文字列を取得
						std::string str;
						for (int j = strFirst; j < strLast; j++)
						{
							// 文字列を取得
							str += line[j];
						}
						// 一時ステージデータに追加
						tempData.push_back(str);
						// 次の文字へ
						strFirst = strLast + 1;
					}
				}

				// データに変換
				// キャラクターの状態
				m_charaState->level = static_cast<int>(std::stoi(tempData[0]));
				m_charaState->exp = static_cast<double>(std::stoi(tempData[1]));
				m_charaState->hunger = static_cast<double>(std::stoi(tempData[2]));
				m_charaState->happy = static_cast<double>((std::stoi(tempData[3])));
				m_charaState->sleep = static_cast<double>((std::stoi(tempData[4])));
			}
			// 行数をカウント
			lineCount++;
		}
		// ファイルを閉じる
		file.close();
	}
	else
	{
		// ステージデータ読み込みエラー処理
		MessageBox(NULL, "ステージデータ読み込み失敗", "", MB_OK);
	}
}

GameDataManager::GameDataManager():
	m_charaState(new charaState())
{
	// キャラクターデータ読み込み
	LoadCharacterData();
}
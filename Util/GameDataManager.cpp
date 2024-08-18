#include "GameDataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

GameDataManager::~GameDataManager()
{
	// �L�����N�^�[�f�[�^�ۑ�
	SaveCharacterData();
	// �L�����N�^�[�f�[�^�폜
	delete m_charaState;
}

void GameDataManager::SaveTempData(charaState data)
{
	// �ꎞ�f�[�^�ɕۑ�
	m_charaState->level = data.level;
	m_charaState->exp = data.exp;
	m_charaState->hunger = data.hunger;
	m_charaState->happy = data.happy;
	m_charaState->sleep = data.sleep;
}

void GameDataManager::SetData(charaState& data)
{
	// �L�����N�^�[�̏��
	data.level = m_charaState->level;
	data.exp = m_charaState->exp;
	data.hunger = m_charaState->hunger;
	data.happy = m_charaState->happy;
	data.sleep = m_charaState->sleep;
}

void GameDataManager::SaveCharacterData()
{
	// CSV�t�@�C���ɏ�������
	std::ofstream file(Game::kGameDataFileName);	// CSV�t�@�C�����J��
	// �t�@�C�����J�������m�F
	if (file.is_open())
	{
		// �w�b�_�[��������
		file << "���x��,�o���l,��,�K��,���C," << std::endl;
		// �L�����N�^�[�̏�ԏ�������
		file << m_charaState->level << "," << m_charaState->exp << "," << m_charaState->hunger << "," << m_charaState->happy << "," << m_charaState->sleep << "," << std::endl;
		// �t�@�C�������
		file.close();
	}
	else
	{
		// �X�e�[�W�f�[�^�ǂݍ��݃G���[����
		MessageBox(NULL, "�X�e�[�W�f�[�^�ǂݍ��ݎ��s", "", MB_OK);
	}
}

void GameDataManager::LoadCharacterData()
{
	std::ifstream file(Game::kGameDataFileName);	// CSV�t�@�C�����J��
	std::string line;								// 1�s���̕�����
	std::vector<std::string> tempData;			// �ꎞ�X�e�[�W�f�[�^
	int lineCount = 0;								// �s��
	int strFirst = 0, strLast = 0;					// ������̍ŏ��ƍŌ�

	// �t�@�C�����J�������m�F
	if (file.is_open())
	{
		// �t�@�C������s��ǂݍ���
		while (getline(file, line))
		{
			// 1�s�ڂ̓X�L�b�v
			if (lineCount != 0)
			{
				// ��؂蕶���ŕ�����𕪊�
				strFirst = 0, strLast = 0;
				// �ꎞ�X�e�[�W�f�[�^���Z�b�g
				tempData.clear();
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] == ',')
					{
						// ��؂蕶���ŕ�����𕪊�
						strLast = i;
						// ��������擾
						std::string str;
						for (int j = strFirst; j < strLast; j++)
						{
							// ��������擾
							str += line[j];
						}
						// �ꎞ�X�e�[�W�f�[�^�ɒǉ�
						tempData.push_back(str);
						// ���̕�����
						strFirst = strLast + 1;
					}
				}

				// �f�[�^�ɕϊ�
				// �L�����N�^�[�̏��
				m_charaState->level = static_cast<int>(std::stoi(tempData[0]));
				m_charaState->exp = static_cast<double>(std::stoi(tempData[1]));
				m_charaState->hunger = static_cast<double>(std::stoi(tempData[2]));
				m_charaState->happy = static_cast<double>((std::stoi(tempData[3])));
				m_charaState->sleep = static_cast<double>((std::stoi(tempData[4])));
			}
			// �s�����J�E���g
			lineCount++;
		}
		// �t�@�C�������
		file.close();
	}
	else
	{
		// �X�e�[�W�f�[�^�ǂݍ��݃G���[����
		MessageBox(NULL, "�X�e�[�W�f�[�^�ǂݍ��ݎ��s", "", MB_OK);
	}
}

GameDataManager::GameDataManager():
	m_charaState(new charaState())
{
	// �L�����N�^�[�f�[�^�ǂݍ���
	LoadCharacterData();
}
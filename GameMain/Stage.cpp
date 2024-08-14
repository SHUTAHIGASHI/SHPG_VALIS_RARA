#include "Stage.h"
#include "Game.h"
#include "Load.h"

namespace
{
	// �X�e�[�W�̔z��
	std::vector<std::vector<int>> kStageList =
	{ 
		{ 0,0,0,0,0,2,0,0,0,0,0 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
		{ 1,1,1,0,1,1,1,0,1,1,1 } ,
	};
}

Stage::Stage():
m_currentStageData(kStageList),
m_stageWidth(kStageList[0].size()),
m_stageHeight(kStageList.size())
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	// �u���b�N�̐���
	CreateStage();
}

void Stage::Update()
{
}

void Stage::Draw()
{
	// �u���b�N�̕`��
	for (auto& cube : m_cubes)
	{
		MV1DrawModel(cube.handle);
	}
}

void Stage::GetTile(VECTOR pos, int&_x, int&_z)
{
	// �X�e�[�W�̏����擾
	for (int z = 0; z < m_currentStageData.size(); z++)
	{
		for (int x = 0; x < m_currentStageData[z].size(); x++)
		{
			// �u���b�N�̍��W�ϊ�
			auto tempX = x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize);
			auto tempZ = z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize);
			// �u���b�N�͈͓̔���
			if (pos.x > tempX - Game::k3DChipSize / 2 && pos.x < tempX + Game::k3DChipSize / 2
				&& pos.z > tempZ - Game::k3DChipSize / 2 && pos.z < tempZ + Game::k3DChipSize / 2)
			{
				// �X�e�[�W�̏���Ԃ�
				_x = x;
				_z = z;
				return;
			}
		}
	}
}

int Stage::GetTileHandle(int x, int z)
{
	for (auto& cube : m_cubes)
	{
		if (cube.x == x && cube.z == z)
		{
			return cube.handle;
		}
	}
}

void Stage::CreateStage()
{
	// �X�e�[�W�̏�����
	for (int z = 0; z < m_currentStageData.size(); z++)
	{
		for (int x = 0; x < m_currentStageData[z].size(); x++)
		{
			if (m_currentStageData[z][x] == 1)
			{
				// �u���b�N�̐���
				m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube"))));
				// �u���b�N�̈ʒu
				VECTOR pos = VGet(
					x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
					-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
					z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
				);
				// �u���b�N�̍��W�w��
				MV1SetPosition(m_cubes.back().handle, pos);
			}
			else if (m_currentStageData[z][x] == 2)
			{
				// �u���b�N�̐���
				m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("goal"))));
				// �u���b�N�̈ʒu
				VECTOR pos = VGet(
					x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
					0.0f,
					z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
				);
				// �u���b�N�̍��W�w��
				MV1SetPosition(m_cubes.back().handle, pos);
			}
		}
	}
}

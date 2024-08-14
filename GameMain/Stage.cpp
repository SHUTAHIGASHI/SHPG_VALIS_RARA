#include "Stage.h"
#include "Game.h"
#include "Load.h"

namespace
{
	// �X�e�[�W�̔z��
	std::vector<std::vector<int>> kStageList =
	{ 
		{ 0,0,0,0,0,1,0,0,0,0,0 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 } ,
		{ 1,1,1,1,1,1,1,1,1,1,1 }
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
	// �X�e�[�W�̏�����
	for (int z = 0; z < m_currentStageData.size(); z++)
		{
			for (int x = 0; x < m_currentStageData[z].size(); x++)
			{
				if (m_currentStageData[z][x] == 1)
				{
					// �u���b�N�̐���
					m_cubeHandle.push_back(MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube")));
					// �u���b�N�̈ʒu
					VECTOR pos = VGet(
						x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
						-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
						z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
					);
					// �u���b�N�̍��W�w��
					MV1SetPosition(m_cubeHandle.back(), pos);
				}
			}
		}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	// �u���b�N�̕`��
	for (auto& cube : m_cubeHandle)
	{
		MV1DrawModel(cube);
	}
}

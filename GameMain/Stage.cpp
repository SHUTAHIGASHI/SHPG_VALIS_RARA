#include "Stage.h"
#include "Game.h"
#include "Load.h"

using namespace StageTile;

namespace
{
	// �X�e�[�W�̔z��
	std::vector<std::vector<int>> kStageList =
	{ 
		// �X�e�[�W(30 * 30)
		{ EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN } ,

		{ WL,WL,WL,WL,WL,WL,WL,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,WL,WL,WL,WL,WL,WL,WL,WL } ,

		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,
		{ WL,CH,CH,CH,CH,CH,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,NI,NI,NI,NI,NI,NI,WL } ,

		{ WL,WL,WL,WL,WL,WL,WL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,WL,WL,WL,WL,WL,WL,WL,WL } ,

		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,SW,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,
		{ WL,MY,MY,MY,MY,MY,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,RA,RA,RA,RA,RA,RA,WL } ,

		{ WL,WL,WL,WL,WL,WL,WL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,WL,WL,WL,WL,WL,WL,WL,WL } ,

		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL } ,
		{ WL,NE,NE,NE,NE,NE,F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2,VI,VI,VI,VI,VI,VI,WL },

		{ WL,WL,WL,WL,WL,WL,WL,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,WL,WL,WL,WL,WL,WL,WL,WL } ,
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
			switch (m_currentStageData[z][x])
			{
			case EN:
				break;
			case FL:
				CreateFloar(x, z);
				break;
			case WL:
				CreateWall(x, z);
				break;
			case F1:
				CreateFence(x, z, false);
				break;
			case F2:
				CreateFence(x, z, true);
				break;
			case SW:
				CreateSwitch(x, z);
				break;
			case CH:
				CreateObject(x, z, Load::GetInstance().GetModelHandle("cube_chino"));
				break;
			case MY:
				CreateObject(x, z, Load::GetInstance().GetModelHandle("cube_myu"));
				break;
			case NE:
				CreateObject(x, z, Load::GetInstance().GetModelHandle("cube_neffy"));
				break;
			case NI:
				CreateObject(x, z, Load::GetInstance().GetModelHandle("cube_nina"));
				break;
			case RA:
				CreateObject(x, z, Load::GetInstance().GetModelHandle("cube_rara"));
				break;
			case VI:
				CreateObject(x, z, Load::GetInstance().GetModelHandle("cube_vitte"));
				break;
			case GL:
				CreateGoal(x, z);
				break;
			}
		}
	}
}

void Stage::CreateObject(int x, int z, int handle)
{
	// �u���b�N�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(handle)));
	// �u���b�N�̈ʒu
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �u���b�N�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateFloar(int x, int z)
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

void Stage::CreateWall(int x, int z)
{
	// �u���b�N�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube"))));
	// �u���b�N�̈ʒu
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-Game::k3DChipSize / 2,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �u���b�N�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateFence(int x, int z, bool isRota)
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

	// �t�F���X�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("fence"))));
	// �t�F���X�̈ʒu
	VECTOR fencePos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-Game::kCharaHeight,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �t�F���X�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, fencePos);
	// �t�F���X�̉�]
	if (isRota)
	{
		MV1SetRotationXYZ(m_cubes.back().handle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	}
}

void Stage::CreateSwitch(int x, int z)
{
// �u���b�N�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("switch"))));
	// �u���b�N�̈ʒu
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		0.0f,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �u���b�N�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateGoal(int x, int z)
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

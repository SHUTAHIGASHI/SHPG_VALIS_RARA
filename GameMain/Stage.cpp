#include "Stage.h"
#include "Game.h"
#include "Load.h"

using namespace StageTile;

namespace
{
	// �X�e�[�W�̔z��
	std::vector<std::vector<int>> kStageList =
	{ 
		// �X�e�[�W
		{ EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN,EN } ,

		{ WL,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,WL } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,SP,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,SP,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,S1,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,S4,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,CH,CH,CH,CH,CH,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,NI,NI,NI,NI,NI,F2 } ,
		{ F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,S2,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,S5,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,MY,MY,MY,MY,MY,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,RA,RA,RA,RA,RA,F2 } ,
		{ F2,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,S3,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,S6,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,SP,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,SP,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 } ,
		{ F2,NE,NE,NE,NE,NE,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,FL,VI,VI,VI,VI,VI,F2 },
		{ WL,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,F1,WL } ,
	};
}

namespace
{
	// �T�v���C�Y���b�Z�[�W�`��ʒu
	static const VECTOR kSurpriseMsgPos = VGet(0.0f, 4000.0f, 6000.0f);
}

Stage::Stage():
m_cubes(),
m_currentStageData(kStageList),
m_hSurpriseMsg(),
m_isDrawSurpriseMsg(false),
m_stageWidth(static_cast<int>(kStageList[0].size())),
m_stageHeight(static_cast<int>(kStageList.size()))
{
}

Stage::~Stage()
{
	// �u���b�N�̉��
	for (auto& cube : m_cubes)
	{
		MV1DeleteModel(cube.handle);
	}
	// �T�v���C�Y���b�Z�[�W�̉��
	for (auto& msg : m_hSurpriseMsg)
	{
		DeleteGraph(msg);
	}
}

void Stage::Init()
{
	// �u���b�N�̐���
	CreateStage();
}

void Stage::Update()
{
	// �X�C�b�`�̊m�F
	CheckSwitch();
}

void Stage::Draw()
{
	// �u���b�N�̕`��
	for (auto& cube : m_cubes)
	{
		MV1DrawModel(cube.handle);
	}

	// �T�v���C�Y���b�Z�[�W�̕`��
	if (m_isDrawSurpriseMsg)
	{
		DrawSurpriseMessage();
	}
}

void Stage::SwitchOn(int x, int z)
{
	if (m_currentStageData[z][x] == S1)
	{
		m_isSwitches[0] = true;
	}
	else if (m_currentStageData[z][x] == S2)
	{
		if (m_isSwitches[0])
		{
			m_isSwitches[1] = true;
		}
		else
		{
			return;
		}
	}
	else if (m_currentStageData[z][x] == S3)
	{
		if (m_isSwitches[1])
		{
			m_isSwitches[2] = true;
		}
		else
		{
			return;
		}
	}
	else if (m_currentStageData[z][x] == S4)
	{
		if (m_isSwitches[2])
		{
			m_isSwitches[3] = true;
		}
		else
		{
			return;
		}
	}
	else if (m_currentStageData[z][x] == S5)
	{
		if (m_isSwitches[3])
		{
			m_isSwitches[4] = true;
		}
		else
		{
			return;
		}
	}
	else if (m_currentStageData[z][x] == S6)
	{
		if (m_isSwitches[4])
		{
			m_isSwitches[5] = true;
		}
		else
		{
			return;
		}
	}

	// �X�C�b�`�̍�����ύX
	for (auto& cube : m_cubes)
	{
		if (cube.x == x && cube.z == z)
		{
			if (cube.name == "switch")
			{
				MV1SetPosition(cube.handle, VGet(
					x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
					Game::k3DChipSize,
					z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)));
			}
		}
	}
}

int Stage::GetSpawnPointNum()
{
	int count = 0;

	for (int z = 0; z < m_currentStageData.size(); z++)
	{
		for (int x = 0; x < m_currentStageData[z].size(); x++)
		{
			if (m_currentStageData[z][x] == SP)
			{
				count++;
			}
		}
	}

	return count;
}

VECTOR Stage::GetSpawnPoint(int num)
{
	int count = 0;

	for (int z = 0; z < m_currentStageData.size(); z++)
	{
		for (int x = 0; x < m_currentStageData[z].size(); x++)
		{
			if (m_currentStageData[z][x] == SP)
			{
				if (count == num)
				{
					return VGet(
						x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
						0.0f,
						z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
					);
				}
				else
				{
					count++;
				}
			}
		}
	}

	return VECTOR();
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

	return -1;
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
			case GL:
				CreateGoal(x, z);
				break;
			case SP:
				CreateFloar(x, z);
				break;
			case S1:
				CreateSwitch(x, z);
				break;
			case S2:
				CreateSwitch(x, z);
				break;
			case S3:
				CreateSwitch(x, z);
				break;
			case S4:
				CreateSwitch(x, z);
				break;
			case S5:
				CreateSwitch(x, z);
				break;
			case S6:
				CreateSwitch(x, z);
				break;
			}
		}
	}
}

void Stage::CreateObject(int x, int z, int handle)
{
	// �u���b�N�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(handle), "other"));
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
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube")), "cube"));
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
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube")), "wall"));
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
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube")), "cube"));
	// �u���b�N�̈ʒu
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �u���b�N�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, pos);

	// �t�F���X�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("fence")), "fence"));
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
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube")), "cube"));
	// �u���b�N�̈ʒu
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �u���b�N�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, pos);

	// �X�C�b�`�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("switch")), "switch"));
	// �X�C�b�`�̈ʒu
	VECTOR switchPos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		0.0f,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �X�C�b�`�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, switchPos);

	// �X�C�b�`�̒ǉ�
	m_isSwitches.push_back(false);
}

void Stage::CreateGoal(int x, int z)
{
	// �u���b�N�̐���
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("goal")), "goal"));
	// �u���b�N�̈ʒu
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		0.0f,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// �u���b�N�̍��W�w��
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CheckSwitch()
{
	for (int i = 0; i < m_isSwitches.size(); i++)
	{
		// ���ԂɃX�C�b�`��������Ă��邩�m�F
		if (!m_isSwitches[i])
		{
			return;
		}
	}

	// �X�C�b�`���S�ĉ�����Ă�����
	if (!m_isDrawSurpriseMsg)
	{
		CreateSurpriseMessage();
	}
}

void Stage::CreateSurpriseMessage()
{
	// �T�v���C�Y���b�Z�[�W�̐���
	m_hSurpriseMsg.push_back(LoadGraph("Data/ImageData/SpMessage1.png"));
	m_hSurpriseMsg.push_back(LoadGraph("Data/ImageData/SpMessage2.png"));

	// �T�v���C�Y���b�Z�[�W�̕\��
	m_isDrawSurpriseMsg = true;
}

void Stage::DrawSurpriseMessage()
{
	// �T�v���C�Y���b�Z�[�W�̕`��
	int count = 0;
	for (auto& msg : m_hSurpriseMsg)
	{
		// �T�v���C�Y���b�Z�[�W�̕`��
		VECTOR drawPos = VGet(kSurpriseMsgPos.x, kSurpriseMsgPos.y - (count * 3000.0f), kSurpriseMsgPos.z);
		DrawBillboard3D(drawPos, 0.5f, 0.5f, 6000.0f, 0.0f, msg, true);
		count++;
	}
}

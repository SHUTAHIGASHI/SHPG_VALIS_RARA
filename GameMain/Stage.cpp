#include "Stage.h"
#include "Game.h"
#include "Load.h"

using namespace StageTile;

namespace
{
	// ステージの配列
	std::vector<std::vector<int>> kStageList =
	{ 
		// ステージ(30 * 30)
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
	// ブロックの生成
	CreateStage();
}

void Stage::Update()
{
}

void Stage::Draw()
{
	// ブロックの描画
	for (auto& cube : m_cubes)
	{
		MV1DrawModel(cube.handle);
	}
}

void Stage::GetTile(VECTOR pos, int&_x, int&_z)
{
	// ステージの情報を取得
	for (int z = 0; z < m_currentStageData.size(); z++)
	{
		for (int x = 0; x < m_currentStageData[z].size(); x++)
		{
			// ブロックの座標変換
			auto tempX = x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize);
			auto tempZ = z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize);
			// ブロックの範囲内か
			if (pos.x > tempX - Game::k3DChipSize / 2 && pos.x < tempX + Game::k3DChipSize / 2
				&& pos.z > tempZ - Game::k3DChipSize / 2 && pos.z < tempZ + Game::k3DChipSize / 2)
			{
				// ステージの情報を返す
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
	// ステージの初期化
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
	// ブロックの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(handle)));
	// ブロックの位置
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// ブロックの座標指定
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateFloar(int x, int z)
{
	// ブロックの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube"))));
	// ブロックの位置
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// ブロックの座標指定
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateWall(int x, int z)
{
	// ブロックの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube"))));
	// ブロックの位置
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-Game::k3DChipSize / 2,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// ブロックの座標指定
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateFence(int x, int z, bool isRota)
{
	// ブロックの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube"))));
	// ブロックの位置
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-(Game::kCharaHeight + (Game::k3DChipSize / 2)),
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// ブロックの座標指定
	MV1SetPosition(m_cubes.back().handle, pos);

	// フェンスの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("fence"))));
	// フェンスの位置
	VECTOR fencePos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		-Game::kCharaHeight,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// フェンスの座標指定
	MV1SetPosition(m_cubes.back().handle, fencePos);
	// フェンスの回転
	if (isRota)
	{
		MV1SetRotationXYZ(m_cubes.back().handle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	}
}

void Stage::CreateSwitch(int x, int z)
{
// ブロックの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("switch"))));
	// ブロックの位置
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		0.0f,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// ブロックの座標指定
	MV1SetPosition(m_cubes.back().handle, pos);
}

void Stage::CreateGoal(int x, int z)
{
	// ブロックの生成
	m_cubes.push_back(TileData(x, z, MV1DuplicateModel(Load::GetInstance().GetModelHandle("goal"))));
	// ブロックの位置
	VECTOR pos = VGet(
		x * Game::k3DChipSize - ((m_currentStageData[z].size() / 2) * Game::k3DChipSize),
		0.0f,
		z * -Game::k3DChipSize + ((m_currentStageData.size() / 2) * Game::k3DChipSize)
	);
	// ブロックの座標指定
	MV1SetPosition(m_cubes.back().handle, pos);
}

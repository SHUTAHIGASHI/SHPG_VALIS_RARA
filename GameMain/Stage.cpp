#include "Stage.h"
#include "Game.h"
#include "Load.h"

namespace
{
	// ステージの配列
	std::vector<std::vector<int>> kStageList =
	{ 
		{ 1,1,1,1,1 } ,
		{ 1,1,1,1,1 } ,
		{ 1,1,0,1,1 } ,
		{ 1,1,1,1,1 } ,
		{ 1,1,1,1,1 } 
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
	// ステージの初期化
	for (int z = 0; z < m_currentStageData.size(); z++)
		{
			for (int x = 0; x < m_currentStageData[z].size(); x++)
			{
				if (m_currentStageData[z][x] == 1)
				{
					// ブロックの生成
					m_cubeHandle.push_back(MV1DuplicateModel(Load::GetInstance().GetModelHandle("cube")));
					// ブロックの位置
					VECTOR pos = VGet(x * 190.0f, -Game::kCharaHeight, z * 190.0f);
					// ブロックの座標指定
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
	// ブロックの描画
	for (auto& cube : m_cubeHandle)
	{
		MV1DrawModel(cube);
	}

	// ステージライン描画
	DrawStageLine();

	// デバッグ用
	MV1SetPosition(Load::GetInstance().GetModelHandle("cube"), VGet(0.0f, 0.0f, 0.0f));
	MV1DrawModel(Load::GetInstance().GetModelHandle("cube"));
}

void Stage::DrawStageLine()
{
	// グリッドを表示
	for (float z = -Game::kStageSizeZ; z <= Game::kStageSizeZ; z += 100.0f)
	{
		VECTOR start = VGet(-Game::kStageSizeX, -Game:: kCharaHeight, z);
		VECTOR end = VGet(Game::kStageSizeX, -Game::kCharaHeight, z);
		DrawLine3D(start, end, 0x00ff00);
	}

	for (float x = -Game::kStageSizeX; x <= Game::kStageSizeX; x += 100.0f)
	{
		VECTOR start = VGet(x, -Game::kCharaHeight, -Game::kStageSizeZ);
		VECTOR end = VGet(x, -Game::kCharaHeight, Game::kStageSizeZ);
		DrawLine3D(start, end, 0xff0000);
	}
}

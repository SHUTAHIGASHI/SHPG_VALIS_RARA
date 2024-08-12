#include "Stage.h"
#include "Game.h"
#include "Load.h"

namespace
{
	// �X�e�[�W�̔z��
	std::list<std::list<int>> kStageList = 
	{ 
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ,
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } 
	};
}

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	// �X�e�[�W���C���`��
	DrawStageLine();

	// �f�o�b�O�p
	MV1SetPosition(Load::GetInstance().GetModelHandle("cube"), VGet(0.0f, 0.0f, 0.0f));
	MV1DrawModel(Load::GetInstance().GetModelHandle("cube"));
}

void Stage::DrawStageLine()
{
	// �O���b�h��\��
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

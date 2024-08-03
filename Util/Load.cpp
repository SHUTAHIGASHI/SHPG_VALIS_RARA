#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// ���f���f�[�^
	m_data["skydome"] = MV1LoadModel("Data/ModelData/SKYDOME.mv1");
	// �摜�f�[�^
	m_data["player"] = LoadGraph("Data/ImageData/RaraTest.png");
	m_data["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_data["lockCursor"] = LoadGraph("Data/ImageData/LockCursor.png");
	m_data["hitCursor"] = LoadGraph("Data/ImageData/HitCursor.png");
	m_data["shot"] = LoadGraph("Data/ImageData/Ringo.png");
	m_data["chino"] = LoadGraph("Data/ImageData/chinoDot.png");
	m_data["myu"] = LoadGraph("Data/ImageData/myuDot.png");
	m_data["neffy"] = LoadGraph("Data/ImageData/NeffyTest.png");
	m_data["nina"] = LoadGraph("Data/ImageData/ninaDot.png");
	m_data["vitte"] = LoadGraph("Data/ImageData/vitteDot.png");
	m_data["fpsHand"] = LoadGraph("Data/ImageData/RaraGame_FpsHand.png");
}

void Load::DeleteAllData()
{
	// ���f���f�[�^���폜����
	m_data["skydome"] = MV1DeleteModel(m_data["skydome"]);

	// �f�[�^���폜����
	for (auto& data : m_data)
	{
		DeleteGraph(data.second);
	}
	m_data.clear();
}

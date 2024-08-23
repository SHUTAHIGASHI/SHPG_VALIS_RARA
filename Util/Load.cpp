#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// モデルデータ
	m_modelData["skydome"] = MV1LoadModel("Data/ModelData/SKYDOME.mv1");
	m_modelData["cube"] = MV1LoadModel("Data/ModelData/CUBE.mv1");
	m_modelData["fence"] = MV1LoadModel("Data/ModelData/FENCE.mv1");
	m_modelData["switch"] = MV1LoadModel("Data/ModelData/SWITCH.mv1");
	m_modelData["cube_chino"] = MV1LoadModel("Data/ModelData/CUBE_CHINO.mv1");
	m_modelData["cube_myu"] = MV1LoadModel("Data/ModelData/CUBE_MYU.mv1");
	m_modelData["cube_neffy"] = MV1LoadModel("Data/ModelData/CUBE_NEFFY.mv1");
	m_modelData["cube_nina"] = MV1LoadModel("Data/ModelData/CUBE_NINA.mv1");
	m_modelData["cube_rara"] = MV1LoadModel("Data/ModelData/CUBE_RARA.mv1");
	m_modelData["cube_vitte"] = MV1LoadModel("Data/ModelData/CUBE_VITTE.mv1");

	m_modelData["goal"] = MV1LoadModel("Data/ModelData/GOAL.mv1");
	// 画像データ
	m_imageData["player"] = LoadGraph("Data/ImageData/RaraTest.png");
	m_imageData["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_imageData["lockCursor"] = LoadGraph("Data/ImageData/LockCursor.png");
	m_imageData["hitCursor"] = LoadGraph("Data/ImageData/HitCursor.png");
	m_imageData["shot"] = LoadGraph("Data/ImageData/Ringo.png");
	m_imageData["neffy"] = LoadGraph("Data/ImageData/RaraGame_Chara1.png");
	m_imageData["neffy2"] = LoadGraph("Data/ImageData/RaraGame_Chara2.png");
	m_imageData["neffyKarasu"] = LoadGraph("Data/ImageData/RaraGame_NeffyKarasu1.png");
	m_imageData["neffyKarasu2"] = LoadGraph("Data/ImageData/RaraGame_NeffyKarasu2.png");
	m_imageData["fpsHand"] = LoadGraph("Data/ImageData/RaraGame_Hands.png");
}

void Load::DeleteAllData()
{
	// 画像データを削除する
	for (auto& data : m_imageData)
	{
		DeleteGraph(data.second);
	}
	m_imageData.clear();

	// モデルデータを削除する
	for (auto& data : m_modelData)
	{
		DeleteGraph(data.second);
	}
	m_modelData.clear();
}

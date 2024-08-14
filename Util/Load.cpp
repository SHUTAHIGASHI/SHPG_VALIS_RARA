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
	m_modelData["goal"] = MV1LoadModel("Data/ModelData/GOAL.mv1");
	// 画像データ
	m_imageData["player"] = LoadGraph("Data/ImageData/RaraTest.png");
	m_imageData["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_imageData["lockCursor"] = LoadGraph("Data/ImageData/LockCursor.png");
	m_imageData["hitCursor"] = LoadGraph("Data/ImageData/HitCursor.png");
	m_imageData["shot"] = LoadGraph("Data/ImageData/Ringo.png");
	m_imageData["chino"] = LoadGraph("Data/ImageData/chinoDot.png");
	m_imageData["myu"] = LoadGraph("Data/ImageData/myuDot.png");
	m_imageData["neffy"] = LoadGraph("Data/ImageData/NeffyTest.png");
	m_imageData["nina"] = LoadGraph("Data/ImageData/ninaDot.png");
	m_imageData["vitte"] = LoadGraph("Data/ImageData/vitteDot.png");
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

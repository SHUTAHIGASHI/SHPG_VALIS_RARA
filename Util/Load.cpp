#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// データをロードする
	m_graphData["player"] = LoadGraph("Data/ImageData/RaraTest.png");
	m_graphData["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_graphData["lockCursor"] = LoadGraph("Data/ImageData/LockCursor.png");
	m_graphData["shot"] = LoadGraph("Data/ImageData/Ringo.png");
	m_graphData["chino"] = LoadGraph("Data/ImageData/chinoDot.png");
	m_graphData["myu"] = LoadGraph("Data/ImageData/myuDot.png");
	m_graphData["neffy"] = LoadGraph("Data/ImageData/NeffyTest.png");
	m_graphData["nina"] = LoadGraph("Data/ImageData/ninaDot.png");
	m_graphData["vitte"] = LoadGraph("Data/ImageData/vitteDot.png");
}

void Load::DeleteAllData()
{
	// データを削除する
	for (auto& data : m_graphData)
	{
		DeleteGraph(data.second);
	}
	m_graphData.clear();
}

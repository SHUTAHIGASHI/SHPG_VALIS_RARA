#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// �f�[�^�����[�h����
	m_graphData["player"] = LoadGraph("Data/ImageData/RaraTest.png");
	m_graphData["enemy"] = LoadGraph("Data/ImageData/NeffyTest.png");
	m_graphData["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_graphData["lockCursor"] = LoadGraph("Data/ImageData/LockCursor.png");
	m_graphData["shot"] = LoadGraph("Data/ImageData/Ringo.png");
}

void Load::DeleteAllData()
{
	// �f�[�^���폜����
	for (auto& data : m_graphData)
	{
		DeleteGraph(data.second);
	}
	m_graphData.clear();
}

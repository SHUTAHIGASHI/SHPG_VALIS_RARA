#pragma once
#include <vector>
#include <memory>
#include <DxLib.h>

namespace StageTile
{
	constexpr int EN = 0;
	constexpr int FL = 1;
	constexpr int WL = 2;
	constexpr int F1 = 3;
	constexpr int F2 = 4;
	constexpr int GL = 5;
	constexpr int CH = 6;
	constexpr int MY = CH + 1;
	constexpr int NE = MY + 1;
	constexpr int NI = NE + 1;
	constexpr int RA = NI + 1;
	constexpr int VI = RA + 1;
}

struct TileData
{
	TileData(int x, int z, int handle) :
		x(x),
		z(z),
		handle(handle)
	{}
	~TileData()
	{
		handle = -1;
	}

	int x;
	int z;
	int handle;
};

class Stage
{
public:
	// コンストラクタ
	Stage();
	// デストラクタ
	virtual ~Stage();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

	// ステージ情報を返す
	std::vector<std::vector<int>> GetStageData() { return m_currentStageData; }

	// 指定した座標のステージ情報を返す
	void GetTile(VECTOR pos, int &x, int &z);

	// 指定したタイルの状態を返す
	int GetTileHandle(int x, int z);

private:
	// ステージの生成
	void CreateStage();

	// ステージモデルの生成
	void CreateObject(int x, int z, int handle);
	void CreateFloar(int x, int z);
	void CreateWall(int x, int z);
	void CreateFence(int x, int z, bool);
	void CreateGoal(int x, int z);

private:
	// キューブの情報
	std::vector<TileData> m_cubes;

	// 現在のステージの情報
	std::vector<std::vector<int>> m_currentStageData;

	// ステージのサイズ
	int m_stageWidth;
	int m_stageHeight;

};


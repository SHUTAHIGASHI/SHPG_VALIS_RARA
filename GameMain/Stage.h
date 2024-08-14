#pragma once
#include <vector>
#include <memory>
#include <DxLib.h>

enum StageType
{
	STAGE_TYPE_NONE = 0,
	STAGE_TYPE_WALL,
	STAGE_TYPE_GOAL,
	STAGE_TYPE_PLAYER,
	STAGE_TYPE_ENEMY,
	STAGE_TYPE_MAX
};

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

private:
	// キューブの情報
	std::vector<TileData> m_cubes;

	// 現在のステージの情報
	std::vector<std::vector<int>> m_currentStageData;

	// ステージのサイズ
	int m_stageWidth;
	int m_stageHeight;

};


#pragma once
#include <DxLib.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

namespace StageTile
{
	constexpr int EN = 0;
	constexpr int CH = 1;
	constexpr int MY = CH + 1;
	constexpr int NE = MY + 1;
	constexpr int NI = NE + 1;
	constexpr int RA = NI + 1;
	constexpr int VI = RA + 1;
	constexpr int FL = VI + 1;
	constexpr int WL = FL + 1;
	constexpr int F1 = WL + 1;
	constexpr int F2 = F1 + 1;
	constexpr int GL = F2 + 1;
	constexpr int SP = GL + 1;
	constexpr int S1 = SP + 1;
	constexpr int S2 = S1 + 1;
	constexpr int S3 = S2 + 1;
	constexpr int S4 = S3 + 1;
	constexpr int S5 = S4 + 1;
	constexpr int S6 = S5 + 1;
}

struct TileData
{
	TileData(int x, int z, int handle, std::string name) :
		x(x),
		z(z),
		handle(handle),
		name(name)
	{}
	~TileData()
	{
		handle = -1;
	}

	int x;
	int z;
	int handle;
	std::string name;
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

	// スイッチ作動
	void SwitchOn(int x, int z);

	// ステージ情報を返す
	std::vector<std::vector<int>> GetStageData() { return m_currentStageData; }

	// スポーンポイントの数を返す
	int GetSpawnPointNum();
	// 指定された順番のスポーンポイントの座標を返す
	VECTOR GetSpawnPoint(int num);

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
	void CreateSwitch(int x, int z);
	void CreateGoal(int x, int z);

	// スイッチの状態を確認
	void CheckSwitch();

	// サプライズメッセージ生成
	void CreateSurpriseMessage();
	// サプライズメッセージ描画
	void DrawSurpriseMessage();

private:
	// キューブの情報
	std::vector<TileData> m_cubes;

	// 現在のステージの情報
	std::vector<std::vector<int>> m_currentStageData;

	// サプライズメッセージ用の画像ハンドル
	std::list<int> m_hSurpriseMsg;

	// サプライズメッセージの描画判定
	bool m_isDrawSurpriseMsg;

	// スイッチ判定
	std::vector<bool> m_isSwitches;

	// ステージのサイズ
	int m_stageWidth;
	int m_stageHeight;
};


#pragma once
#include <vector>
#include <memory>

enum StageType
{
	STAGE_TYPE_NONE = 0,
	STAGE_TYPE_WALL,
	STAGE_TYPE_GOAL,
	STAGE_TYPE_PLAYER,
	STAGE_TYPE_ENEMY,
	STAGE_TYPE_MAX
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

private:

private:
	// キューブの情報
	std::vector<int> m_cubeHandle;

	// 現在のステージの情報
	std::vector<std::vector<int>> m_currentStageData;

	// ステージのサイズ
	int m_stageWidth;
	int m_stageHeight;

};


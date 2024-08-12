#pragma once
#include <vector>
#include <memory>

class Stage
{
public:
	// コンストラクタ
	Stage();
	// デストラクタ
	~Stage();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// ステージライン描画
	void DrawStageLine();

private:
	// ステージモデルのハンドル
	std::vector<int> m_modelHandle;
};


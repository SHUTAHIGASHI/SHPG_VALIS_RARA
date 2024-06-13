#pragma once
#include "ObjectBase.h"

class Player :
	public ObjectBase
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	virtual ~Player();

	// 初期化
	void Init() override;
	// 更新
	void Update(const InputState& input) override;
	// 描画
	void Draw() override;

	// ショット生成
	void CreateShot();

private:
	// 画像ハンドル
	int m_hImg;
};


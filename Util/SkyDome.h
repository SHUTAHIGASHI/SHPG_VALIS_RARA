#pragma once
#include<memory>
#include "Game.h"

class Model;

class SkyDome
{
public:
	// コンストラクタ
	SkyDome();
	// デストラクタ
	~SkyDome();
	// 初期化
	void Init(VECTOR pos);
	// 更新
	void Update();
	// 描画
	void Draw();

	// 各種設定
	void SetPos(VECTOR pos);
	void SetScale(float scale);

private:
	// モデル
	std::shared_ptr<Model> m_pModel;
	// ハンドル
	int m_handle;
	// サイズ
	float m_scale;
	// 回転角度
	float m_rot;
};


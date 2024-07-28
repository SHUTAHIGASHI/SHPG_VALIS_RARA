#include "SceneHowTo.h"
#include "SceneManager.h"

namespace
{
	// 描画テキスト
	const char* const kTextBack = "ボタンを押して戻る";
}

SceneHowTo::SceneHowTo(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_hImg(-1),
	m_pos()
{
	// 画像読み込み
	m_hImg = LoadGraph("Data/ImageData/RARA_GAME_HOWTO.png");
}

SceneHowTo::~SceneHowTo()
{
	// 画像解放
	DeleteGraph(m_hImg);
}

void SceneHowTo::Update(const InputState& input)
{
	// 毎フレームカウント
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
	}

	// どこかのボタンが押されたらタイトルへ
	if (input.IsTriggered(InputType::all))
	{
		m_Manager.PopScene();
	}
}

void SceneHowTo::Draw()
{
	// 背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 画像描画
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.2, 0.0, m_hImg, true);
	float stringLength = static_cast<float>(GetDrawFormatStringWidth(kTextBack));
	// 10フレームごとに点滅
	if ((m_countFrame / 10) % 6 != 0)
	{
		// テキスト描画
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 150, Game::kColorWhite, "%s", kTextBack);
	}
}

#include "SceneResult.h"
#include "SceneManager.h"
#include "SelectMenuBase.h"
#include "Game.h"
#include "SceneMain.h"
#include "SceneTitleMenu.h"
#include "SoundManager.h"
#include "GameDataManager.h"

namespace
{
	// テキスト
	const char* const kTextScene = "リザルト";
	const char* const kScoreTexts[] = {
		"生き残ったラウンド",
		"ラウンド : "
	};
	// 選択項目
	const char* const kMenuTexts[] = {
		"もういちど遊ぶ",
		"タイトルへ"
	};

	// テキスト描画位置
	constexpr float kTextDrawPosX = Game::kScreenWidthHalf - 200.0f;
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf;
	// スコア描画位置
	constexpr float kHighScoreDrawPosX = Game::kScreenWidthHalf + 200.0f;
	constexpr float kHighScoreDrawPosY = Game::kScreenHeightHalf;
	// タイトルテキスト描画位置
	constexpr float kTitleDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTitleDrawPosY = Game::kScreenHeightHalf - 180.0f;
	// スコア描画初期位置
	constexpr float kScorePosY = 1000.0f;
	// スクロール速度
	constexpr float kScrollSpeed = 16.0f;
	// 文字間隔
	constexpr int kTextDistance = static_cast<int>(Game::kFontSize * 1.5);
}

SceneResult::SceneResult(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneResult::StartUpdate),
	m_hBgImg(-1),
	m_scorePosY(-kScorePosY),
	m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// 選択メニュー初期化
	m_pSelectMenu->Init(true);
	// シーン文字列設定
	m_pSelectMenu->SetTitleTextAndPos(kTextScene, kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
	// 描画位置設定
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	// 描画色設定
	m_pSelectMenu->SetSelectedItemColor(Game::kColorGreen);
	// 選択メニューに項目を追加
	for (auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}

	// 背景画像読み込み
	m_hBgImg = LoadGraph("Data/ImageData/RARA_GAME_BG.png");

	// マウス表示
	SetMouseDispFlag(true);
}

SceneResult::~SceneResult()
{
	// 背景画像削除
	m_hBgImg = -1;
}

void SceneResult::Update(const InputState& input)
{
	// Update処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
}

void SceneResult::Draw()
{
	// 背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 背景描画
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf + m_scorePosY, 1.0f, 0.0f, m_hBgImg, true);

	// スコア描画
	int i = 0;
	for (auto& text : kScoreTexts)
	{
		std::string scoreText;
		if (i == 0) scoreText = text;
		else scoreText = text + std::to_string(GameDataManager::GetInstance().GetSurvivedRound());
		// 文字列の長さ取得
		int textLength = GetDrawFormatStringWidth(scoreText.c_str());
		// 描画位置設定
		int drawX = static_cast<int>(kHighScoreDrawPosX - (textLength / 2));
		int drawY = static_cast<int>(kHighScoreDrawPosY + (i * kTextDistance));
		// 描画
		DrawFormatString(drawX, drawY + static_cast<int>(m_scorePosY), Game::kColorGreen, "%s", scoreText.c_str());
		i++;
	}
	// メニュー描画
	m_pSelectMenu->Draw();
}

void SceneResult::StartUpdate(const InputState& input)
{
	// スコア表示位置が0になるまでスクロール
	if (m_scorePosY < 0.0f)
	{
		m_scorePosY += kScrollSpeed;
	}
	else
	{
		m_scorePosY = 0.0f;
		m_updateFunc = &SceneResult::NormalUpdate;
	}

	// 描画位置設定
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	m_pSelectMenu->SetTitleDrawPos(kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
}

void SceneResult::NormalUpdate(const InputState& input)
{
	// 選択メニュー更新
	m_pSelectMenu->Update(input);
	// エンターキーが押されたら
	if (input.IsTriggered(InputType::select))
	{
		// SE再生
		SoundManager::GetInstance().PlaySE(SoundType::select);
		// 選択項目によって処理を分岐
		m_updateFunc = &SceneResult::EndUpdate;
		return;
	}
}

void SceneResult::EndUpdate(const InputState& input)
{
	// スコア表示位置が指定位置になるまでスクロール
	if (m_scorePosY < kScorePosY)
	{
		m_scorePosY += kScrollSpeed;
	}
	else
	{
		m_scorePosY = kScorePosY;
		if (m_pSelectMenu->GetSelectedNum() == 0)
		{
			// 次のステージへ
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else if (m_pSelectMenu->GetSelectedNum() == 1)
		{
			// タイトルへ戻る
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
		return;
	}

	// 描画位置設定
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	m_pSelectMenu->SetTitleDrawPos(kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
}

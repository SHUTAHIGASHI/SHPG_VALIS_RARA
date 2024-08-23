#include "SceneTitleMenu.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneHowTo.h"
#include "Scene2DGame.h"
#include "SceneOption.h"
#include "SelectMenuBase.h"
#include "SkyDome.h"
#include "Load.h"

namespace
{
	// タイトルロゴ描画位置
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 340.0f;
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 150.0f;
	constexpr float kTextDrawSpace = Game::kFontSize;
	// テキスト
	const char* const kMenuTexts[] = 
	{ 
		"ゲームスタート", 
		"あそびかた", 
		"ミニゲーム", 
		"設定", 
		"終了" 
	};

	// 背景キャラのサイズ
	constexpr double kCharaSize = 5.0;
	// キャラクター移動速度
	constexpr float kCharaSpeed = 2.0f;

	// 曲名移動速度
	constexpr float kMusicNameMoveSpeed = 2.0f;
	// 曲名
	const char* const kTextMusicName = "♪.「 月輪迷宮 」- VALIS";
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_hBackGroundImg(-1),
m_hCharaImg(-1),
m_charaPos(VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f)),
m_charaDir(VGet(kCharaSpeed, kCharaSpeed, 0.0f)),
m_musicNameDrawPos(VGet(Game::kScreenWidth, Game::kScreenHeight - 50.0f, 0.0f)),
m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// データ読み込み
	LoadData();
}

SceneTitleMenu::~SceneTitleMenu()
{
	// 画像ハンドル解放
	DeleteGraph(m_hTitleLogoImg);
	// 背景画像解放	
	DeleteGraph(m_hBackGroundImg);
	// キャラ画像解放
	m_hCharaImg = -1;
}

void SceneTitleMenu::Init()
{
	// 選択メニューの初期化
	m_pSelectMenu->Init(true);
	// 選択項目追加
	for (const auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	// 選択項目描画位置設定
	m_pSelectMenu->SetDrawPos(Game::kScreenWidthHalf, kTextDrawPosY);

	// マウスカーソル表示
	SetMouseDispFlag(true);
}

void SceneTitleMenu::Update(const InputState& input)
{
	// 毎フレームカウント
	m_countFrame++;
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
	// キャラクター更新
	UpdateChara();
	// 曲名ループ処理
	MusicNameLoop();
}

void SceneTitleMenu::Draw()
{
	// 背景画像描画
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hBackGroundImg, true);
	// キャラクター描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawRotaGraphF(m_charaPos.x, m_charaPos.y, kCharaSize, 0, m_hCharaImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// タイトルロゴ描画
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 1.0, 0, m_hTitleLogoImg, true);
	// 選択項目描画
	m_pSelectMenu->Draw();
	// 曲名描画
	SetFontSize(32);
	DrawFormatStringF(m_musicNameDrawPos.x, m_musicNameDrawPos.y, Game::kColorWhite, "%s", kTextMusicName);
	SetFontSize(Game::kFontSize);
}

void SceneTitleMenu::End()
{
}

void SceneTitleMenu::LoadData()
{
	// 画像読み込み
	m_hTitleLogoImg = LoadGraph("Data/ImageData/RARA_GAME_TITLE.png");
	// 背景画像読み込み
	m_hBackGroundImg = LoadGraph("Data/ImageData/RARA_GAME_TITLE_BG.png");
	// キャラ画像読み込み
	m_hCharaImg = Load::GetInstance().GetImageHandle("shot");
}

void SceneTitleMenu::OnSceneEnd()
{
	// 選択項目によってシーン遷移
	if (m_pSelectMenu->GetSelectedNum() == 0)
	{
		m_Manager.ChangeScene(new SceneMain(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 1)
	{
		m_Manager.PushScene(new SceneHowTo(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 2)
	{
		m_Manager.ChangeScene(new Scene2DGame(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 3)
	{
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 4)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitleMenu::UpdateChara()
{
	// 画面端判定
	if (m_charaPos.x - (Game::k2DChipSize / 2) < 0.0f || m_charaPos.x + (Game::k2DChipSize / 2) > Game::kScreenWidth)
	{
		m_charaDir.x *= -1;
	}
	if (m_charaPos.y - (Game::k2DChipSize / 2)< 0.0f || m_charaPos.y + (Game::k2DChipSize / 2) > Game::kScreenHeight)
	{
		m_charaDir.y *= -1;
	}
	// キャラクター座標更新
	m_charaPos = VAdd(m_charaPos, m_charaDir);
}

void SceneTitleMenu::MusicNameLoop()
{
	m_musicNameDrawPos.x -= kMusicNameMoveSpeed;

	int textLength = GetDrawFormatStringWidth(kTextMusicName);
	if (m_musicNameDrawPos.x + textLength < 0)
	{
		m_musicNameDrawPos.x = Game::kScreenWidth;
	}
}

void SceneTitleMenu::NormalUpdate(const InputState& input)
{
	// 選択項目描画
	m_pSelectMenu->Update(input);

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}
}

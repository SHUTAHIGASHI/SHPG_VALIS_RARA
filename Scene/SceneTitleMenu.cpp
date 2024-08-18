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
	constexpr float kLogoDrawPosY = 300.0f;
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 200.0f;
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
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_hCharaImg(-1),
m_charaPos(VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f)),
m_charaDir(VGet(kCharaSpeed, kCharaSpeed, 0.0f)),
m_pSelectMenu(std::make_shared<SelectMenuBase>()),
m_pSkyDome(std::make_shared<SkyDome>())
{
	// データ読み込み
	LoadData();
}

SceneTitleMenu::~SceneTitleMenu()
{
	// 画像ハンドル解放
	DeleteGraph(m_hTitleLogoImg);
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

	// スカイドーム初期化
	m_pSkyDome->Init(Game::kVecZero);

	// カメラ初期化
	SetCameraPositionAndAngle(Game::kVecZero, 0.0f,0.0f,0.0f);
}

void SceneTitleMenu::Update(const InputState& input)
{
	// 毎フレームカウント
	m_countFrame++;
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
	// キャラクター更新
	UpdateChara();
}

void SceneTitleMenu::Draw()
{
	// スカイドーム描画
	m_pSkyDome->Draw();
	// キャラクター描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawRotaGraphF(m_charaPos.x, m_charaPos.y, kCharaSize, 0, m_hCharaImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// タイトルロゴ描画
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 1.0, 0, m_hTitleLogoImg, true);
	// 選択項目描画
	m_pSelectMenu->Draw();
}

void SceneTitleMenu::End()
{
}

void SceneTitleMenu::LoadData()
{
	// 画像読み込み
	m_hTitleLogoImg = LoadGraph("Data/ImageData/RARA_GAME_TITLE.png");
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

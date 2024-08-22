#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"
#include "ObjectBase.h"
#include "string"

namespace
{
	// UIを描画する範囲
	constexpr float kDrawRange = 600.0f;
	// 敵HPバーのサイズ
	constexpr float kEnemyHPBarW = 50.0f;
	constexpr float kEnemyHPBarH = 10.0f;

	// 残弾数UIの描画位置
	constexpr int kUiPosX = 100;
	constexpr int kUiPosY = 50;
	// 残弾数UIの拡大率
	constexpr double kUiScale = 3.0;

	// プレイヤーHPバーの描画位置
	constexpr float kPlayerHPBarPosX = Game::kScreenWidthHalf;
	constexpr float kPlayerHPBarPosY = 100.0f;
	// プレイヤーHPバーのサイズ
	constexpr double kPlayerHPBarW = 1000.0f;
	constexpr double kPlayerHPBarH = 60.0f;
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
	// 残弾数UIの読み込み
	m_weaponUiHandle = LoadGraph("Data/ImageData/RARA_GAME_AMMO.png");
	// プレイヤーHPバーの画像読み込み
	m_playerHPBarHandle = LoadGraph("Data/ImageData/RARA_GAME_HPBAR.png");
}

void UiManager::Update()
{
	// UIの更新
	for (auto& ui : m_pEnemyHpBar)
	{
		ui->Update();
	}

	if (m_pPlayerHpBar != nullptr)
	{
		m_pPlayerHpBar->Update();
	}
}

void UiManager::Draw()
{
	// UIの描画
	for (auto& ui : m_pEnemyHpBar)
	{
		// プレイヤーから一定範囲内のUIのみ描画
		if (VSize(VSub(m_playerPos, ui->GetObj()->GetPos())) < kDrawRange)
		{
			ui->Draw();
		}
	}

	if (m_pPlayerHpBar != nullptr)
	{
		m_pPlayerHpBar->Draw();
	}

	// ステージ状態の描画
	DrawRoundState();
	
	// 武器UIの描画
	DrawRotaGraphF(Game::kScreenWidth - (kUiPosX * kUiScale),
		Game::kScreenHeight - (kUiPosY * kUiScale), kUiScale, 0.0, m_weaponUiHandle, true);
}

void UiManager::End()
{
	// UIの削除
	DeleteAllUI();

	// 残弾数UIの削除
	DeleteGraph(m_weaponUiHandle);
}

void UiManager::AddEnemyHpBar(ObjectBase* obj)
{
	// UIの追加
	m_pEnemyHpBar.push_back(new UiBar(obj, false));
	m_pEnemyHpBar.back()->Init();
	// バーのサイズ設定
	m_pEnemyHpBar.back()->SetGaugeSize(kEnemyHPBarW, kEnemyHPBarH);
}

void UiManager::DeleteEnemyHpBar(ObjectBase* obj)
{
	// UIの削除
	for(auto& ui : m_pEnemyHpBar)
	{
		if (ui->GetObj() == obj)
		{
			ui->SetDelete(true);
		}
	}

	// 無効になったオブジェクトは排除
	auto rmIt = std::remove_if(m_pEnemyHpBar.begin(), m_pEnemyHpBar.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// 実際に範囲を指定して削除
	m_pEnemyHpBar.erase(rmIt, m_pEnemyHpBar.end());
}

void UiManager::DeleteAllUI()
{
	// 全UIの削除
	for (auto& ui : m_pEnemyHpBar)
	{
		ui->SetDelete(true);
	}

	// 無効になったオブジェクトは排除
	auto rmIt = std::remove_if(m_pEnemyHpBar.begin(), m_pEnemyHpBar.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// 実際に範囲を指定して削除
	m_pEnemyHpBar.erase(rmIt, m_pEnemyHpBar.end());
}

void UiManager::SetPlayerHPBar(ObjectBase* obj)
{
	// プレイヤーHPバーの設定
	m_pPlayerHpBar = new UiBar(obj, true);
	m_pPlayerHpBar->Init();
	// 描画位置設定
	m_pPlayerHpBar->SetDrawPos(kPlayerHPBarPosX, kPlayerHPBarPosY);
	// バーのサイズ設定
	m_pPlayerHpBar->SetGaugeSize(kPlayerHPBarW, kPlayerHPBarH);
	// 画像ハンドルの設定
	m_pPlayerHpBar->SetGaugeHandle(m_playerHPBarHandle);
}

void UiManager::DrawRoundState()
{
	// ラウンド状態によって描画
	if(m_roundState == RoundState::ROUND_START)
	{
		if (m_roundCount == 0) return;

		// ラウンド開始
		std::string drawText = "ラウンド" + std::to_string(m_roundCount);
		// 文字列サイズ取得
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		// 背景描画
		DrawBox(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2),
			Game::kScreenWidthHalf + (textLength / 2), Game::kScreenHeightHalf + (Game::kFontSize / 2), 0x000000, true);
		// 文字列描画
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2), 0xffffff, "%s", drawText.c_str());
	}
	else if (m_roundState == RoundState::ROUND_ON)
	{
		int drawX = 90;
		int drawY = Game::kScreenHeight - (Game::kFontSize * 3);
		// 文字列描画
		SetFontSize(80);
		std::string drawText = std::to_string(m_roundCount);
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(drawX - (textLength / 2), drawY, 0xffffff, "%d", m_roundCount);
		SetFontSize(20);
		drawText = "ラウンド";
		// 文字列サイズ取得
		textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(drawX - (textLength / 2), drawY - 10, 0xffffff, "%s", drawText.c_str());
		SetFontSize(Game::kFontSize);
	}
	else if (m_roundState == RoundState::ROUND_END)
	{
		// ラウンド終了
		std::string drawText = "ラウンドクリア";
		// 文字列サイズ取得
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		// 背景描画
		DrawBox(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2),
			Game::kScreenWidthHalf + (textLength / 2), Game::kScreenHeightHalf + (Game::kFontSize / 2), 0x000000, true);
		// 文字列描画
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2), 0xffffff, "%s", drawText.c_str());
	}
}

#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"
#include "ObjectBase.h"
#include "string"

namespace
{
	// UIを描画する範囲
	constexpr float kDrawRange = 600.0f;

	// 残弾数UIの描画位置
	constexpr int kUiPosX = 100;
	constexpr int kUiPosY = 50;
	// 残弾数UIの拡大率
	constexpr double kUiScale = 3.0;
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
	// 残弾数UIの読み込み
	m_weaponUiHandle = LoadGraph("Data/ImageData/RARA_GAME_AMMO.png");
}

void UiManager::Update()
{
	// UIの更新
	for (auto& ui : m_pUiBarList)
	{
		ui->Update();
	}

//	if()
}

void UiManager::Draw()
{
	// UIの描画
	for (auto& ui : m_pUiBarList)
	{
		// プレイヤーから一定範囲内のUIのみ描画
		if (VSize(VSub(m_playerPos, ui->GetObj()->GetPos())) < kDrawRange)
		{
			ui->Draw();
		}
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

void UiManager::AddUIBar(ObjectBase* obj)
{
	// UIの追加
	m_pUiBarList.push_back(new UiBar(obj));
	m_pUiBarList.back()->Init();
}

void UiManager::DeleteUIBar(ObjectBase* obj)
{
	// UIの削除
	for(auto& ui : m_pUiBarList)
	{
		if (ui->GetObj() == obj)
		{
			ui->SetDelete(true);
		}
	}

	// 無効になったオブジェクトは排除
	auto rmIt = std::remove_if(m_pUiBarList.begin(), m_pUiBarList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// 実際に範囲を指定して削除
	m_pUiBarList.erase(rmIt, m_pUiBarList.end());
}

void UiManager::DeleteAllUI()
{
	// 全UIの削除
	for (auto& ui : m_pUiBarList)
	{
		ui->SetDelete(true);
	}

	// 無効になったオブジェクトは排除
	auto rmIt = std::remove_if(m_pUiBarList.begin(), m_pUiBarList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// 実際に範囲を指定して削除
	m_pUiBarList.erase(rmIt, m_pUiBarList.end());
}

void UiManager::DrawRoundState()
{
	// ラウンド状態によって描画
	if(m_roundState == RoundState::ROUND_START)
	{
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
		return;
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

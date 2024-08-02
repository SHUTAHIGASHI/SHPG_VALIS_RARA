#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"
#include "ObjectBase.h"
#include "StageManager.h"
#include "string"

namespace
{
	// UIを描画する範囲
	constexpr float kDrawRange = 600.0f;
}

UiManager::~UiManager()
{
}

void UiManager::Update()
{
	// UIの更新
	for (auto& ui : m_pUIList)
	{
		ui->Update();
	}
}

void UiManager::Draw()
{
	// UIの描画
	for (auto& ui : m_pUIList)
	{
		// プレイヤーから一定範囲内のUIのみ描画
		if (VSize(VSub(m_playerPos, ui->GetObj()->GetPos())) < kDrawRange)
		{
			ui->Draw();
		}
	}

	// ステージ状態の描画
	if(m_pStage != nullptr)
	{
		DrawRoundState();
	}
}

void UiManager::AddUI(ObjectBase* obj)
{
	// UIの追加
	m_pUIList.push_back(new UiBar(obj));
	m_pUIList.back()->Init();
}

void UiManager::DeleteUI(ObjectBase* obj)
{
	// UIの削除
	for(auto& ui : m_pUIList)
	{
		if (ui->GetObj() == obj)
		{
			ui->SetDelete(true);
		}
	}

	// 無効になったオブジェクトは排除
	auto rmIt = std::remove_if(m_pUIList.begin(), m_pUIList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// 実際に範囲を指定して削除
	m_pUIList.erase(rmIt, m_pUIList.end());
}

void UiManager::DeleteAllUI()
{
	// 全UIの削除
	for (auto& ui : m_pUIList)
	{
		ui->SetDelete(true);
	}

	// 無効になったオブジェクトは排除
	auto rmIt = std::remove_if(m_pUIList.begin(), m_pUIList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// 実際に範囲を指定して削除
	m_pUIList.erase(rmIt, m_pUIList.end());
}

void UiManager::DrawRoundState()
{
	// ラウンド状態の描画
	auto roundState = m_pStage->GetRoundState();

	if(roundState == RoundState::ROUND_START)
	{
		// ラウンド開始
		std::string drawText = "ラウンド" + std::to_string(m_pStage->GetRoundCount());
		// 文字列サイズ取得
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf, 0xffffff, "%s", drawText.c_str());
	}
	else if (roundState == RoundState::ROUND_ON)
	{
		return;
	}
	else if (roundState == RoundState::ROUND_END)
	{
		// ラウンド終了
		std::string drawText = "ラウンドクリア";
		// 文字列サイズ取得
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf, 0xffffff, "%s", drawText.c_str());
	}
}

#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"

namespace
{

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
		ui->Draw();
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

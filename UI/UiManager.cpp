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
	// UI�̍X�V
	for (auto& ui : m_pUIList)
	{
		ui->Update();
	}
}

void UiManager::Draw()
{
	// UI�̕`��
	for (auto& ui : m_pUIList)
	{
		ui->Draw();
	}
}

void UiManager::AddUI(ObjectBase* obj)
{
	// UI�̒ǉ�
	m_pUIList.push_back(new UiBar(obj));
	m_pUIList.back()->Init();
}

void UiManager::DeleteUI(ObjectBase* obj)
{
	// UI�̍폜
	for(auto& ui : m_pUIList)
	{
		if (ui->GetObj() == obj)
		{
			ui->SetDelete(true);
		}
	}

	// �����ɂȂ����I�u�W�F�N�g�͔r��
	auto rmIt = std::remove_if(m_pUIList.begin(), m_pUIList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// ���ۂɔ͈͂��w�肵�č폜
	m_pUIList.erase(rmIt, m_pUIList.end());
}

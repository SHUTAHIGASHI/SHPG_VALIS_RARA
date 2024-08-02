#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"
#include "ObjectBase.h"
#include "StageManager.h"
#include "string"

namespace
{
	// UI��`�悷��͈�
	constexpr float kDrawRange = 600.0f;
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
		// �v���C���[������͈͓���UI�̂ݕ`��
		if (VSize(VSub(m_playerPos, ui->GetObj()->GetPos())) < kDrawRange)
		{
			ui->Draw();
		}
	}

	// �X�e�[�W��Ԃ̕`��
	if(m_pStage != nullptr)
	{
		DrawRoundState();
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

void UiManager::DeleteAllUI()
{
	// �SUI�̍폜
	for (auto& ui : m_pUIList)
	{
		ui->SetDelete(true);
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

void UiManager::DrawRoundState()
{
	// ���E���h��Ԃ̕`��
	auto roundState = m_pStage->GetRoundState();

	if(roundState == RoundState::ROUND_START)
	{
		// ���E���h�J�n
		std::string drawText = "���E���h" + std::to_string(m_pStage->GetRoundCount());
		// ������T�C�Y�擾
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf, 0xffffff, "%s", drawText.c_str());
	}
	else if (roundState == RoundState::ROUND_ON)
	{
		return;
	}
	else if (roundState == RoundState::ROUND_END)
	{
		// ���E���h�I��
		std::string drawText = "���E���h�N���A";
		// ������T�C�Y�擾
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf, 0xffffff, "%s", drawText.c_str());
	}
}

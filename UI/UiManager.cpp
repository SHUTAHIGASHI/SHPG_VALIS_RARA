#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"
#include "ObjectBase.h"
#include "string"

namespace
{
	// UI��`�悷��͈�
	constexpr float kDrawRange = 600.0f;

	// �c�e��UI�̕`��ʒu
	constexpr int kUiPosX = 100;
	constexpr int kUiPosY = 50;
	// �c�e��UI�̊g�嗦
	constexpr double kUiScale = 3.0;
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
	// �c�e��UI�̓ǂݍ���
	m_weaponUiHandle = LoadGraph("Data/ImageData/RARA_GAME_AMMO.png");
}

void UiManager::Update()
{
	// UI�̍X�V
	for (auto& ui : m_pUiBarList)
	{
		ui->Update();
	}

//	if()
}

void UiManager::Draw()
{
	// UI�̕`��
	for (auto& ui : m_pUiBarList)
	{
		// �v���C���[������͈͓���UI�̂ݕ`��
		if (VSize(VSub(m_playerPos, ui->GetObj()->GetPos())) < kDrawRange)
		{
			ui->Draw();
		}
	}

	// �X�e�[�W��Ԃ̕`��
	DrawRoundState();
	
	// ����UI�̕`��
	DrawRotaGraphF(Game::kScreenWidth - (kUiPosX * kUiScale),
		Game::kScreenHeight - (kUiPosY * kUiScale), kUiScale, 0.0, m_weaponUiHandle, true);
}

void UiManager::End()
{
	// UI�̍폜
	DeleteAllUI();

	// �c�e��UI�̍폜
	DeleteGraph(m_weaponUiHandle);
}

void UiManager::AddUIBar(ObjectBase* obj)
{
	// UI�̒ǉ�
	m_pUiBarList.push_back(new UiBar(obj));
	m_pUiBarList.back()->Init();
}

void UiManager::DeleteUIBar(ObjectBase* obj)
{
	// UI�̍폜
	for(auto& ui : m_pUiBarList)
	{
		if (ui->GetObj() == obj)
		{
			ui->SetDelete(true);
		}
	}

	// �����ɂȂ����I�u�W�F�N�g�͔r��
	auto rmIt = std::remove_if(m_pUiBarList.begin(), m_pUiBarList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// ���ۂɔ͈͂��w�肵�č폜
	m_pUiBarList.erase(rmIt, m_pUiBarList.end());
}

void UiManager::DeleteAllUI()
{
	// �SUI�̍폜
	for (auto& ui : m_pUiBarList)
	{
		ui->SetDelete(true);
	}

	// �����ɂȂ����I�u�W�F�N�g�͔r��
	auto rmIt = std::remove_if(m_pUiBarList.begin(), m_pUiBarList.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// ���ۂɔ͈͂��w�肵�č폜
	m_pUiBarList.erase(rmIt, m_pUiBarList.end());
}

void UiManager::DrawRoundState()
{
	// ���E���h��Ԃɂ���ĕ`��
	if(m_roundState == RoundState::ROUND_START)
	{
		// ���E���h�J�n
		std::string drawText = "���E���h" + std::to_string(m_roundCount);
		// ������T�C�Y�擾
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		// �w�i�`��
		DrawBox(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2),
			Game::kScreenWidthHalf + (textLength / 2), Game::kScreenHeightHalf + (Game::kFontSize / 2), 0x000000, true);
		// ������`��
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2), 0xffffff, "%s", drawText.c_str());
	}
	else if (m_roundState == RoundState::ROUND_ON)
	{
		return;
	}
	else if (m_roundState == RoundState::ROUND_END)
	{
		// ���E���h�I��
		std::string drawText = "���E���h�N���A";
		// ������T�C�Y�擾
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		// �w�i�`��
		DrawBox(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2),
			Game::kScreenWidthHalf + (textLength / 2), Game::kScreenHeightHalf + (Game::kFontSize / 2), 0x000000, true);
		// ������`��
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - (Game::kFontSize / 2), 0xffffff, "%s", drawText.c_str());
	}
}

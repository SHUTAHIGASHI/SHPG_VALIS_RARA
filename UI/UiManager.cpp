#include "UiManager.h"
#include "SceneMain.h"
#include "UiBar.h"
#include "ObjectBase.h"
#include "string"

namespace
{
	// UI��`�悷��͈�
	constexpr float kDrawRange = 600.0f;
	// �GHP�o�[�̃T�C�Y
	constexpr float kEnemyHPBarW = 50.0f;
	constexpr float kEnemyHPBarH = 10.0f;

	// �c�e��UI�̕`��ʒu
	constexpr int kUiPosX = 100;
	constexpr int kUiPosY = 50;
	// �c�e��UI�̊g�嗦
	constexpr double kUiScale = 3.0;

	// �v���C���[HP�o�[�̕`��ʒu
	constexpr float kPlayerHPBarPosX = Game::kScreenWidthHalf;
	constexpr float kPlayerHPBarPosY = 100.0f;
	// �v���C���[HP�o�[�̃T�C�Y
	constexpr double kPlayerHPBarW = 1000.0f;
	constexpr double kPlayerHPBarH = 60.0f;
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
	// �c�e��UI�̓ǂݍ���
	m_weaponUiHandle = LoadGraph("Data/ImageData/RARA_GAME_AMMO.png");
	// �v���C���[HP�o�[�̉摜�ǂݍ���
	m_playerHPBarHandle = LoadGraph("Data/ImageData/RARA_GAME_HPBAR.png");
}

void UiManager::Update()
{
	// UI�̍X�V
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
	// UI�̕`��
	for (auto& ui : m_pEnemyHpBar)
	{
		// �v���C���[������͈͓���UI�̂ݕ`��
		if (VSize(VSub(m_playerPos, ui->GetObj()->GetPos())) < kDrawRange)
		{
			ui->Draw();
		}
	}

	if (m_pPlayerHpBar != nullptr)
	{
		m_pPlayerHpBar->Draw();
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

void UiManager::AddEnemyHpBar(ObjectBase* obj)
{
	// UI�̒ǉ�
	m_pEnemyHpBar.push_back(new UiBar(obj, false));
	m_pEnemyHpBar.back()->Init();
	// �o�[�̃T�C�Y�ݒ�
	m_pEnemyHpBar.back()->SetGaugeSize(kEnemyHPBarW, kEnemyHPBarH);
}

void UiManager::DeleteEnemyHpBar(ObjectBase* obj)
{
	// UI�̍폜
	for(auto& ui : m_pEnemyHpBar)
	{
		if (ui->GetObj() == obj)
		{
			ui->SetDelete(true);
		}
	}

	// �����ɂȂ����I�u�W�F�N�g�͔r��
	auto rmIt = std::remove_if(m_pEnemyHpBar.begin(), m_pEnemyHpBar.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// ���ۂɔ͈͂��w�肵�č폜
	m_pEnemyHpBar.erase(rmIt, m_pEnemyHpBar.end());
}

void UiManager::DeleteAllUI()
{
	// �SUI�̍폜
	for (auto& ui : m_pEnemyHpBar)
	{
		ui->SetDelete(true);
	}

	// �����ɂȂ����I�u�W�F�N�g�͔r��
	auto rmIt = std::remove_if(m_pEnemyHpBar.begin(), m_pEnemyHpBar.end(),
		[](UiBar* ui)
		{
			return ui->IsDelete();
		});
	// ���ۂɔ͈͂��w�肵�č폜
	m_pEnemyHpBar.erase(rmIt, m_pEnemyHpBar.end());
}

void UiManager::SetPlayerHPBar(ObjectBase* obj)
{
	// �v���C���[HP�o�[�̐ݒ�
	m_pPlayerHpBar = new UiBar(obj, true);
	m_pPlayerHpBar->Init();
	// �`��ʒu�ݒ�
	m_pPlayerHpBar->SetDrawPos(kPlayerHPBarPosX, kPlayerHPBarPosY);
	// �o�[�̃T�C�Y�ݒ�
	m_pPlayerHpBar->SetGaugeSize(kPlayerHPBarW, kPlayerHPBarH);
	// �摜�n���h���̐ݒ�
	m_pPlayerHpBar->SetGaugeHandle(m_playerHPBarHandle);
}

void UiManager::DrawRoundState()
{
	// ���E���h��Ԃɂ���ĕ`��
	if(m_roundState == RoundState::ROUND_START)
	{
		if (m_roundCount == 0) return;

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
		int drawX = 90;
		int drawY = Game::kScreenHeight - (Game::kFontSize * 3);
		// ������`��
		SetFontSize(80);
		std::string drawText = std::to_string(m_roundCount);
		int textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(drawX - (textLength / 2), drawY, 0xffffff, "%d", m_roundCount);
		SetFontSize(20);
		drawText = "���E���h";
		// ������T�C�Y�擾
		textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(drawX - (textLength / 2), drawY - 10, 0xffffff, "%s", drawText.c_str());
		SetFontSize(Game::kFontSize);
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

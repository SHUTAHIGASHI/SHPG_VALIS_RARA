#include "SceneClear.h"
#include "SceneManager.h"
#include "SelectMenuBase.h"
#include "Game.h"
#include "SceneMain.h"
#include "SceneTitleMenu.h"
#include "SoundManager.h"

namespace
{
	// �e�L�X�g
	const char* const kTextScene = "�X�e�[�W�N���A�I";
	const char* const kScoreTexts[] = {
		"�X�R�A : ",
		"�����N : "
	};
	// �I������
	const char* const kMenuTexts[] = {
		"���̃X�e�[�W��",
		"�^�C�g����"
	};

	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosX = Game::kScreenWidthHalf - 200.0f;
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf;
	// �X�R�A�`��ʒu
	constexpr float kHighScoreDrawPosX = Game::kScreenWidthHalf + 200.0f;
	constexpr float kHighScoreDrawPosY = Game::kScreenHeightHalf;
	// �^�C�g���e�L�X�g�`��ʒu
	constexpr float kTitleDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTitleDrawPosY = Game::kScreenHeightHalf - 180.0f;
	// �X�R�A�`�揉���ʒu
	constexpr float kScorePosY = 1000.0f;
	// �X�N���[�����x
	constexpr float kScrollSpeed = 12.0f;
	// �����Ԋu
	constexpr int kTextDistance = static_cast<int>(Game::kFontSize * 1.5);
}

SceneClear::SceneClear(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneClear::StartUpdate),
	m_hBgImg(-1),
	m_highScore(0),
	m_rank(""),
	m_scorePosY(-kScorePosY),
	m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// �I�����j���[������
	m_pSelectMenu->Init(false);
	// �V�[��������ݒ�
	m_pSelectMenu->SetTitleTextAndPos(kTextScene, kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
	// �`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	// �I�����j���[�ɍ��ڂ�ǉ�
	for (auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}

	// �w�i�摜�ǂݍ���
	m_hBgImg = LoadGraph("Data/ImageData/OptionBg.png");
}

SceneClear::~SceneClear()
{
	// ���y��~
	SoundManager::GetInstance().StopBGM();
	// �w�i�摜�폜
	DeleteGraph(m_hBgImg);
}

void SceneClear::Update(const InputState& input)
{
	// ���y�Đ��J�n
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic(MusicType::over);
	}

	// Update�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneClear::Draw()
{
	// �w�i�`��
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf + m_scorePosY, 1.0f, 0.0f, m_hBgImg, true);

	// �X�R�A�`��
	int i = 0;
	for (auto& text : kScoreTexts)
	{
		std::string scoreText;
		if (i == 0) scoreText = text + std::to_string(m_highScore);
		else scoreText = text + m_rank;
		// ������̒����擾
		int textLength = GetDrawFormatStringWidth(scoreText.c_str());
		// �`��ʒu�ݒ�
		int drawX = static_cast<int>(kHighScoreDrawPosX - (textLength / 2));
		int drawY = static_cast<int>(kHighScoreDrawPosY + (i * kTextDistance));
		// �`��
		DrawFormatString(drawX, drawY + static_cast<int>(m_scorePosY), Game::kColorWhite, "%s", scoreText.c_str());
		i++;
	}
	// ���j���[�`��
	m_pSelectMenu->Draw();
}

void SceneClear::StartUpdate(const InputState& input)
{
	// �X�R�A�\���ʒu��0�ɂȂ�܂ŃX�N���[��
	if (m_scorePosY < 0.0f)
	{
		m_scorePosY += kScrollSpeed;
	}
	else
	{
		m_scorePosY = 0.0f;
		m_updateFunc = &SceneClear::NormalUpdate;
	}

	// �`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	m_pSelectMenu->SetTitleDrawPos(kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
}

void SceneClear::NormalUpdate(const InputState& input)
{
	// �I�����j���[�X�V
	m_pSelectMenu->Update(input);
	// �G���^�[�L�[�������ꂽ��
	if (input.IsTriggered(InputType::select))
	{
		// SE�Đ�
		SoundManager::GetInstance().PlaySE(SoundType::select);
		// �I�����ڂɂ���ď����𕪊�
		m_updateFunc = &SceneClear::EndUpdate;
		return;
	}
}

void SceneClear::EndUpdate(const InputState& input)
{
	// �X�R�A�\���ʒu���w��ʒu�ɂȂ�܂ŃX�N���[��
	if (m_scorePosY < kScorePosY)
	{
		m_scorePosY += kScrollSpeed;
	}
	else
	{
		m_scorePosY = kScorePosY;
		if (m_pSelectMenu->GetSelectedNum() == 0)
		{
			// ���̃X�e�[�W��
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else if (m_pSelectMenu->GetSelectedNum() == 1)
		{
			// �^�C�g���֖߂�
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
		return;
	}

	// �`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	m_pSelectMenu->SetTitleDrawPos(kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
}

#include "SceneGameOver.h"
#include "SceneManager.h"
#include "SelectMenuBase.h"
#include "Game.h"
#include "SceneMain.h"
#include "SceneTitleMenu.h"
#include "SoundManager.h"

namespace
{
	// �e�L�X�g
	const char* const kTextScene = "�Q�[���I�[�o�[";
	const char* const kTextScore = "�X�R�A : ";
	// �I������
	const char* const kMenuTexts[] = {
		"�R���e�B�j���[",
		"�^�C�g���֖߂�"
	};

	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf;
	// �^�C�g���e�L�X�g�`��ʒu
	constexpr float kTitleDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTitleDrawPosY = Game::kScreenHeightHalf - 180.0f;
	// �X�R�A�`�揉���ʒu
	constexpr float kScorePosY = 1000.0f;
	// �X�N���[�����x
	constexpr float kScrollSpeed = 12.0f;
}

SceneGameOver::SceneGameOver(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneGameOver::StartUpdate),
	m_hBgImg(-1),
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

SceneGameOver::~SceneGameOver()
{
	// ���y��~
	SoundManager::GetInstance().StopBGM();
	// �w�i�摜�폜
	DeleteGraph(m_hBgImg);
}

void SceneGameOver::Update(const InputState& input)
{
	// ���y�Đ��J�n
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic(MusicType::over);
	}

	// Update�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneGameOver::Draw()
{
	// �w�i�`��
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf + m_scorePosY, 1.0f, 0.0f, m_hBgImg, true);

	// ���j���[�`��
	m_pSelectMenu->Draw();
}

void SceneGameOver::StartUpdate(const InputState& input)
{
	if (m_scorePosY < 0.0f)
	{
		m_scorePosY += kScrollSpeed;
	}
	else
	{
		m_scorePosY = 0.0f;
		m_updateFunc = &SceneGameOver::NormalUpdate;
	}

	// �`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(kTextDrawPosX, kTextDrawPosY + m_scorePosY);
	m_pSelectMenu->SetTitleDrawPos(kTitleDrawPosX, kTitleDrawPosY + m_scorePosY);
}

void SceneGameOver::NormalUpdate(const InputState& input)
{
	// �I�����j���[�X�V
	m_pSelectMenu->Update(input);
	// �G���^�[�L�[�������ꂽ��
	if (input.IsTriggered(InputType::select))
	{
		// SE�Đ�
		SoundManager::GetInstance().PlaySE(SoundType::select);
		// �I�����ڂɂ���ď����𕪊�
		m_updateFunc = &SceneGameOver::EndUpdate;
		return;
	}
}

void SceneGameOver::EndUpdate(const InputState& input)
{
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

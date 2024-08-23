#include "SceneTitleMenu.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneHowTo.h"
#include "Scene2DGame.h"
#include "SceneOption.h"
#include "SelectMenuBase.h"
#include "SkyDome.h"
#include "Load.h"

namespace
{
	// �^�C�g�����S�`��ʒu
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 340.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 150.0f;
	constexpr float kTextDrawSpace = Game::kFontSize;
	// �e�L�X�g
	const char* const kMenuTexts[] = 
	{ 
		"�Q�[���X�^�[�g", 
		"�����т���", 
		"�~�j�Q�[��", 
		"�ݒ�", 
		"�I��" 
	};

	// �w�i�L�����̃T�C�Y
	constexpr double kCharaSize = 5.0;
	// �L�����N�^�[�ړ����x
	constexpr float kCharaSpeed = 2.0f;

	// �Ȗ��ړ����x
	constexpr float kMusicNameMoveSpeed = 2.0f;
	// �Ȗ�
	const char* const kTextMusicName = "��.�u ���֖��{ �v- VALIS";
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_hBackGroundImg(-1),
m_hCharaImg(-1),
m_charaPos(VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f)),
m_charaDir(VGet(kCharaSpeed, kCharaSpeed, 0.0f)),
m_musicNameDrawPos(VGet(Game::kScreenWidth, Game::kScreenHeight - 50.0f, 0.0f)),
m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// �f�[�^�ǂݍ���
	LoadData();
}

SceneTitleMenu::~SceneTitleMenu()
{
	// �摜�n���h�����
	DeleteGraph(m_hTitleLogoImg);
	// �w�i�摜���	
	DeleteGraph(m_hBackGroundImg);
	// �L�����摜���
	m_hCharaImg = -1;
}

void SceneTitleMenu::Init()
{
	// �I�����j���[�̏�����
	m_pSelectMenu->Init(true);
	// �I�����ڒǉ�
	for (const auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	// �I�����ڕ`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(Game::kScreenWidthHalf, kTextDrawPosY);

	// �}�E�X�J�[�\���\��
	SetMouseDispFlag(true);
}

void SceneTitleMenu::Update(const InputState& input)
{
	// ���t���[���J�E���g
	m_countFrame++;
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
	// �L�����N�^�[�X�V
	UpdateChara();
	// �Ȗ����[�v����
	MusicNameLoop();
}

void SceneTitleMenu::Draw()
{
	// �w�i�摜�`��
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hBackGroundImg, true);
	// �L�����N�^�[�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawRotaGraphF(m_charaPos.x, m_charaPos.y, kCharaSize, 0, m_hCharaImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �^�C�g�����S�`��
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 1.0, 0, m_hTitleLogoImg, true);
	// �I�����ڕ`��
	m_pSelectMenu->Draw();
	// �Ȗ��`��
	SetFontSize(32);
	DrawFormatStringF(m_musicNameDrawPos.x, m_musicNameDrawPos.y, Game::kColorWhite, "%s", kTextMusicName);
	SetFontSize(Game::kFontSize);
}

void SceneTitleMenu::End()
{
}

void SceneTitleMenu::LoadData()
{
	// �摜�ǂݍ���
	m_hTitleLogoImg = LoadGraph("Data/ImageData/RARA_GAME_TITLE.png");
	// �w�i�摜�ǂݍ���
	m_hBackGroundImg = LoadGraph("Data/ImageData/RARA_GAME_TITLE_BG.png");
	// �L�����摜�ǂݍ���
	m_hCharaImg = Load::GetInstance().GetImageHandle("shot");
}

void SceneTitleMenu::OnSceneEnd()
{
	// �I�����ڂɂ���ăV�[���J��
	if (m_pSelectMenu->GetSelectedNum() == 0)
	{
		m_Manager.ChangeScene(new SceneMain(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 1)
	{
		m_Manager.PushScene(new SceneHowTo(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 2)
	{
		m_Manager.ChangeScene(new Scene2DGame(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 3)
	{
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 4)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitleMenu::UpdateChara()
{
	// ��ʒ[����
	if (m_charaPos.x - (Game::k2DChipSize / 2) < 0.0f || m_charaPos.x + (Game::k2DChipSize / 2) > Game::kScreenWidth)
	{
		m_charaDir.x *= -1;
	}
	if (m_charaPos.y - (Game::k2DChipSize / 2)< 0.0f || m_charaPos.y + (Game::k2DChipSize / 2) > Game::kScreenHeight)
	{
		m_charaDir.y *= -1;
	}
	// �L�����N�^�[���W�X�V
	m_charaPos = VAdd(m_charaPos, m_charaDir);
}

void SceneTitleMenu::MusicNameLoop()
{
	m_musicNameDrawPos.x -= kMusicNameMoveSpeed;

	int textLength = GetDrawFormatStringWidth(kTextMusicName);
	if (m_musicNameDrawPos.x + textLength < 0)
	{
		m_musicNameDrawPos.x = Game::kScreenWidth;
	}
}

void SceneTitleMenu::NormalUpdate(const InputState& input)
{
	// �I�����ڕ`��
	m_pSelectMenu->Update(input);

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}
}

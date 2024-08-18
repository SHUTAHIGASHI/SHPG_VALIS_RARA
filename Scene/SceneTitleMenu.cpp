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
	constexpr float kLogoDrawPosY = 300.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 200.0f;
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
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_hCharaImg(-1),
m_charaPos(VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f)),
m_charaDir(VGet(kCharaSpeed, kCharaSpeed, 0.0f)),
m_pSelectMenu(std::make_shared<SelectMenuBase>()),
m_pSkyDome(std::make_shared<SkyDome>())
{
	// �f�[�^�ǂݍ���
	LoadData();
}

SceneTitleMenu::~SceneTitleMenu()
{
	// �摜�n���h�����
	DeleteGraph(m_hTitleLogoImg);
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

	// �X�J�C�h�[��������
	m_pSkyDome->Init(Game::kVecZero);

	// �J����������
	SetCameraPositionAndAngle(Game::kVecZero, 0.0f,0.0f,0.0f);
}

void SceneTitleMenu::Update(const InputState& input)
{
	// ���t���[���J�E���g
	m_countFrame++;
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
	// �L�����N�^�[�X�V
	UpdateChara();
}

void SceneTitleMenu::Draw()
{
	// �X�J�C�h�[���`��
	m_pSkyDome->Draw();
	// �L�����N�^�[�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawRotaGraphF(m_charaPos.x, m_charaPos.y, kCharaSize, 0, m_hCharaImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �^�C�g�����S�`��
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 1.0, 0, m_hTitleLogoImg, true);
	// �I�����ڕ`��
	m_pSelectMenu->Draw();
}

void SceneTitleMenu::End()
{
}

void SceneTitleMenu::LoadData()
{
	// �摜�ǂݍ���
	m_hTitleLogoImg = LoadGraph("Data/ImageData/RARA_GAME_TITLE.png");
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

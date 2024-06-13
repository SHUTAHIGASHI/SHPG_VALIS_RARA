#include "SceneTitleMenu.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneHowTo.h"
#include "SceneOption.h"
#include "SelectMenuBase.h"
#include "Load.h"

namespace
{
	// ���P�b�g�̃T�C�Y
	constexpr double kRocketSize = 0.1;
	// ���P�b�g�̉�]���x
	constexpr float kRocketRotaSpeed = 0.0175f;
	// ���P�b�g�̒��S����̋���
	constexpr float kRocketCenterDistance = 320.0f;
	// �^�C�g�����S�`��ʒu
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 340.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 200.0f;
	constexpr float kTextDrawSpace = Game::kFontSize;
	// �e�L�X�g
	const char* const kMenuTexts[] = { "�Q�[���X�^�[�g", "�����т���", "�ݒ�", "�I��" };
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_hTitleRocketImg(-1),
m_rocketPos(),
m_rocketDir(),
m_rocketRotation(DX_PI_F),
m_rocketAngle(90.0),
m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// �f�[�^�ǂݍ���
	LoadData();
}

SceneTitleMenu::~SceneTitleMenu()
{
	// BGM��~
	SoundManager::GetInstance().StopBGM();
	// �摜�n���h�����
	DeleteGraph(m_hTitleLogoImg);
	DeleteGraph(m_hTitleRocketImg);
}

void SceneTitleMenu::Init()
{
	// �I�����j���[�̏�����
	m_pSelectMenu->Init(false);
	// �I�����ڒǉ�
	for (const auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	// �I�����ڕ`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(Game::kScreenWidthHalf, kTextDrawPosY);
	// ���P�b�g���W������
	m_rocketPos = VGet(kLogoDrawPosX, kLogoDrawPosY + kRocketCenterDistance, 0.0f);
	m_rocketDir = VGet(0.0f, 0.0f, 0.0f);
}

void SceneTitleMenu::Update(const InputState& input)
{
	// ���y�Đ��J�n
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic(MusicType::title);
	}

	// ���t���[���J�E���g
	m_countFrame++;
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneTitleMenu::Draw()
{
	// ���P�b�g�`��
	DrawRotaGraphF(m_rocketPos.x, m_rocketPos.y, kRocketSize, m_rocketRotation, m_hTitleRocketImg, true);
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
	m_hTitleLogoImg = LoadGraph("Data/ImageData/GAME_TITLE.png");
	m_hTitleRocketImg = LoadGraph("Data/ImageData/TitleRocket.png");
}

void SceneTitleMenu::UpdateRocket()
{
	// ��]���𖈃t���[���ύX
	m_rocketRotation += kRocketRotaSpeed;
	if (m_rocketRotation > DX_PI_F)
	{
		m_rocketRotation = -DX_PI_F;
	}
	// �p�x�̒l�𑝂₷
	m_rocketAngle += 1.0f;

	// �p�x�̍ő�l(  360��)�𒴂����ꍇ�A0�ɂ���
	if (m_rocketAngle >= 360.0f)
	{
		m_rocketAngle = 0.0f;
	}
	// �p�x�����W�A���ɕϊ�
	float rad = m_rocketAngle * (DX_PI_F / 180.0f);

	// ���S�ʒu���甼�a�����ƂɋO�����v�Z
	m_rocketDir.x = cos(rad) * kRocketCenterDistance;
	m_rocketDir.y = sin(rad) * kRocketCenterDistance;

	// ���S�ʒu�̑��
	m_rocketPos = VGet(kLogoDrawPosX, kLogoDrawPosY, 0.0f);

	// �x�N�g�����ʒu�ɉ��Z
	m_rocketPos = VAdd(m_rocketPos, m_rocketDir);
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
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 3)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitleMenu::NormalUpdate(const InputState& input)
{
	// �I�����ڕ`��
	m_pSelectMenu->Update(input);
	// ���o���P�b�g�X�V
	UpdateRocket();

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}
}

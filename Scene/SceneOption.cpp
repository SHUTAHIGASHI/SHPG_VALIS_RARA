#include "SceneOption.h"
#include "SceneManager.h"
#include "SoundManager.h"

namespace
{
	// �^�C�g���e�L�X�g�`��ʒu
	constexpr float kTitleDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTitleDrawPosY = Game::kScreenHeightHalf - 180.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf - 85.0f;
	// �e�L�X�g�`��Ԋu
	constexpr float kTextDistance = 60.0f;
	// �T�E���h�e�L�X�g�̊Ԋu
	constexpr float kSoundTextDistance = 230.0f;
	// ���ʕω���
	constexpr int kVolumeChangeNum = 10;

	// �V�[����
	const char* const kTextScene = "�I�v�V����";
	// �e�L�X�g
	const char* const kMenuTexts[] = {
		"����", 
		"���y", 
		"���ʉ�", 
		"�E�B���h�E���[�h", 
		"�ۑ����ĕ���" 
	};
	// �I���\���ڂ̐�
	constexpr int kMenuTextSize = sizeof(kMenuTexts) / sizeof(char*);
}

SceneOption::SceneOption(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_exVolumeBGM(0),
	m_exVolumeSE(0),
	m_volumeBGM(0),
	m_volumeSE(0),
	m_selectedPos(0),
	m_selectedItemName(),
	m_hBgImg(-1),
	m_hMusicVolImg(-1),
	m_isVolumeChangeMode(false),
	m_isSavedWindowMode(false)
{
	// �摜�ǂݍ���
	m_hBgImg = LoadGraph("Data/ImageData/OptionBg.png");
	m_hMusicVolImg = LoadGraph("Data/ImageData/soundVol.png");
}

SceneOption::~SceneOption()
{
	// �摜�폜
	DeleteGraph(m_hBgImg);
	DeleteGraph(m_hMusicVolImg);
}

void SceneOption::Init()
{
	// ���ʏ����擾
	m_volumeSE = SoundManager::GetInstance().GetSEVolume();
	m_volumeBGM = SoundManager::GetInstance().GetBGMVolume();
	// ���ʏ����Z�b�g
	m_exVolumeBGM = m_volumeBGM;
	m_exVolumeSE = m_volumeSE;
	// ���݂̃E�B���h�E���[�h��ۑ�
	m_isSavedWindowMode = static_cast<bool>(GetWindowModeFlag());
}

void SceneOption::Update(const InputState& input)
{
	// �t���[���J�E���g
	m_countFrame++;
	if (m_countFrame > 60)
	{
		m_countFrame = 0;
	}
	// �|�[�Y�V�[���I��
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PopScene();
		return;
	}
	// ���ʒ���
	if (m_isVolumeChangeMode)
	{
		ChangeVolume(input);
	}
	// ���ʕύX���[�h�łȂ��ꍇ
	else
	{
		// �I�����ڕύX
		if (input.IsTriggered(InputType::down))
		{
			m_selectedPos++;
			if (m_selectedPos > kMenuTextSize - 1) m_selectedPos = 0;
			m_countFrame = 6;
		}
		else if (input.IsTriggered(InputType::up))
		{
			m_selectedPos--;
			if (m_selectedPos < 0) m_selectedPos = kMenuTextSize - 1;
			m_countFrame = 6;
		}
	}
	// ����
	if (input.IsTriggered(InputType::select))
	{
		OnSelect();
	}
	// ���ʕύX���[�h����
	if (input.IsTriggered(InputType::pause))
	{
		// ���ʏ������Z�b�g���ĕ���
		ResetVolumeInfo();
		// �E�B���h�E���[�h���Z�b�g
		if (m_isSavedWindowMode != static_cast<bool>(GetWindowModeFlag())) ChangeWindowMode(m_isSavedWindowMode);
		// �V�[�������
		m_Manager.PopScene();
	}
}

void SceneOption::Draw()
{
	// �w�i�`��
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0, 0.0, m_hBgImg, true);
	// �e�L�X�g�`��
	DrawMenuText();
}

void SceneOption::ChangeVolume(const InputState& input)
{
	// ���ʕύX
	if (m_selectedPos == 1)
	{
		// BGM
		ControllVolume(input, m_volumeBGM);
	}
	else if (m_selectedPos == 2)
	{
		// SE
		ControllVolume(input, m_volumeSE);
	}
}

void SceneOption::ControllVolume(const InputState& input, int& volume)
{
	// ���ʕύX
	if (input.IsTriggered(InputType::right))
	{
		volume += kVolumeChangeNum;
		if (volume > 100) volume = 100;
		// ���ʏ����Z�b�g
		SetVolumeInfo();
	}
	if (input.IsTriggered(InputType::left))
	{
		volume -= kVolumeChangeNum;
		if (volume < 0) volume = 0;
		// ���ʏ����Z�b�g
		SetVolumeInfo();
	}
}

void SceneOption::SetVolumeInfo()
{
	// ���ʏ����Z�b�g
	SoundManager::GetInstance().SetSEVolume(m_volumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_volumeBGM);
}

void SceneOption::ResetVolumeInfo()
{
	// ���ʏ������Z�b�g
	SoundManager::GetInstance().SetSEVolume(m_exVolumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_exVolumeBGM);
}

void SceneOption::DrawSoundBar(float drawX, float drawY, int& volume)
{
	// ���ʃo�[�̐F
	int barColorBGM = 0xffffff, barColorSE = 0xffffff;
	if (m_selectedPos == 1) barColorBGM = Game::kColorOrange;
	if (m_selectedPos == 2) barColorSE = Game::kColorOrange;
	// ���ʃo�[�`��
	for (int i = 0; i < 10; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
		DrawRotaGraphF(drawX + (i * 40), drawY + 20.0f, 0.5, 0.0, m_hMusicVolImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// ���݂̉��ʕ��`��
	int n = 0;
	n = volume / kVolumeChangeNum;
	for (int i = 0; i < n; i++)
	{
		DrawRotaGraphF(drawX + (i * 40), drawY + 20.0f, 0.5, 0.0, m_hMusicVolImg, true);
	}
}

void SceneOption::DrawMenuText()
{
	// �^�C�g���`��
	SetFontSize(static_cast<int>(Game::kFontSize * 1.5));
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(kTitleDrawPosX - (GetDrawFormatStringWidth(kTextScene) / 2));
	drawY = kTitleDrawPosY;
	DrawStringF(drawX, drawY, kTextScene, 0xffffff);
	SetFontSize(Game::kFontSize);
	// ���j���[�e�L�X�g�`��
	for (int i = 0; i < kMenuTextSize; i++)
	{
		if (m_isVolumeChangeMode)
		{
			if (i == m_selectedPos) continue;
		}

		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tSelectedItemName.c_str());
		drawX = static_cast<float>(Game::kScreenWidthHalf - (textLength / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);

		DrawFormatStringF(drawX, drawY, Game::kColorGray, "%s", tSelectedItemName.c_str());
	}
	// �I�𒆂̍��ڕ`��
	m_selectedItemName = "> " + GetCurrentText(m_selectedPos) + " <";
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	// ���ʕύX���[�h
	if (m_isVolumeChangeMode)
	{
		int* volume = 0;
		if (m_selectedPos == 1) volume = &m_volumeBGM;
		else if (m_selectedPos == 2)volume = &m_volumeSE;
		else return;
		// ���ʃo�[�`��
		DrawSoundBar(Game::kScreenWidthHalf - 180.0f, drawY, *volume);
	}
	else
	{ 
		// �I�𒆂̍��ڕ`��
		if ((m_countFrame / 10) % 6 != 0)
		{
			DrawFormatStringF(drawX, drawY - 2, Game::kColorOrange, "%s", m_selectedItemName.c_str());
		}
	}
}

void SceneOption::OnSelect()
{
	// �I�����Đ�
	SoundManager::GetInstance().PlaySE(SoundType::select);
	// �I������
	if (m_selectedPos == 0)
	{
		// ���ʏ������Z�b�g���ĕ���
		ResetVolumeInfo();
		// �E�B���h�E���[�h���Z�b�g
		if (m_isSavedWindowMode != static_cast<bool>(GetWindowModeFlag())) ChangeWindowMode(m_isSavedWindowMode);
		// �V�[�������
		m_Manager.PopScene();
	}
	else if (m_selectedPos == 1 || m_selectedPos == 2)
	{
		// ���ʕύX���[�h
		m_isVolumeChangeMode = !m_isVolumeChangeMode;
	}
	else if (m_selectedPos == 3)
	{
		// �E�B���h�E���[�h�ύX
		auto result = ChangeWindowMode(!static_cast<bool>(GetWindowModeFlag()));
		assert(result == DX_CHANGESCREEN_OK);
	}
	else if (m_selectedPos == 4)
	{
		// ���̂܂ܕ���
		m_Manager.PopScene();
	}
}

std::string SceneOption::GetCurrentText(int textNum)
{
	std::string text;
	// �e�L�X�g�擾
	text = kMenuTexts[textNum];
	return text;
}
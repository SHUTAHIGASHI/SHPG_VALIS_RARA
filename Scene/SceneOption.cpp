#include "SceneOption.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Load.h"

namespace
{
	// �^�C�g���e�L�X�g�`��ʒu
	constexpr float kTitleDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTitleDrawPosY = Game::kScreenHeightHalf - 240.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf - 150.0f;
	// �e�L�X�g�`��Ԋu
	constexpr float kTextDistance = 70.0f;
	// �T�E���h�e�L�X�g�̊Ԋu
	constexpr float kSoundTextDistance = 230.0f;

	// �e�L�X�g�`��F
	constexpr int kTextColor = Game::kColorBlue;

	// ���ʕω���
	constexpr int kVolumeChangeNum = 10;

	// �e�L�X�g
	const char* const kTitleText = "�` �ݒ� �`";
	const char* const kMenuTexts[] = {
		"����",
		"���x",
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
	m_selectedItemName("����"),
	m_hBgImg(-1),
	m_hMusicVolImg(-1),
	m_isCursorRanged(false),
	m_isVolumeChangeMode(false),
	m_isSavedWindowMode(false)
{
	// �摜�ǂݍ���
	m_hBgImg = LoadGraph("Data/ImageData/RARA_GAME_BG.png");
	m_hMusicVolImg = Load::GetInstance().GetHandle("shot");
}

SceneOption::~SceneOption()
{
	// �摜�n���h�����
	DeleteGraph(m_hBgImg);
	m_hMusicVolImg = -1;
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
	if (m_countFrame > 600)
	{
		m_countFrame = 0;
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

	// ���ʕύX���[�h
	if (m_isVolumeChangeMode)
	{
		// ���ʕύX
		ChangeVolume(input);
	}
	else
	{
		// �J�[�\���X�V
		CursorUpdate(input);
	}

	// �I��
	if (input.IsTriggered(InputType::select) && m_isCursorRanged)
	{
		// �I�����̏���
		OnSelect();
	}
}

void SceneOption::Draw()
{
	// �w�i�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �w�i�`��
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.2, 0.0, m_hBgImg, true);
	// �^�C�g���`��
	SetFontSize(60);
	auto titleLength = GetDrawFormatStringWidth(kTitleText);
	DrawFormatStringF(kTitleDrawPosX - (titleLength / 2), kTitleDrawPosY, kTextColor, "%s", kTitleText);
	SetFontSize(Game::kFontSize);
	// ���ڕ`��
	DrawMenuText();
}

void SceneOption::ChangeVolume(const InputState& input)
{
	if (m_selectedItemName == "���y")
	{
		// BGM
		ControllVolume(input, m_volumeBGM);
	}
	else if (m_selectedItemName == "���ʉ�")
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
		// ���ʏ�
		volume += kVolumeChangeNum;
		if (volume > 100) volume = 100;
		SetVolumeInfo();
	}
	if (input.IsTriggered(InputType::left))
	{
		// ���ʉ�
		volume -= kVolumeChangeNum;
		if (volume < 0) volume = 0;
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

void SceneOption::DrawSoundBar(float drawX, float drawY, int volume)
{
	// ���ʃo�[�`��F�ݒ�
	int barColorBGM = 0xffffff, barColorSE = 0xffffff;
	if (m_selectedPos == 1) barColorBGM = Game::kColorBlue;
	if (m_selectedPos == 2) barColorSE = Game::kColorBlue;

	// ���ʃo�[�`��
	for (int i = 0; i < 10; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
		DrawRotaGraphF(drawX + (i * 40), drawY + 20.0f, 1.0, 0.0, m_hMusicVolImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	int n = 0;
	n = volume / kVolumeChangeNum;
	for (int i = 0; i < n; i++)
	{
		// ���ʃo�[�`��
		DrawRotaGraphF(drawX + (i * 40), drawY + 20.0f, 1.0, 0.0, m_hMusicVolImg, true);
	}
}

void SceneOption::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	// ���j���[�e�L�X�g�`��
	for (int i = 0; i < kMenuTextSize; i++)
	{
		if (m_isVolumeChangeMode)
		{
			if (i == m_selectedPos) continue;
		}

		std::string tSelectedItemName = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tSelectedItemName.c_str());
		drawX = static_cast<float>(Game::kScreenWidthHalf - (textLength / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);

		DrawFormatStringF(drawX, drawY, Game::kColorGray, "%s", tSelectedItemName.c_str());
	}
	// �I�𒆂̍��ڕ`��
	std::string drawText = "> " + m_selectedItemName + " <";
	int textLength = GetDrawFormatStringWidth(drawText.c_str());
	drawX = static_cast<float>(Game::kScreenWidthHalf - (textLength / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	// ���ʕύX���[�h
	if (m_isVolumeChangeMode)
	{
		int* volume = 0;
		if (m_selectedItemName == "���y") volume = &m_volumeBGM;
		else if (m_selectedItemName == "���ʉ�")volume = &m_volumeSE;
		else return;
		// ���ʃo�[�`��
		DrawSoundBar(Game::kScreenWidthHalf - 180.0f, drawY, *volume);
	}
	else
	{
		// �I�𒆂̍��ڕ`��
		if ((m_countFrame / 10) % 6 != 0)
		{
			DrawFormatStringF(drawX, drawY - 2, kTextColor, "%s", drawText.c_str());
		}
	}
}

void SceneOption::CursorUpdate(const InputState& input)
{
	m_isCursorRanged = false;
	int buttonPosX = 0, buttonPosY = Game::kScreenHeightHalf;
	std::string tText;
	for (int i = 0; i < kMenuTextSize; i++)
	{
		tText = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tText.c_str());
		buttonPosX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
		buttonPosY = static_cast<int>(kTextDrawPosY + (kTextDistance * i));

		if (input.GetMousePosX() > buttonPosX && input.GetMousePosX() < buttonPosX + textLength
			&& input.GetMousePosY() > buttonPosY && input.GetMousePosY() < buttonPosY + Game::kFontSize)
		{
			// �J�[�\�����g���ɂ���
			m_isCursorRanged = true;
			// �I���ʒu�X�V
			m_selectedPos = i;
			// �I�𒆂̍��ڂ̕�������Z�b�g
			m_selectedItemName = GetCurrentText(m_selectedPos);

			break;
		}
	}
}

void SceneOption::OnSelect()
{
	// �I�����Đ�
	SoundManager::GetInstance().PlaySE(SoundType::select);
	// �I�����ڂɂ�鏈��
	if (m_selectedItemName == "����")
	{
		// ���ʏ������Z�b�g���ĕ���
		ResetVolumeInfo();
		// �E�B���h�E���[�h���Z�b�g
		if (m_isSavedWindowMode != static_cast<bool>(GetWindowModeFlag())) ChangeWindowMode(m_isSavedWindowMode);
		// �V�[�������
		m_Manager.PopScene();
	}
	else if (m_selectedItemName == "���x")
	{
		// ������
	}
	else if (m_selectedItemName == "���y" || m_selectedItemName == "���ʉ�")
	{
		// ���ʕύX���[�h
		m_isVolumeChangeMode = !m_isVolumeChangeMode;
	}
	else if (m_selectedItemName == "�E�B���h�E���[�h")
	{
		// �E�B���h�E���[�h�ύX
		auto result = ChangeWindowMode(!static_cast<bool>(GetWindowModeFlag()));
		assert(result == DX_CHANGESCREEN_OK);
	}
	else if (m_selectedItemName == "�ۑ����ĕ���")
	{
		// ���ʏ���ۑ����ĕ���
		m_Manager.PopScene();
	}
}

std::string SceneOption::GetCurrentText(int textNum)
{
	// �I�𒆂̕������Ԃ�
	return kMenuTexts[textNum];
}
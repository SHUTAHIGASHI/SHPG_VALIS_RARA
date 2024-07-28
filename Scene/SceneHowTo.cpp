#include "SceneHowTo.h"
#include "SceneManager.h"

namespace
{
	// �`��e�L�X�g
	const char* const kTextBack = "�{�^���������Ė߂�";
}

SceneHowTo::SceneHowTo(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_hImg(-1),
	m_pos()
{
	// �摜�ǂݍ���
	m_hImg = LoadGraph("Data/ImageData/RARA_GAME_HOWTO.png");
}

SceneHowTo::~SceneHowTo()
{
	// �摜���
	DeleteGraph(m_hImg);
}

void SceneHowTo::Update(const InputState& input)
{
	// ���t���[���J�E���g
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
	}

	// �ǂ����̃{�^���������ꂽ��^�C�g����
	if (input.IsTriggered(InputType::all))
	{
		m_Manager.PopScene();
	}
}

void SceneHowTo::Draw()
{
	// �w�i�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �摜�`��
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.2, 0.0, m_hImg, true);
	float stringLength = static_cast<float>(GetDrawFormatStringWidth(kTextBack));
	// 10�t���[�����Ƃɓ_��
	if ((m_countFrame / 10) % 6 != 0)
	{
		// �e�L�X�g�`��
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 150, Game::kColorWhite, "%s", kTextBack);
	}
}

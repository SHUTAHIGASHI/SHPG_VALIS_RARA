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
	m_hImg = LoadGraph("Data/ImageData/HowImage.png");
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
	// �摜�`��
	DrawExtendGraphF(0.0f, 0.0f, Game::kScreenWidth, Game::kScreenHeight, m_hImg, true);
	float stringLength = static_cast<float>(GetDrawFormatStringWidth(kTextBack));
	// 10�t���[�����Ƃɓ_��
	if ((m_countFrame / 10) % 6 != 0)
	{
		// �e�L�X�g�`��
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 100, Game::kColorWhite, "%s", kTextBack);
	}
}

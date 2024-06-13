#include "SceneDebug.h"
#include "Game.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneTitleMenu.h"
#include "ScenePauseMenu.h"
#include "SceneGameOver.h"
#include "SceneClear.h"

namespace
{
	// �I���\���ڂ̐�
	constexpr int kSelectItemNum = 4;
	// �e�L�X�g
	const char* const kTextGameMain = "���C��";
	const char* const kTextGameTitleMenu = "�^�C�g��";
	const char* const kTextGamePause = "�|�[�Y";
	const char* const kTextScene = "�Q�[���I�[�o�[";
	const char* const kTextGameEnd = "�N���A";
}

SceneDebug::SceneDebug(SceneManager& manager) :
	Scene(manager),
	m_hImg(-1),
	m_selectedPos(0),
	m_selectedItemName()
{
	m_hImg = LoadGraph("Data/ImageData/PLAYER2_KOLIS.png");
}

SceneDebug::~SceneDebug()
{
	DeleteGraph(m_hImg);
}

void SceneDebug::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::back))
	{
		m_Manager.GameEnd();
		return;
	}

	if (input.IsTriggered(InputType::select))
	{
		if (m_selectedPos == 0)
		{
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else if (m_selectedPos == 1)
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
		else if (m_selectedPos == 2)
		{
			m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		}
		else if (m_selectedPos == 3)
		{
			m_Manager.ChangeScene(new SceneGameOver(m_Manager));
		}
		else
		{
			m_Manager.ChangeScene(new SceneClear(m_Manager));
		}
		return;
	}

	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = kSelectItemNum;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > kSelectItemNum) m_selectedPos = 0;
	}

	UpdateText();
}

void SceneDebug::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraph(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1, 0, m_hImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(100, 100, 0xffffff, "�f�o�b�N�V�[��");
	DrawFormatString(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0xffff00, "%s", m_selectedItemName.c_str());
}

void SceneDebug::UpdateText()
{
	if (m_selectedPos == 0)
	{
		m_selectedItemName = kTextGameMain;
	}
	else if (m_selectedPos == 1)
	{
		m_selectedItemName = kTextGameTitleMenu;
	}
	else if (m_selectedPos == 2)
	{
		m_selectedItemName = kTextGamePause;
	}
	else if (m_selectedPos == 3)
	{
		m_selectedItemName = kTextScene;
	}
	else
	{
		m_selectedItemName = kTextGameEnd;
	}
}

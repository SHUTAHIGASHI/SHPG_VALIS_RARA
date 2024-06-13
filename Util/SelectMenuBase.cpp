#include "SelectMenuBase.h"
#include "SceneManager.h"

namespace
{
	// �����Ԋu
	constexpr int kTextDistance = static_cast<int>(Game::kFontSize * 1.5);
	// �V�[��������g�嗦
	constexpr float kSceneTextScale = 1.5f;
}

SelectMenuBase::SelectMenuBase() :
	m_updateFunc(&SelectMenuBase::NormalUpdate),
	m_selectedPos(0),
	m_selectItems(),
	m_sceneText(nullptr),
	m_mouseState(),
	m_isCursorRanged(false),
	m_drawPos(Game::kVecZero),
	m_titleDrawPos(Game::kVecZero),
	m_itemColor(Game::kColorGray),
	m_selectedItemColor(Game::kColorWhite),
	m_countFrame(0)
{
}

SelectMenuBase::~SelectMenuBase()
{
}

void SelectMenuBase::Init(bool isMouse)
{
	if (isMouse) m_updateFunc = &SelectMenuBase::CursorUpdate;
}

void SelectMenuBase::Update(const InputState& input)
{
	// �t���[���J�E���g
	m_countFrame++;
	if (m_countFrame > 60) m_countFrame = 0;
	// �}�E�X�J�[�\�����W�擾
	m_mouseState.x = input.GetMousePosX();
	m_mouseState.y = input.GetMousePosY();
	// �X�V
	(this->*m_updateFunc)(input);
}

void SelectMenuBase::Draw()
{
	// �V�[��������`��
	DrawSceneText();
	// ���j���[������`��
	DrawMenuText();
}

void SelectMenuBase::AddSelectItem(std::string itemName)
{
	m_selectItems.push_back(SelectItemState());
	m_selectItems.back().itemName = itemName;
}

void SelectMenuBase::DrawMenuText()
{
	int drawX = 0, drawY = 0;

	int itemCount = 0;
	for (auto& items : m_selectItems)
	{
		int textLength = GetDrawFormatStringWidth(items.itemName.c_str());
		drawX = static_cast<int>(m_drawPos.x - (textLength / 2));
		drawY = static_cast<int>(m_drawPos.y + (kTextDistance * itemCount));
		DrawFormatString(drawX, drawY, m_itemColor, "%s", items.itemName.c_str());

		itemCount++;
	}

	std::string drawText = "> " + m_selectItems[m_selectedPos].itemName + " <";
	int textLength = GetDrawFormatStringWidth(drawText.c_str());
	drawX = static_cast<int>(m_drawPos.x - (textLength / 2));
	drawY = static_cast<int>(m_drawPos.y + (kTextDistance * m_selectedPos));

	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawFormatString(drawX, drawY - 2, m_selectedItemColor, "%s", drawText.c_str());
	}
}

void SelectMenuBase::DrawSceneText()
{
	// �V�[��������`��
	if (m_sceneText != nullptr)
	{
		// �t�H���g�T�C�Y�g��
		SetFontSize(static_cast<int>(Game::kFontSize * kSceneTextScale));
		int textLength = GetDrawFormatStringWidth(m_sceneText->c_str());
		int drawX = static_cast<int>(m_titleDrawPos.x - (textLength / 2));
		int drawY = static_cast<int>(m_titleDrawPos.y);
		// �����`��
		DrawFormatString(drawX, drawY, Game::kColorWhite, "%s", m_sceneText->c_str());
		// �t�H���g�T�C�Y�߂�
		SetFontSize(Game::kFontSize);
	}
}

void SelectMenuBase::CursorUpdate(const InputState& input)
{
	m_isCursorRanged = false;

	int buttonPosX = 0, buttonPosY = 0;
	int itemCount = 0;
	for (auto& items : m_selectItems)
	{
		int textLength = GetDrawFormatStringWidth(items.itemName.c_str());
		buttonPosX = static_cast<int>(m_drawPos.x - (textLength / 2));
		buttonPosY = static_cast<int>(m_drawPos.y + (kTextDistance * itemCount));

		if (m_mouseState.x > buttonPosX && m_mouseState.x < buttonPosX + textLength
			&& m_mouseState.y > buttonPosY && m_mouseState.y < buttonPosY + Game::kFontSize)
		{
			m_isCursorRanged = true;
			m_selectedPos = itemCount;
			m_countFrame = 6;
		}
		itemCount++;
	}
}

void SelectMenuBase::NormalUpdate(const InputState& input)
{
	int selectItemMax = static_cast<int>(m_selectItems.size() - 1);
	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = selectItemMax;
		m_countFrame = 6;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > selectItemMax) m_selectedPos = 0;
		m_countFrame = 6;
	}
}

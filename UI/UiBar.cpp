#include "UiBar.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// �Q�[�W�̍��W
	constexpr int kGaugeW = 50;
	constexpr int kGaugeH = 10;
	constexpr int kDrawPosDiff = 30;
}

UiBar::UiBar(class ObjectBase* obj) :
	m_isDelete(false),
	m_drawX(0),
	m_drawY(0),
	m_num(0),
	m_maxNum(0),
	m_currentNumRate(0.0f),
	m_maxNumRate(0.0f),
	m_color(0),
	m_targetObj(obj)
{
}

UiBar::~UiBar()
{
}

void UiBar::Init()
{
	// ���l�̏�����
	m_num = m_targetObj->GetHpPointer();
	m_maxNum = *m_num;
	// �o�[�̐F
	m_color = Game::kColorOrange;
	// �`����W
	m_drawX = 0;
	m_drawY = 0;
	// HP���̌v�Z
	m_maxNumRate = (static_cast<float>(m_maxNum) / m_maxNum) * kGaugeW;
}

void UiBar::Update()
{
	// HP���̌v�Z
	m_currentNumRate = (static_cast<float>(*m_num) / m_maxNum) * kGaugeW;

	if (m_currentNumRate < 30)
	{
		m_color = Game::kColorRed;
	}
	else
	{
		m_color = Game::kColorGreen;
	}

	// �`��ʒu�ݒ�
	VECTOR screenPos = ConvWorldPosToScreenPos(m_targetObj->GetPos());
	SetDrawPos(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y));
}

void UiBar::Draw()
{
	// HP�o�[�̕`��
	int drawX = m_drawX - static_cast<int>(m_maxNumRate / 2);
	int drawY = m_drawY - kDrawPosDiff;
	int drawW = drawX + static_cast<int>(m_currentNumRate);
	int drawH = drawY + kGaugeH;
	DrawBox(drawX, drawY, drawW, drawH, m_color, true);
	// �g�̕`��
	drawW = drawX + static_cast<int>(m_maxNumRate);
	DrawBox(drawX, drawY, drawW, drawH, 0xffffff, false);
}

void UiBar::SetDrawPos(int x, int y)
{
	m_drawX = x;
	m_drawY = y;
}

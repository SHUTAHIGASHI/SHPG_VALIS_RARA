#include "Player.h"
#include "Game.h"

Player::Player():
	ObjectBase(),
	m_hImg(-1)
{
	// ‰æ‘œ“Ç‚İ‚İ
	m_hImg = LoadGraph("Data/ImageData/Manju_Chino.png");
}

Player::~Player()
{
	// ‰æ‘œíœ
	DeleteGraph(m_hImg);
}

void Player::Init()
{

}

void Player::Update(const InputState& input)
{
}

void Player::Draw()
{
	// ‰æ‘œ•`‰æ
	m_status.pos.z += 1000.0f;
	DrawBillboard3D(m_status.pos, 1.0f, 1.0f, m_status.scale, 0.0f, m_hImg, TRUE);
}

void Player::CreateShot()
{
}

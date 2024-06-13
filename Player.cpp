#include "Player.h"
#include "Game.h"

Player::Player():
	ObjectBase(),
	m_hImg(-1)
{
	// �摜�ǂݍ���
	m_hImg = LoadGraph("Data/ImageData/Manju_Chino.png");
}

Player::~Player()
{
	// �摜�폜
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
	// �摜�`��
	m_status.pos.z += 1000.0f;
	DrawBillboard3D(m_status.pos, 1.0f, 1.0f, m_status.scale, 0.0f, m_hImg, TRUE);
}

void Player::CreateShot()
{
}

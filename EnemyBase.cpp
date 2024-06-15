#include "EnemyBase.h"
#include "Load.h"
#include "Game.h"

namespace
{

}

EnemyBase::EnemyBase(VECTOR pos)
{
	// 拡大率設定
	m_status.scale = Game::kBaseScale;
	// 座標設定
	m_status.pos = pos;
	// 画像設定
	m_status.hImg = Load::GetInstance().GetHandle("enemy");
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
	// 3D描画
	//DrawSphere3D(m_status.pos, 10.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	// 画像描画
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void EnemyBase::OnHit()
{
	// 当たった時の処理
	m_status.isEnabled = false;
}

#include "SkyDome.h"
#include "Model.h"
#include "Load.h"

namespace
{
	// スカイドームの半径
	constexpr float kSkyDomeRadius = 10.0f;
	// スカイドームの回転速度
	constexpr float kSkyDomeRotSpeed = 0.0002f;
}

SkyDome::SkyDome() :
	m_pModel(nullptr),
	m_scale(kSkyDomeRadius),
	m_rot(0.0f)
{
	// モデルの読み込み
	m_handle = MV1DuplicateModel(Load::GetInstance().GetModelHandle("skydome"));
	// モデルクラス初期化
	m_pModel = std::make_shared<Model>(m_handle);
	// スカイドームのスケールを設定
	m_pModel->SetScale(m_scale);
	// 座標初期化
	m_pModel->SetPosition(Game::kVecZero);
}

SkyDome::~SkyDome()
{
}

void SkyDome::Init(VECTOR pos)
{
	// モデル情報更新
	m_pModel->SetPosition(pos);
}

void SkyDome::Update()
{
	// スカイドーム回転
	m_pModel->SetRotation(VGet(0.0f, m_rot, 0.0f));
	m_rot += kSkyDomeRotSpeed;
	if (m_rot >= DX_PI_F) m_rot = -DX_PI_F;
}

void SkyDome::Draw()
{
	m_pModel->Draw();
}

void SkyDome::SetPos(VECTOR pos)
{
	m_pModel->SetPosition(pos);
}

void SkyDome::SetScale(float scale)
{
	m_pModel->SetScale(m_scale * scale);
}

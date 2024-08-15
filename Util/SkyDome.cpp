#include "SkyDome.h"
#include "Model.h"
#include "Load.h"

namespace
{
	// �X�J�C�h�[���̔��a
	constexpr float kSkyDomeRadius = 10.0f;
	// �X�J�C�h�[���̉�]���x
	constexpr float kSkyDomeRotSpeed = 0.0002f;
}

SkyDome::SkyDome() :
	m_pModel(nullptr),
	m_scale(kSkyDomeRadius),
	m_rot(0.0f)
{
	// ���f���̓ǂݍ���
	m_handle = MV1DuplicateModel(Load::GetInstance().GetModelHandle("skydome"));
	// ���f���N���X������
	m_pModel = std::make_shared<Model>(m_handle);
	// �X�J�C�h�[���̃X�P�[����ݒ�
	m_pModel->SetScale(m_scale);
	// ���W������
	m_pModel->SetPosition(Game::kVecZero);
}

SkyDome::~SkyDome()
{
}

void SkyDome::Init(VECTOR pos)
{
	// ���f�����X�V
	m_pModel->SetPosition(pos);
}

void SkyDome::Update()
{
	// �X�J�C�h�[����]
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

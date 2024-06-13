#include "SkyDome.h"
#include "Model.h"
#include "Load.h"

namespace
{
	// �X�J�C�h�[���̔��a
	constexpr float kSkyDomeRadius = 10.0f;
	// �X�J�C�h�[���̉�]���x
	constexpr float kSkyDomeRotSpeed = 0.0003f;
	// 0 �̃x�N�g��
	constexpr VECTOR kZero = { 0.0f, 0.0f, 0.0f };
}

SkyDome::SkyDome() :
	m_pModel(nullptr),
	m_scale(kSkyDomeRadius),
	m_angle(0.0f),
	m_dir(Game::kVecZero)
{
	// ���f���N���X������
	m_pModel = std::make_shared<Model>(MV1DuplicateModel(Load::GetInstance().GetHandle("skydome")));
	// �X�J�C�h�[���̃X�P�[����ݒ�
	m_pModel->SetScale(m_scale);
}

SkyDome::~SkyDome()
{
}

void SkyDome::Init(VECTOR playerPos)
{
	m_dir = playerPos;
	//X��
	m_dir.x += 1.0f * cosf(m_angle);
	//Z��
	m_dir.z += 1.0f * sinf(m_angle);
	// ���f�����X�V
	m_pModel->SetPosition(playerPos);
	m_pModel->SetDirectionAxisZ(m_dir, 0.0f);
}

void SkyDome::Update(VECTOR playerPos)
{
	m_dir = playerPos;
	//X��
	m_dir.x += 1.0f * cosf(m_angle);
	//Z��
	m_dir.z += 1.0f * sinf(m_angle);
	// ���f�����X�V
	m_pModel->SetPosition(playerPos);
	m_pModel->SetDirectionAxisZ(m_dir, 0.0f);
}

void SkyDome::Draw()
{
	m_pModel->Draw();
}

void SkyDome::SetScale(float scale)
{
	m_pModel->SetScale(m_scale * scale);
}

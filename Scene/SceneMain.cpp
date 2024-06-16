#include "SceneMain.h"
// �V�[���֌W
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "ScenePauseMenu.h"
#include "SceneGameOver.h"
#include "SceneClear.h"
#include "SceneHowTo.h"
#include "SceneFade.h"
// �Q�[���֌W
#include "Game.h"
#include "Player.h"
#include "EnemyManager.h"
// �S��
#include "CameraManager.h"
#include "EffekseerManager.h"
#include "SoundManager.h"
#include "SkyDome.h"

SceneMain::SceneMain(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneMain::StartUpdate),
	m_pCamera(std::make_shared<CameraManager>()),
	m_pPlayer(std::make_shared<Player>()),
	m_pEnemyManager(std::make_shared<EnemyManager>()),
	m_pSkyDome(std::make_shared<SkyDome>())
{
}

SceneMain::~SceneMain()
{
	// �Đ����̉��y���~
	SoundManager::GetInstance().StopBGM();
}

void SceneMain::Init()
{
	// �J����������
	m_pCamera->SetPlayer(m_pPlayer.get());
	m_pCamera->Init();
	// �v���C���[������
	m_pPlayer->SetEnemyManager(m_pEnemyManager.get());
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->Init();
	// �G�Ǘ�������
	m_pEnemyManager->Init();
	// �X�J�C�h�[���̏���������
	m_pSkyDome->Init(m_pPlayer->GetPos());
}

void SceneMain::Update(const InputState& input)
{
	// Update�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);

	// �J�����X�V
	m_pCamera->Update();
	// �v���C���[�X�V
	m_pPlayer->Update(input);
	// �G�Ǘ��X�V
	m_pEnemyManager->Update();
	// �X�J�C�h�[���̍X�V����
	m_pSkyDome->Update(m_pPlayer->GetPos());

	// �G�t�F�N�g�̍X�V����
	EffekseerManager::GetInstance().Update();
}

void SceneMain::Draw()
{
	// �G�Ǘ��`��
	m_pEnemyManager->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();
	//�X�J�C�h�[���`��
	//m_pSkyDome->Draw();

	// �G�t�F�N�g�`��
	EffekseerManager::GetInstance().Draw();

	// �X�e�[�W���C���`��
	DrawStageLine();
}

void SceneMain::End()
{
	// �Đ����̃G�t�F�N�g��~
	EffekseerManager::GetInstance().StopAllEffect();
}

void SceneMain::DrawStageLine()
{
	// �O���b�h��\��
	for (float z = -Game::kStageSizeZ; z <= Game::kStageSizeZ; z += 100.0f)
	{
		VECTOR start = VGet(-Game::kStageSizeX, -100.0f, z);
		VECTOR end = VGet(Game::kStageSizeX, -100.0f, z);
		DrawLine3D(start, end, 0x00ff00);
	}

	for (float x = -Game::kStageSizeX; x <= Game::kStageSizeX; x += 100.0f)
	{
		VECTOR start = VGet(x, -100.0f, -Game::kStageSizeZ);
		VECTOR end = VGet(x, -100.0f, Game::kStageSizeZ);
		DrawLine3D(start, end, 0xff0000);
	}
}

void SceneMain::NormalUpdate(const InputState& input)
{
	// �|�[�Y���j���[�ֈڍs
	if (input.IsTriggered(InputType::pause))
	{
		// BGM��~
		SoundManager::GetInstance().StopBGM();
		// �|�[�Y���j���[�V�[���ֈڍs
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}

	// ���y�Đ��J�n
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic(MusicType::main);
	}
}

void SceneMain::StartUpdate(const InputState& input)
{
}

void SceneMain::EndUpdate(const InputState& input)
{
}

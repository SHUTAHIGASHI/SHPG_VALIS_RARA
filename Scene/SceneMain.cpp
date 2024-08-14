#include "SceneMain.h"
// �V�[���֌W
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "ScenePauseMenu.h"
#include "SceneGameOver.h"
#include "SceneResult.h"
#include "SceneHowTo.h"
#include "SceneFade.h"
// �Q�[���֌W
#include "Game.h"
#include "Player.h"
#include "StageManager.h"
#include "EnemyManager.h"
// �S��
#include "CameraManager.h"
#include "SoundManager.h"
#include "UiManager.h"
#include "SkyDome.h"

SceneMain::SceneMain(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_pCamera(std::make_shared<CameraManager>()),
	m_pPlayer(std::make_shared<Player>()),
	m_pStage(std::make_shared<StageManager>()),
	m_pSkyDome(std::make_shared<SkyDome>())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// �}�E�X��\��
	SetMouseDispFlag(false);
	// �v���C���[������
	m_pPlayer->SetCamera(m_pCamera.get());
	m_pPlayer->Init();
	// �G�Ǘ�������
	m_pStage->SetPlayer(m_pPlayer.get());
	m_pStage->Init();
	// �X�J�C�h�[���̏���������
	m_pSkyDome->Init(m_pPlayer->GetPos());
	// �J����������
	m_pCamera->Init();
	// �J�[�\�����W�Œ�
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
}

void SceneMain::Update(const InputState& input)
{
	// Update�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);

	// UI�X�V
	UiManager::GetInstance().Update();
}

void SceneMain::Draw()
{
	//�X�J�C�h�[���`��
	m_pSkyDome->Draw();

	// �G�Ǘ��`��
	m_pStage->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();

	// UI�`��
	UiManager::GetInstance().Draw();
}

void SceneMain::End()
{
	// �}�E�X�\��
	SetMouseDispFlag(true);
	// �SUI�̍폜
	UiManager::GetInstance().DeleteAllUI();
}

void SceneMain::OnGameOver()
{
	// ���s����X�V�����ύX
	m_updateFunc = &SceneMain::EndUpdate;

	// �V�[���ύX
	m_Manager.PushSceneAllUpdate(new SceneResult(m_Manager));
}

void SceneMain::NormalUpdate(const InputState& input)
{
	// �|�[�Y���j���[�ֈڍs
	if (input.IsTriggered(InputType::pause))
	{
		// �|�[�Y���j���[�V�[���ֈڍs
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}

	// �J�[�\�����W�Œ�
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// �J�����X�V
	m_pCamera->Update();
	// �v���C���[�X�V
	m_pPlayer->Update(input);
	// �G�Ǘ��X�V
	m_pStage->Update();
	// �X�J�C�h�[���̍X�V
	m_pSkyDome->Update();
	m_pSkyDome->SetPos(m_pPlayer->GetPos());

	// �Q�[���I�[�o�[
	if (m_pPlayer->IsDead())
	{
		// �Q�[���I�[�o�[���������s
		OnGameOver();
		return;
	}
}

void SceneMain::StartUpdate(const InputState& input)
{
	// �|�[�Y���j���[�ֈڍs
	if (input.IsTriggered(InputType::pause))
	{
		// �|�[�Y���j���[�V�[���ֈڍs
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}
}

void SceneMain::EndUpdate(const InputState& input)
{
	// �J�����X�V
	m_pCamera->Update();
	// �v���C���[�X�V
	m_pPlayer->UpdateGameover();
	// �G�Ǘ��X�V
	m_pStage->Update();
	// �X�J�C�h�[���̍X�V
	m_pSkyDome->Update();
	m_pSkyDome->SetPos(m_pPlayer->GetPos());
}

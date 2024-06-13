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
// �S��
#include "CameraController.h"
#include "EffekseerManager.h"
#include "SoundManager.h"

SceneMain::SceneMain(SceneManager& manager) :
	Scene(manager),
	m_updateFunc(&SceneMain::StartUpdate),
	m_drawFunc(&SceneMain::StartDraw),
	m_pCamera(std::make_shared<CameraController>()),
	m_pPlayer(std::make_shared<Player>())
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
	m_pCamera->Init();
	// �v���C���[������
	m_pPlayer = std::make_shared<Player>();
}

void SceneMain::Update(const InputState& input)
{
	// Update�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);

	// �G�t�F�N�g�̍X�V����
	EffekseerManager::GetInstance().Update();
}

void SceneMain::Draw()
{
	// Draw�����̃����o�֐��|�C���^
	//(this->*m_drawFunc)();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �G�t�F�N�g�`��
	EffekseerManager::GetInstance().Draw();

	// �O���b�h��\��
	for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
	{
		VECTOR start = VGet(-1000.0f, 0.0f, z);
		VECTOR end = VGet(1000.0f, 0.0f, z);
		DrawLine3D(start, end, 0x00ff00);
	}

	for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
	{
		VECTOR start = VGet(x, 0.0f, -1000.0f);
		VECTOR end = VGet(x, 0.0f, 1000.0f);
		DrawLine3D(start, end, 0xff0000);
	}
}

void SceneMain::End()
{
	// �Đ����̃G�t�F�N�g��~
	EffekseerManager::GetInstance().StopAllEffect();
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

void SceneMain::NormalDraw()
{
}

void SceneMain::StartDraw()
{
	// �����Ȃ�
}

void SceneMain::EndDraw()
{
	// �����Ȃ�
}

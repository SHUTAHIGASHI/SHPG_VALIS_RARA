#include "SceneManager.h"
#include "Scene.h"
#include "SceneFade.h"
#include "SoundManager.h"

namespace
{
	//�����p�����o�[�̕����̍��W
	constexpr int kUpdateBarStringPosX = 0;
	constexpr int kUpdateBarStringPosY = Game::kScreenHeight - 188;
	constexpr int kDrawBarPosStringPosX = 0;
	constexpr int kDrawBarPosStringPosY = Game::kScreenHeight - 172;

	//�����p�����o�[�̍��W
	constexpr int kExplainUpdateBarPosX1 = 34;
	constexpr int kExplainUpdateBarPosY1 = Game::kScreenHeight - 186;
	constexpr int kExplainUpdateBarPosX2 = 62;
	constexpr int kExplainUpdateBarPosY2 = Game::kScreenHeight - 174;
	constexpr int kExplainDrawBarPosX1 = 34;
	constexpr int kExplainDrawBarPosY1 = Game::kScreenHeight - 170;
	constexpr int kExplainDrawBarPosX2 = 62;
	constexpr int kExplainDrawBarPosY2 = Game::kScreenHeight - 158;


	//�����o�[�̐F
	constexpr int kUpdateBarColor = 0x0000ff;
	constexpr int kDrawBarColor = 0xff0000;

	//�����o�[�̍��W
	constexpr int kBarPosX = 0;
	constexpr int kBarPosY = Game::kScreenHeight - 100;
}

void SceneManager::ChangeScene(Scene* scene)
{
	m_isAllUpdate = false;
	m_updateFunc = &SceneManager::FadeCloseUpdate;
	m_NextScene = scene;
	m_Fade = new SceneFade(*this);
}

void SceneManager::PushSceneAllUpdate(Scene* scene)
{
	m_Scene.push_front(scene);			//1������
	m_Scene.front()->Init();
	m_isAllUpdate = true;
}

void SceneManager::PushScene(Scene* scene)
{
	m_Scene.push_front(scene);			//1������
	m_Scene.front()->Init();
	m_isAllUpdate = false;
}

void SceneManager::PopScene()
{
	m_isAllUpdate = false;
	//�|�b�v�̌��ʁA�V�[����0�ɂȂ�Ȃ��悤�ɂ���
	if (m_Scene.size() > 1)
	{
		delete m_Scene.front();
		m_Scene.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	//�X�V�O�̃��[�f�B���O���Ԏ擾
	LONGLONG start = GetNowHiPerformanceCount();

	(this->*m_updateFunc)(input);

	//�X�V��̃��[�f�B���O���Ԃ���X�V�O�̃��[�f�B���O���Ԃ��������l���擾
	m_updateTime = static_cast<float>(GetNowHiPerformanceCount() - start);
}

void SceneManager::Draw()
{
	//�`��O�̃��[�f�B���O���Ԏ擾
	LONGLONG start = GetNowHiPerformanceCount();

	for (int i = static_cast<int>(m_Scene.size() - 1); i >= 0; --i)
	{
		m_Scene[i]->Draw();
	}

	if (m_Fade != nullptr)
	{
		m_Fade->Draw();
	}

	//�f�o�b�O���͍X�V�A�`�掞�̏������x�𑪂�
#ifdef _DEBUG
	m_drawTime = static_cast<float>(GetNowHiPerformanceCount() - start);

	//�����o�[�̕\���@
	//����
	DrawString(kUpdateBarStringPosX, kUpdateBarStringPosY, "����", 0xffffff, 0x000000);
	DrawBox(kExplainUpdateBarPosX1, kExplainUpdateBarPosY1, kExplainUpdateBarPosX2, kExplainUpdateBarPosY2, kUpdateBarColor, true);
	DrawString(kDrawBarPosStringPosX, kDrawBarPosStringPosY, "�`��", 0xffffff, 0x000000);
	DrawBox(kExplainDrawBarPosX1, kExplainDrawBarPosY1, kExplainDrawBarPosX2, kExplainDrawBarPosY2, kDrawBarColor, true);

	float rate = static_cast<float>(m_updateTime + m_drawTime) / 16666.6f;
	float width = static_cast<float>(Game::kScreenWidth * rate);
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kDrawBarColor, true);

	rate = static_cast<float>(m_updateTime) / 16666.6f;
	width = static_cast<float>(Game::kScreenWidth * rate);
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kUpdateBarColor, true);
#endif
}

void SceneManager::GameEnd()
{
	ClearAllScene();

	m_isAllUpdate = false;
	m_isEnd = true;
}

void SceneManager::ClearAllScene()
{
	//�V�[���X�^�b�N����ł͂Ȃ�������...
	if (!m_Scene.empty())
	{
		// ���ݎ��s���̃V�[�������ׂč폜
		for (auto& scenes : m_Scene)
		{
			scenes->End();
			delete scenes;
		}
		m_Scene.clear();
	}
}

// �V�[���̒ʏ�X�V����
void SceneManager::SceneNormalUpdate(const InputState& input)
{
	if (m_isAllUpdate)
	{
		// �S�Ă̍X�V���������s
		for (auto scene : m_Scene)
		{
			scene->Update(input);
		}
	}
	else 
	{
		// �V�[���z��̐擪�����X�V
		m_Scene.front()->Update(input);
	}
}

// �V�[���ύX���̍X�V����
void SceneManager::FadeOpenUpdate(const InputState& input)
{
	// �t�F�[�h�V�[���̍X�V
	m_Fade->Update(input);

	if (m_Fade->IsFadeOpen())
	{
		m_updateFunc = &SceneManager::SceneNormalUpdate;
		delete m_Fade;
		m_Fade = nullptr;
	}	
}

void SceneManager::FadeCloseUpdate(const InputState& input)
{
	// �t�F�[�h�V�[���̍X�V
	m_Fade->Update(input);

	if (m_Fade->IsFadeClose())
	{
		// �t�F�[�h�������J���ق��ɕύX
		m_updateFunc = &SceneManager::FadeOpenUpdate;
		// �����V�[�����폜
		ClearAllScene();
		// �V�����V�[���쐬
		m_Scene.push_front(m_NextScene);
		// �V�K�V�[���̏���������
		m_Scene.front()->Init();
		// ���̃V�[���Ƃ��ĕۑ����Ă������g���폜
		m_NextScene = nullptr;
	}
}

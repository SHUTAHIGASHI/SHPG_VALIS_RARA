#include "SceneManager.h"
#include "Scene.h"
#include "SceneFade.h"
#include "SoundManager.h"

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
	(this->*m_updateFunc)(input);
}

void SceneManager::Draw()
{
	for (int i = static_cast<int>(m_Scene.size() - 1); i >= 0; --i)
	{
		m_Scene[i]->Draw();
	}

	if (m_Fade != nullptr)
	{
		m_Fade->Draw();
	}
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

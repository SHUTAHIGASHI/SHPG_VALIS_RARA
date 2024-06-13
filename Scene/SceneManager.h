#pragma once
#include <deque>

//�v���g�^�C�v�錾
class Scene;
class SceneFade;
class InputState;

//�V�[���Ď��N���X
class SceneManager
{
public:

	/// <summary>
	/// �V�[���̐؂�ւ����s��
	/// </summary>
	/// <param name="scene">�؂�ւ��������V�[���̃A�h���X</param>
	void ChangeScene(Scene* scene);

	/// <summary>
	/// �V�[������ɐς�
	/// Update�ł͑S�ẴV�[�����X�V�����
	/// </summary>
	/// <param name="scene"></param>
	void PushSceneAllUpdate(Scene* scene);
	/// <summary>
	/// �V�[������ɐς�
	/// Update�Ŏ��s�����̂͏�ɂ܂ꂽ�V�[���̂�
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(Scene* scene);
	/// <summary>
	/// ��ԏ�̃V�[�����폜����
	/// �������A���̌��ʃX�^�b�N����ɂȂ邱�Ƃ̂Ȃ��悤��
	/// </summary>
	void PopScene();
	/// <summary>
	/// �e�V�[����Update���s��
	/// </summary>
	/// <param name="input">���̓X�e�[�g</param>
	void Update(const InputState& input);
	/// <summary>
	/// �e�V�[���̕`����s��
	/// </summary>
	void Draw();
	/// <summary>
	/// �V�[�������ׂč폜���A���ׂĂ̏������I��������
	/// </summary>
	void GameEnd();
	/// <summary>
	/// �Q�[���̏I�����邩�ǂ�����Ԃ�
	/// </summary>
	bool IsGameEnd() { return m_isEnd; }

private:
	// �V�[����S�ăN���A����
	void ClearAllScene();

	//�����o�֐��|�C���^
	using m_tUpdateFunc = void (SceneManager::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	// �ʏ�̍X�V����
	void SceneNormalUpdate(const InputState& input);
	// �t�F�[�h����
	void FadeCloseUpdate(const InputState& input);
	void FadeOpenUpdate(const InputState& input);

private:
	//�����s���̃V�[����؂�ւ��Ă��������̂�	
	//�Q�Ƃł͂Ȃ��|�C���^�Ƃ��Đ錾
	std::deque<Scene*> m_Scene;
	// ���Ɏ��s����V�[�����ꎞ�I�ɕۑ�����
	Scene* m_NextScene;
	// �t�F�[�h�����̃V�[���錾
	SceneFade* m_Fade;

	// �������I�����邩
	bool m_isEnd = false;

	// �X�V������S�čs�����ǂ���
	bool m_isAllUpdate = false;
};


#pragma once
#include "Scene.h"
#include <string>
#include <memory>
#include "Game.h"

class SceneTitleMenu :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneTitleMenu(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneTitleMenu();
    // ������
    void Init();
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();
    // �I��
    void End();

private: // �v���C�x�[�g�֐�
    // �f�[�^�ǂݍ���
    void LoadData();
    // �^�C�g���I��������
    void OnSceneEnd();
    // �L�����N�^�[�X�V
    void UpdateChara();
    // �Ȗ����[�v����
    void MusicNameLoop();

    using m_tUpdateFunc = void (SceneTitleMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // �^�C�g����ʍX�V����
    void NormalUpdate(const InputState& input);

private: // �V�[���S�̂̊Ǘ��ϐ�
    // ���t���[���J�E���g�p
    int m_countFrame;

private: // �V�[�������̊Ǘ��ϐ�
    // �摜�n���h��
    int m_hTitleLogoImg;
    // �w�i�摜�n���h��
	int m_hBackGroundImg;
    // �L�����n���h��
    int m_hCharaImg;
    // �L�����N�^�[���W
    VECTOR m_charaPos;
    VECTOR m_charaDir;
    // �Ȗ��\���ʒu
    VECTOR m_musicNameDrawPos;

private:
    // �Z���N�g���j���[�̊Ǘ��ϐ�
    std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
};


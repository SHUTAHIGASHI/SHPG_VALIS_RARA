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
    // ���P�b�g�̈ړ�����
    void UpdateRocket();
    // �^�C�g���I��������
    void OnSceneEnd();

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
    int m_hTitleRocketImg;

private: // ���P�b�g���������̕ϐ��B
    // �^�C�g����ʂ̃��P�b�g�ʒu
    VECTOR m_rocketPos;
    VECTOR m_rocketDir;
    double m_rocketRotation;
    float m_rocketAngle;

private:
    // �Z���N�g���j���[�̊Ǘ��ϐ�
    std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
};


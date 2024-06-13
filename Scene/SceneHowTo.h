#pragma once
#include "Scene.h"
#include "Game.h"

class SceneHowTo :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneHowTo(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneHowTo();
    // ������
    void Init() override {}
    // �X�V
    void Update(const InputState& input) override;
    // �`��
    void Draw();
    // �I��
    void End() {}

private:
    // ���t���[���J�E���g
    int m_countFrame;
    // �摜�n���h��
    int m_hImg;
    // �`����W
    VECTOR m_pos;
};


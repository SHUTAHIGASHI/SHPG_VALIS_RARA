#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <string>

class SceneDebug :
    public Scene
{
public:
    SceneDebug(SceneManager& manager);
    virtual ~SceneDebug();

    // �V�[��������
    void Init() {}
    // �X�V����
    void Update(const InputState& input);
    // �`�揈��
    void Draw();
    // �I��
    void End() {}

private:
    void UpdateText();

private:
    // �摜�n���h��
    int m_hImg;
    // �I�𒆂̍���
    int m_selectedPos;
    // �I�𒆂̍��ږ�
    std::string m_selectedItemName;
};


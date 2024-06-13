#pragma once
#include "Scene.h"
#include <memory>
#include <string>

class SceneGameOver :
    public Scene
{
public:
    SceneGameOver(SceneManager& manager);
    virtual ~SceneGameOver();

    // ������
    void Init() {}
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();
    // �I��
    void End() {}

private:
    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneGameOver::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void StartUpdate(const InputState& input);      // �J�n���̍X�V����
    void NormalUpdate(const InputState& input);     // �ʏ�̍X�V����
    void EndUpdate(const InputState& input);        // �I�����̍X�V����

private: // �ϐ�
    int m_hBgImg;
    // �X�R�A�`��p���W
    float m_scorePosY;
    // �I�����j���[
    std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
};


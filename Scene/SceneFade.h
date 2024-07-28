#pragma once
#include "Scene.h"
#include "Game.h"
#include <vector>

class SceneFade :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneFade(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneFade();

    // ������
    void Init() {}
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();
    // �I��
    void End() {}

    // �t�F�[�h�����̔����Ԃ� //
    bool IsFadeClose() { return m_isFadeClose; } // ���؂������ǂ���
    bool IsFadeOpen() { return m_isFadeOpen; }  // �J���؂������ǂ���

private:
    //�����o�֐��|�C���^
    using m_tUpdateFunc = void (SceneFade::*) ();
    m_tUpdateFunc m_updateFunc = nullptr;
    void CloseUpdate();  // �V�[���J�n���̕`�揈��
    void OpenUpdate();    // �V�[���I�����̕`�揈��

private:
    // �t�F�[�h�����������������ǂ���
    bool m_isFadeClose;
    bool m_isFadeOpen;
    // �t�F�[�h�摜
    int m_hFadeImg;
    // �O���t�T�C�Y
    int m_graphSizeX;
    int m_graphSizeY;
    // �g�嗦
    double m_imgScale;
};


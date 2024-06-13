#pragma once
#include "Scene.h"
#include "Game.h"
#include <string>

enum class volume
{
    SE,
    BGM
};

class SceneOption :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneOption(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneOption();

    // ������
    void Init();
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();
    // �I��
    void End() {}

private: // �v���C�x�[�g�֐�
    // ���ʂ̐ݒ�
    void ChangeVolume(const InputState& input);
    // ���ʂ̑���
    void ControllVolume(const InputState& input, int& volume);
    // �ύX�������ʏ��𔽉f������
    void SetVolumeInfo();
    // �ύX�O�̉��ʏ��𔽉f������
    void ResetVolumeInfo();
    // �e�L�X�g�`��ʒu
    void DrawSoundBar(float drawX, float drawY, int& volume);
    // �e�L�X�g���̕`��
    void DrawMenuText();
    // �I�����̏���
    void OnSelect();

    // �I�𒆂̕������Ԃ�
    std::string GetCurrentText(int textNum);
private:
    // ���t���[���J�E���g
    int m_countFrame;
    // �O�̉���
    int m_exVolumeBGM;
    int m_exVolumeSE;
    // ����
    int m_volumeBGM;
    int m_volumeSE;
    // �I���ʒu
    int m_selectedPos;
    // �I�𒆂̕�����
    std::string m_selectedItemName;
    // �摜
	int m_hBgImg;
    int m_hMusicVolImg;
    // ���ʒ������[�h
    bool m_isVolumeChangeMode;
    // �E�B���h�E���[�h�ύX�������ǂ���
    bool m_isSavedWindowMode;
};

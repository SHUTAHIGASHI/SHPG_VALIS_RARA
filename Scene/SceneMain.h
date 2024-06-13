#pragma once
#include "Scene.h"
#include <memory>

class SceneMain :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneMain(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneMain();

    // �V�[��������
    void Init();
    // �X�V����
    void Update(const InputState& input);
    // �`�揈��
    void Draw();
    // �I��
    void End();

private:

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);     // �ʏ�̍X�V����
    void StartUpdate(const InputState& input);      // �Q�[���X�^�[�g���̍X�V����
    void EndUpdate(const InputState& input);        // �Q�[���I�[�o�[���̍X�V����

    // �����o�֐��|�C���^(�`��)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void NormalDraw();      // �ʏ�̕`�揈��
    void StartDraw();       // �V�[���J�n���̕`�揈��
    void EndDraw();         // �V�[���I�����̕`�揈��

private:
    std::shared_ptr<class CameraController> m_pCamera;     // �J����
	std::shared_ptr<class Player> m_pPlayer;               // �v���C���[
};


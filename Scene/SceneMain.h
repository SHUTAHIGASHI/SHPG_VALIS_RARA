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
    void Init()override;
    // �X�V����
    void Update(const InputState& input)override;
    // �`�揈��
    void Draw()override;
    // �I��
    void End()override;

private:
    // �Q�[���I�[�o�[����
    void OnGameOver();

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);     // �ʏ�̍X�V����
    void StartUpdate(const InputState& input);      // �Q�[���X�^�[�g���̍X�V����
    void EndUpdate(const InputState& input);        // �Q�[���I�[�o�[���̍X�V����

private:
    std::shared_ptr<class CameraManager> m_pCamera; // �J����
	std::shared_ptr<class Player> m_pPlayer;        // �v���C���[ 
	std::shared_ptr<class StageManager> m_pStage;   // �G�Ǘ�
	std::shared_ptr<class SkyDome> m_pSkyDome;      // �X�J�C�h�[��
};


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
	// �X�e�[�W���C���`��
	void DrawStageLine();

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);     // �ʏ�̍X�V����
    void StartUpdate(const InputState& input);      // �Q�[���X�^�[�g���̍X�V����
    void EndUpdate(const InputState& input);        // �Q�[���I�[�o�[���̍X�V����

private:
    std::shared_ptr<class CameraManager> m_pCamera;         // �J����
	std::shared_ptr<class Player> m_pPlayer;               // �v���C���[ 
	std::shared_ptr<class EnemyManager> m_pEnemyManager;   // �G�Ǘ�
	std::shared_ptr<class SkyDome> m_pSkyDome;             // �X�J�C�h�[��
};


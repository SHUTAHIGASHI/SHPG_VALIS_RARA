#pragma once
#include "ObjectBase.h"
#include <list>

class Player :
	public ObjectBase
{
public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	virtual ~Player();

	// �G�l�~�[�}�l�[�W���[�̐ݒ�
	void SetEnemyManager(class EnemyManager* pEnemyManager) { m_pEnemyManager = pEnemyManager; }
	// �J�����̐ݒ�
	void SetCamera(class CameraManager* pCamera) { m_pCamera = pCamera; }

	// ������
	void Init() override;
	// �X�V
	void Update(const InputState& input) override;
	// �`��
	void Draw() override;

private:
	// �V���b�g�Ǘ�
	void ControllShot(const InputState& input);
	// �V���b�g����
	void CreateShot();
	// �X�y�V�����V���b�g����
	void CreateSprShot();
	// �V���b�g�X�V
	void UpdateShot();
	// �J�[�\���X�V
	void UpdateCursor(const InputState& input);
	// 2D�`��
	void Draw2D();

private:
	// �摜�n���h��
	int m_hLockCursorImg;
	// �V���b�g�A�ˑ��x
	int m_shotDelay;
	// �J�[�\�����b�N����
	bool m_isLockOn;
	// �J�[�\�����W
	VECTOR m_cursorPos;
	// ���b�N�I���J�[�\�����W
	VECTOR m_lockObjPos;
	// �V���b�g�z��
	std::list<class Shot*> m_pShots;
	

private:// �e��|�C���^
	// �V���b�g�^�[�Q�b�g�|�C���^
	ObjectBase* m_pTargetObj;
	// �G�l�~�[�}�l�[�W���[�̃|�C���^
	class EnemyManager* m_pEnemyManager;
	// �J�����̃|�C���^
	class CameraManager* m_pCamera;
};


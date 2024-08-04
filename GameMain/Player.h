#pragma once
#include "ObjectBase.h"
#include <list>

enum class PostureType
{
	stand,
	crouch,
	slide
};

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
	// �Q�[���I�[�o�[���̍X�V
	void UpdateGameover();
	// �`��
	void Draw() override;

	// ��_���[�W����
	void OnDamage(int damage);

private:
	// ���_�̑���
	void ControllView(const InputState& input);
	// ���_�̍X�V
	void UpdateView();

	// �ړ�����
	void ControllMove(const InputState& input);
	// �p���̍X�V
	void UpdatePosture(const InputState& input);
	// �X���C�f�B���O�̍X�V
	void UpdateSlide();
	// �X���C�f�B���O����
	void OnSlide();

	// �V���b�g�Ǘ�
	void ControllShot(const InputState& input);
	// �V���b�g����
	void CreateShot();
	// �X�y�V�����V���b�g����
	void CreateSprShot();
	// �V���b�g�X�V
	void UpdateShot();
	// �V���b�g�q�b�g����
	void OnHitShot(class Shot* pShot);

	// �J�[�\���X�V
	void UpdateCursor(const InputState& input);

	// 2D�`��
	void Draw2D();

private:
	// �v���C���[�̎p��
	PostureType m_posture;

	// �摜�n���h��
	int m_hFpsHand;
	int m_hCursorImg;
	int m_hLockCursorImg;
	int m_hHitCursorImg;
	// �摜�T�C�Y
	int m_HandSizeX;
	int m_HandSizeY;
	// ���t���[���J�E���g
	int m_frameCount;
	// ��̕`��p�t���[��
	int m_handFrame;
	// �V���b�g�A�ˑ��x
	int m_shotDelay;
	// �X���C�f�B���O����
	int m_slideTime;
	// ���G����
	int m_invTime;
	// �q�b�g�}�[�N�`��t���[��
	int m_hitMarkFrame;

	// �ړ�����
	bool m_isMove;
	// �J�[�\�����b�N����
	bool m_isLockOn;
	// �ˌ�������
	bool m_isShot;

	// �����̍���
	float m_eyeHeight;

	// �����_�̈ړ���
	float m_playerAngleY;
	float m_playerAngleX;

	// �X���C�f�B���O�x�N�g��
	VECTOR m_slideVec;
	// ���b�N�I���J�[�\�����W
	VECTOR m_lockObjPos;
	// ���e�n�_
	VECTOR m_targetPos;

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


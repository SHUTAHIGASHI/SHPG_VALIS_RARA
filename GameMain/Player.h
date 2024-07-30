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

	// �X���C�f�B���O����
	void OnSlide();

private:
	// �v���C���[�̎p��
	PostureType m_posture;

	// �摜�n���h��
	int m_hFpsHand;
	int m_hCursorImg;
	int m_hLockCursorImg;
	// �摜�T�C�Y
	int m_HandSizeX;
	int m_HandSizeY;
	// �V���b�g�A�ˑ��x
	int m_shotDelay;
	// �X���C�f�B���O����
	int m_slideTime;
	// ���G����
	int m_invTime;

	// �ړ�����
	bool m_isMove;
	// �_�b�V������
	bool m_isDash;
	// �J�[�\�����b�N����
	bool m_isLockOn;

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


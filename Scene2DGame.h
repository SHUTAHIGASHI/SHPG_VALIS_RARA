#pragma once
#include "Scene.h"
#include "Game.h"
#include <list>

struct Shot
{
	// �V���b�g�摜
	int shotHandle = -1;
	// �V���b�g���W
	VECTOR shotPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR shotDir = VGet(0.0f, 0.0f, 0.0f);
	// �V���b�g���x
	float shotSpeed = 32.0f;
};

struct Enemy
{
	// �G�l�~�[�摜
	int enemyHandle = -1;
	// �G�l�~�[���W
	VECTOR enemyPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR enemyDir = VGet(0.0f, 1.0f, 0.0f);
	// �G�l�~�[���x
	float enemySpeed = 12.0f;
	// �폜����
	bool isDelete = false;
};

class Scene2DGame :
    public Scene
{
public:
    // �R���X�g���N�^
    Scene2DGame(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~Scene2DGame();

	// ������
	void Init() override;
	// �X�V
	void Update(const InputState& input) override;
	// �`��
	void Draw() override;
	// �I��
	void End() override;

private: // �v���C���[�֐�
	// �v���C���[�X�V
	void UpdatePlayer(const InputState& input);
	// �v���C���[�`��
	void DrawPlayer();

private: // �V���b�g�֐�
	// �V���b�g�X�V
	void UpdateShot();
	// �V���b�g�`��
	void DrawShot();

private: // �G�l�~�[�֐�
	// �G�l�~�[�X�V
	void UpdateEnemy();
	// �G�l�~�[�`��
	void DrawEnemy();

private: // �v���C���[�ϐ�
	// �v���C���[�摜
	int m_hPlayerImg;
	// �v���C���[���W
	VECTOR m_playerPos;

private: // �V���b�g�ϐ�
	// �V���b�g�\���̔z��
	std::list<Shot> m_shots;
	// �V���b�g�摜
	int m_hShotImg;
	// �V���b�g�x��
	int m_shotDelay;

private: // �G�l�~�[�ϐ�
	// �G�l�~�[�\���̔z��
	std::list<Enemy> m_enemies;
	// �G�l�~�[�摜
	int m_hEnemyImg;
	// �����J�E���g
	int m_enemyCount;

private: // ���̑��ϐ�
	// �w�i�摜
	int m_hBackImg;
	// �J�[�\���摜
	int m_hCursorImg;
	// �J�[�\�����W
	VECTOR m_cursorPos;
};


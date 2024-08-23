#pragma once
#include <DxLib.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

namespace StageTile
{
	constexpr int EN = 0;
	constexpr int CH = 1;
	constexpr int MY = CH + 1;
	constexpr int NE = MY + 1;
	constexpr int NI = NE + 1;
	constexpr int RA = NI + 1;
	constexpr int VI = RA + 1;
	constexpr int FL = VI + 1;
	constexpr int WL = FL + 1;
	constexpr int F1 = WL + 1;
	constexpr int F2 = F1 + 1;
	constexpr int GL = F2 + 1;
	constexpr int SP = GL + 1;
	constexpr int S1 = SP + 1;
	constexpr int S2 = S1 + 1;
	constexpr int S3 = S2 + 1;
	constexpr int S4 = S3 + 1;
	constexpr int S5 = S4 + 1;
	constexpr int S6 = S5 + 1;
}

struct TileData
{
	TileData(int x, int z, int handle, std::string name) :
		x(x),
		z(z),
		handle(handle),
		name(name)
	{}
	~TileData()
	{
		handle = -1;
	}

	int x;
	int z;
	int handle;
	std::string name;
};

class Stage
{
public:
	// �R���X�g���N�^
	Stage();
	// �f�X�g���N�^
	virtual ~Stage();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// �X�C�b�`�쓮
	void SwitchOn(int x, int z);

	// �X�e�[�W����Ԃ�
	std::vector<std::vector<int>> GetStageData() { return m_currentStageData; }

	// �X�|�[���|�C���g�̐���Ԃ�
	int GetSpawnPointNum();
	// �w�肳�ꂽ���Ԃ̃X�|�[���|�C���g�̍��W��Ԃ�
	VECTOR GetSpawnPoint(int num);

	// �w�肵�����W�̃X�e�[�W����Ԃ�
	void GetTile(VECTOR pos, int &x, int &z);

	// �w�肵���^�C���̏�Ԃ�Ԃ�
	int GetTileHandle(int x, int z);

private:
	// �X�e�[�W�̐���
	void CreateStage();

	// �X�e�[�W���f���̐���
	void CreateObject(int x, int z, int handle);
	void CreateFloar(int x, int z);
	void CreateWall(int x, int z);
	void CreateFence(int x, int z, bool);
	void CreateSwitch(int x, int z);
	void CreateGoal(int x, int z);

	// �X�C�b�`�̏�Ԃ��m�F
	void CheckSwitch();

	// �T�v���C�Y���b�Z�[�W����
	void CreateSurpriseMessage();
	// �T�v���C�Y���b�Z�[�W�`��
	void DrawSurpriseMessage();

private:
	// �L���[�u�̏��
	std::vector<TileData> m_cubes;

	// ���݂̃X�e�[�W�̏��
	std::vector<std::vector<int>> m_currentStageData;

	// �T�v���C�Y���b�Z�[�W�p�̉摜�n���h��
	std::list<int> m_hSurpriseMsg;

	// �T�v���C�Y���b�Z�[�W�̕`�攻��
	bool m_isDrawSurpriseMsg;

	// �X�C�b�`����
	std::vector<bool> m_isSwitches;

	// �X�e�[�W�̃T�C�Y
	int m_stageWidth;
	int m_stageHeight;
};


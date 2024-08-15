#pragma once
#include <vector>
#include <memory>
#include <DxLib.h>

namespace StageTile
{
	constexpr int EN = 0;
	constexpr int FL = 1;
	constexpr int WL = 2;
	constexpr int F1 = 3;
	constexpr int F2 = 4;
	constexpr int GL = 5;
	constexpr int CH = 6;
	constexpr int MY = CH + 1;
	constexpr int NE = MY + 1;
	constexpr int NI = NE + 1;
	constexpr int RA = NI + 1;
	constexpr int VI = RA + 1;
}

struct TileData
{
	TileData(int x, int z, int handle) :
		x(x),
		z(z),
		handle(handle)
	{}
	~TileData()
	{
		handle = -1;
	}

	int x;
	int z;
	int handle;
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

	// �X�e�[�W����Ԃ�
	std::vector<std::vector<int>> GetStageData() { return m_currentStageData; }

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
	void CreateGoal(int x, int z);

private:
	// �L���[�u�̏��
	std::vector<TileData> m_cubes;

	// ���݂̃X�e�[�W�̏��
	std::vector<std::vector<int>> m_currentStageData;

	// �X�e�[�W�̃T�C�Y
	int m_stageWidth;
	int m_stageHeight;

};


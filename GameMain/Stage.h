#pragma once
#include <vector>
#include <memory>
#include <DxLib.h>

enum StageType
{
	STAGE_TYPE_NONE = 0,
	STAGE_TYPE_WALL,
	STAGE_TYPE_GOAL,
	STAGE_TYPE_PLAYER,
	STAGE_TYPE_ENEMY,
	STAGE_TYPE_MAX
};

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

private:
	// �L���[�u�̏��
	std::vector<TileData> m_cubes;

	// ���݂̃X�e�[�W�̏��
	std::vector<std::vector<int>> m_currentStageData;

	// �X�e�[�W�̃T�C�Y
	int m_stageWidth;
	int m_stageHeight;

};


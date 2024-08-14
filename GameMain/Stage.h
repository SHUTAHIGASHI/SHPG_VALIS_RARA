#pragma once
#include <vector>
#include <memory>

enum StageType
{
	STAGE_TYPE_NONE = 0,
	STAGE_TYPE_WALL,
	STAGE_TYPE_GOAL,
	STAGE_TYPE_PLAYER,
	STAGE_TYPE_ENEMY,
	STAGE_TYPE_MAX
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
private:

private:
	// �L���[�u�̏��
	std::vector<int> m_cubeHandle;

	// ���݂̃X�e�[�W�̏��
	std::vector<std::vector<int>> m_currentStageData;

	// �X�e�[�W�̃T�C�Y
	int m_stageWidth;
	int m_stageHeight;

};


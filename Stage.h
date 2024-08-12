#pragma once
#include <vector>
#include <memory>

class Stage
{
public:
	// �R���X�g���N�^
	Stage();
	// �f�X�g���N�^
	~Stage();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

private:
	// �X�e�[�W���C���`��
	void DrawStageLine();

private:
	// �X�e�[�W���f���̃n���h��
	std::vector<int> m_modelHandle;
};


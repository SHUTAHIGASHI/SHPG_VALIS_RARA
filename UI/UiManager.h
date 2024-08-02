#pragma once
#include "Game.h"
#include <list>

class UiManager
{
public:
	~UiManager();
	/// <summary>
	/// UiManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static UiManager& GetInstance()
	{
		// �B��̎���
		static UiManager instance;

		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}
private:
	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	UiManager()
	{
	}
	// �R�s�[��������֎~����
	UiManager(const UiManager&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const UiManager&) = delete;	// ������֎~

public:
	// �X�e�[�W�N���X�̐ݒ�
	void SetStage(class StageManager* stage) { m_pStage = stage; }

	// �X�V
	void Update();
	// �`��
	void Draw();

	// UI�̒ǉ�
	void AddUI(class ObjectBase* obj);
	// UI�̍폜
	void DeleteUI(class ObjectBase* obj);
	// �SUI�̍폜
	void DeleteAllUI();

	// �v���C���[���W��ݒ�
	void SetPlayerPos(const VECTOR pos) { m_playerPos = pos; }

	// �X�e�[�W�̃|�C���^�폜
	void DeleteStage() { m_pStage = nullptr; }

private:
	// ���E���h��Ԃ̕`��
	void DrawRoundState();

private:
	// �v���C���[���W
	VECTOR m_playerPos = Game::kVecZero;

private:
	// UI�̃��X�g
	std::list<class UiBar*> m_pUIList;

	// �X�e�[�W�N���X
	class StageManager* m_pStage = nullptr;
};

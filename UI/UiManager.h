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

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �I��
	void End();

	// UI�̒ǉ�
	void AddUIBar(class ObjectBase* obj);
	// UI�̍폜
	void DeleteUIBar(class ObjectBase* obj);
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
	
	// �c�e��UI�摜�n���h��
	int m_bulletUiHandle = -1;

private:
	// UI�̃��X�g
	std::list<class UiBar*> m_pUiBarList;

	// �X�e�[�W�N���X
	class StageManager* m_pStage = nullptr;
};

#pragma once
#include "Game.h"
#include <list>
#include "StageManager.h"

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

	// ���E���h��Ԃ̃|�C���^�ݒ�
	void SetRoundState(RoundState state) { m_roundState = state; }
	// ���E���h�J�E���g�̐ݒ�
	void SetRoundCount(int count) { m_roundCount = count; }

	// �v���C���[���W��ݒ�
	void SetPlayerPos(const VECTOR pos) { m_playerPos = pos; }

private:
	// ���E���h��Ԃ̕`��
	void DrawRoundState();

private:
	// �v���C���[���W
	VECTOR m_playerPos = Game::kVecZero;
	
	// ����UI�摜�n���h��
	int m_weaponUiHandle = -1;

private:
	// UI�o�[�̃��X�g
	std::list<class UiBar*> m_pUiBarList;

	// �v���C���[��HP�o�[
	class UiBar* m_pPlayerHPBar = nullptr;
	// ���E���h��ԊǗ�
	RoundState m_roundState;
	int m_roundCount;
};

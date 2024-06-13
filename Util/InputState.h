#pragma once
#include <EffekseerForDXLib.h>

enum class InputType
{
	// �V�X�e���n�{�^��
	all,	// �S����
	pause,	// �|�[�Y
	select,	// ����
	back,	// �߂�
	space,	// �X�y�[�X
	up,		// ��
	down,	// ��
	right,	// �E
	left,	// ��

	// �Q�[���n�{�^��
	lookUp,			// ���_��
	lookDown,		// ���_��
	lookRight,		// ���_�E
	lookLeft,		// ���_��
	moveForward,	// �O���ړ�
	moveBehind,		// ����ړ�
	moveRight,		// �E�ړ�
	moveLeft,		// ���ړ�
	avoid,			// ���
	shot,			// �U��
};

struct MouseInputState
{
	// �}�E�X�J�[�\�����W
	int x = 0;
	int y = 0;
	// �}�E�X���͏��
	int keyMouseState = 0;
	int lastKeyMouseState = 0;
	// �}�E�X�z�C�[�����͏��
	int mouseWheelState = 0;
};

class InputState
{
public:
	// �g���K�[����
	bool IsTriggered(InputType type)const;
	// �������ݔ���
	bool IsPressed(InputType type)const;
	// ���͏�ԍX�V
	void Update();
	// �}�E�X�z�C�[���̓��͏�Ԏ擾
	bool IsMouseWheel(bool isPlus)const;
	// �p�b�h�X�e�B�b�N�̓��͏�Ԏ擾
	bool IsStickInput(int stickType, bool isPlus)const;
	// �}�E�X�J�[�\���̍��W�擾
	int GetMousePosX()const { return mouseState.x; }
	int GetMousePosY()const { return mouseState.y; }

private:
	int lastPadState = 0;
	int padState = 0;
	char keyState[256];
	char lastKeyState[256];
	// �}�E�X�̓��͏��
	MouseInputState mouseState;
	// �p�b�h�̓��͏��
	DINPUT_JOYSTATE dinputPadState;
};
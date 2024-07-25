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
	dash,			// �_�b�V��
	jump,			// �W�����v
	crouch,			// ���Ⴊ��
	shot,			// �U��
	sprShot,		// �X�y�V�����U��
};

struct MouseInputState
{
	// �}�E�X�J�[�\�����WX
	int x = 0;
	// �}�E�X�J�[�\�����WY
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
	// ���͏�ԍX�V
	void Update();
	// �}�E�X�ړ���Ԏ擾
	float GetMouseMoveX()const;
	float GetMouseMoveY()const;
	// �g���K�[����
	bool IsTriggered(InputType type)const;
	// �������ݔ���
	bool IsPressed(InputType type)const;
	// �}�E�X�J�[�\���̍��W�擾
	int GetMousePosX()const { return mouseState.x; }
	int GetMousePosY()const { return mouseState.y; }

private:
	// �}�E�X�z�C�[���̓��͏�Ԏ擾
	bool IsMouseWheel(bool isPlus)const;
	// �}�E�X�̈ړ���Ԏ擾
	bool IsMouseMoveX(bool isPlus)const;
	bool IsMouseMoveY(bool isPlus)const;
	// �p�b�h�X�e�B�b�N�̓��͏�Ԏ擾
	bool IsStickInput(int stickType, bool isPlus)const;

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
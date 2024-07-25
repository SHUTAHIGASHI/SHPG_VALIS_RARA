#include "InputState.h"
#include "Game.h"

void InputState::Update()
{
	// 前のフレームのキー状況をコピー
	for (int i = 0; i < _countof(lastKeyState); ++i)
	{
		lastKeyState[i] = keyState[i];
	}
	// キーボードキー入力状態取得
	GetHitKeyStateAll(keyState);

	// マウスのキー状態取得
	mouseState.lastKeyMouseState = mouseState.keyMouseState;
	mouseState.keyMouseState = GetMouseInput();
	// マウスホイールの状態管理
	mouseState.mouseWheelState = GetMouseWheelRotVol(true);
	// マウスカーソルの座標取得
	GetMousePoint(&mouseState.x, &mouseState.y);

	// パッドキー状態取得
	lastPadState = padState;
	padState = GetJoypadInputState(DX_INPUT_PAD1);
	// パッドキー状態取得(スティック状態管理用)
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinputPadState);
}

float InputState::GetMouseMoveX() const
{
	return -static_cast<float>(Game::kScreenWidthHalf - mouseState.x);
}

float InputState::GetMouseMoveY() const
{
	return -static_cast<float>(Game::kScreenHeightHalf - mouseState.y);
}

bool InputState::IsTriggered(InputType type)const
{
	if (type == InputType::all)
	{
		return !lastKeyState[KEY_INPUT_RETURN] &&
			keyState[KEY_INPUT_RETURN] ||
			!(lastPadState) &&
			(padState) ||
			!(mouseState.lastKeyMouseState) &&
			(mouseState.keyMouseState);;
	}
	else if (type == InputType::pause)
	{
		return !lastKeyState[KEY_INPUT_ESCAPE] &&
			keyState[KEY_INPUT_ESCAPE] ||
			!(lastPadState & PAD_INPUT_8) &&
			(padState & PAD_INPUT_8);
	}
	else if (type == InputType::select)
	{
		return !lastKeyState[KEY_INPUT_RETURN] &&
			keyState[KEY_INPUT_RETURN] ||
			!(lastPadState & PAD_INPUT_2) &&
			(padState & PAD_INPUT_2) ||
			!(mouseState.lastKeyMouseState & MOUSE_INPUT_LEFT) &&
			(mouseState.keyMouseState & MOUSE_INPUT_LEFT);
	}
	else if (type == InputType::back)
	{
		return !lastKeyState[KEY_INPUT_ESCAPE] &&
			keyState[KEY_INPUT_ESCAPE] ||
			!(lastPadState & PAD_INPUT_1) &&
			(padState & PAD_INPUT_1);
	}
	else if (type == InputType::space)
	{
		return !lastKeyState[KEY_INPUT_SPACE] &&
			keyState[KEY_INPUT_SPACE];
	}
	else if (type == InputType::up)
	{
		return !lastKeyState[KEY_INPUT_UP] &&
			keyState[KEY_INPUT_UP] ||
			!(lastPadState & PAD_INPUT_UP) &&
			(padState & PAD_INPUT_UP) ||
			(IsMouseWheel(true));
	}
	else if (type == InputType::down)
	{
		return !lastKeyState[KEY_INPUT_DOWN] &&
			keyState[KEY_INPUT_DOWN] ||
			!(lastPadState & PAD_INPUT_DOWN) &&
			(padState & PAD_INPUT_DOWN) ||
			(IsMouseWheel(false));
	}
	else if (type == InputType::right)
	{
		return !lastKeyState[KEY_INPUT_RIGHT] &&
			keyState[KEY_INPUT_RIGHT] ||
			!(lastPadState & PAD_INPUT_RIGHT) &&
			(padState & PAD_INPUT_RIGHT) ||
			(IsMouseWheel(false));
	}
	else if (type == InputType::left)
	{
		return !lastKeyState[KEY_INPUT_LEFT] &&
			keyState[KEY_INPUT_LEFT] ||
			!(lastPadState & PAD_INPUT_LEFT) &&
			(padState & PAD_INPUT_LEFT) ||
			(IsMouseWheel(true));
	}
	else if (type == InputType::lookUp)
	{
		return !lastKeyState[KEY_INPUT_UP] &&
			keyState[KEY_INPUT_UP] ||
			!(lastPadState & PAD_INPUT_UP) &&
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::lookDown)
	{
		return !lastKeyState[KEY_INPUT_DOWN] &&
			keyState[KEY_INPUT_DOWN] ||
			!(lastPadState & PAD_INPUT_DOWN) &&
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::lookRight)
	{
		return !lastKeyState[KEY_INPUT_RIGHT] &&
			keyState[KEY_INPUT_RIGHT] ||
			!(lastPadState & PAD_INPUT_RIGHT) &&
			(padState & PAD_INPUT_RIGHT);;
	}
	else if (type == InputType::lookLeft)
	{
		return !lastKeyState[KEY_INPUT_LEFT] &&
			keyState[KEY_INPUT_LEFT] ||
			!(lastPadState & PAD_INPUT_LEFT) &&
			(padState & PAD_INPUT_LEFT);
	}
	else if (type == InputType::moveForward)
	{
		return !lastKeyState[KEY_INPUT_W] &&
			keyState[KEY_INPUT_W] ||
			!(lastPadState & PAD_INPUT_UP) &&
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::moveBehind)
	{
		return !lastKeyState[KEY_INPUT_S] &&
			keyState[KEY_INPUT_S] ||
			!(lastPadState & PAD_INPUT_DOWN) &&
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::moveRight)
	{
		return !lastKeyState[KEY_INPUT_D] &&
			keyState[KEY_INPUT_D] ||
			!(lastPadState & PAD_INPUT_RIGHT) &&
			(padState & PAD_INPUT_RIGHT);;
	}
	else if (type == InputType::moveLeft)
	{
		return !lastKeyState[KEY_INPUT_A] &&
			keyState[KEY_INPUT_A] ||
			!(lastPadState & PAD_INPUT_LEFT) &&
			(padState & PAD_INPUT_LEFT);
	}
	else if (type == InputType::dash)
	{
		return !lastKeyState[KEY_INPUT_LSHIFT] &&
			keyState[KEY_INPUT_LSHIFT] ||
			!(lastPadState & PAD_INPUT_3) &&
			(padState & PAD_INPUT_3);
			}
	else if (type == InputType::jump)
	{
		return !lastKeyState[KEY_INPUT_SPACE] &&
			keyState[KEY_INPUT_SPACE];
	}
	else if (type == InputType::crouch)
	{
		return !lastKeyState[KEY_INPUT_LCONTROL] &&
			keyState[KEY_INPUT_LCONTROL] ||
			!lastKeyState[KEY_INPUT_C] &&
			keyState[KEY_INPUT_C];
	}
	else if (type == InputType::shot)
	{
		return !lastKeyState[KEY_INPUT_RSHIFT] &&
			keyState[KEY_INPUT_RSHIFT] ||
			!(lastPadState & PAD_INPUT_2) &&
			(padState & PAD_INPUT_2) ||
			!(mouseState.lastKeyMouseState & MOUSE_INPUT_LEFT) &&
			(mouseState.keyMouseState & MOUSE_INPUT_LEFT);
	}
	else if (type == InputType::sprShot)
	{
		return !(lastPadState & PAD_INPUT_1) &&
			(padState & PAD_INPUT_1) ||
			!(mouseState.lastKeyMouseState & MOUSE_INPUT_RIGHT) &&
			(mouseState.keyMouseState & MOUSE_INPUT_RIGHT);
	}

	return false;
}

bool InputState::IsPressed(InputType type)const
{
	if (type == InputType::pause)
	{
		return keyState[KEY_INPUT_ESCAPE] ||
			(padState & PAD_INPUT_8);
	}
	else if (type == InputType::select)
	{
		return keyState[KEY_INPUT_RETURN] ||
			(padState & PAD_INPUT_2);
	}
	else if (type == InputType::back)
	{
		return keyState[KEY_INPUT_ESCAPE] ||
			(padState & PAD_INPUT_1);
	}
	else if (type == InputType::space)
	{
		return keyState[KEY_INPUT_SPACE];
	}
	else if (type == InputType::up)
	{
		return keyState[KEY_INPUT_UP] ||
			keyState[KEY_INPUT_W] ||
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::down)
	{
		return keyState[KEY_INPUT_DOWN] ||
			keyState[KEY_INPUT_S] ||
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::right)
	{
		return keyState[KEY_INPUT_RIGHT] ||
			keyState[KEY_INPUT_D] ||
			(padState & PAD_INPUT_RIGHT);;
	}
	else if (type == InputType::left)
	{
		return keyState[KEY_INPUT_LEFT] ||
			keyState[KEY_INPUT_A] ||
			(padState & PAD_INPUT_LEFT);
	}
	else if (type == InputType::lookUp)
	{
		return keyState[KEY_INPUT_UP] ||
			(IsStickInput(dinputPadState.Ry, false))/*||
			(IsMouseMoveY(false))*/;
	}
	else if (type == InputType::lookDown)
	{
		return keyState[KEY_INPUT_DOWN] ||
			(IsStickInput(dinputPadState.Ry, true))/*||
			(IsMouseMoveY(true))*/;
	}
	else if (type == InputType::lookRight)
	{
		return keyState[KEY_INPUT_RIGHT] ||
			(IsStickInput(dinputPadState.Rx, true))/*||
			(IsMouseMoveX(true))*/;
	}
	else if (type == InputType::lookLeft)
	{
		return keyState[KEY_INPUT_LEFT] ||
			(IsStickInput(dinputPadState.Rx, false))/*||
			(IsMouseMoveX(false))*/;
	}
	else if (type == InputType::moveForward)
	{
		return keyState[KEY_INPUT_W] ||
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::moveBehind)
	{
		return keyState[KEY_INPUT_S] ||
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::moveRight)
	{
		return keyState[KEY_INPUT_D] ||
			(padState & PAD_INPUT_RIGHT);
	}
	else if (type == InputType::moveLeft)
	{
		return keyState[KEY_INPUT_A] ||
			(padState & PAD_INPUT_LEFT);
	}
	else if (type == InputType::dash)
	{
		return keyState[KEY_INPUT_LSHIFT] ||
			(padState & PAD_INPUT_3);
	}
	else if (type == InputType::jump)
	{
		return keyState[KEY_INPUT_SPACE];
	}
	else if (type == InputType::crouch)
	{
		return keyState[KEY_INPUT_LCONTROL] ||
			keyState[KEY_INPUT_C];
	}
	else if (type == InputType::shot)
	{
		return keyState[KEY_INPUT_RSHIFT] ||
			(padState & PAD_INPUT_2) ||
			(mouseState.keyMouseState & MOUSE_INPUT_LEFT);
	}
	else if (type == InputType::sprShot)
	{
		return keyState[KEY_INPUT_RSHIFT] ||
			(padState & PAD_INPUT_1) ||
			(mouseState.keyMouseState & MOUSE_INPUT_RIGHT);
	}

	return false;
}

bool InputState::IsMouseWheel(bool isPlus) const
{
	if (isPlus)
	{
		if (mouseState.mouseWheelState > 0)
		{
			return true;
		}
	}
	else
	{
		if (mouseState.mouseWheelState < 0)
		{
			return true;
		}
	}

	return false;
}

bool InputState::IsMouseMoveX(bool isPlus) const
{
	if (isPlus)
	{
		if (mouseState.x > Game::kScreenWidthHalf)
		{
			return true;
		}
	}
	else
	{
		if (mouseState.x < Game::kScreenWidthHalf)
		{
			return true;
		}
	}

	return false;
}

bool InputState::IsMouseMoveY(bool isPlus) const
{
	if (isPlus)
	{
		if (mouseState.y > Game::kScreenHeightHalf)
		{
			return true;
		}
	}
	else
	{
		if (mouseState.y < Game::kScreenHeightHalf)
		{
			return true;
		}
	}

	return false;
}

bool InputState::IsStickInput(int stickType, bool isPlus)const
{
	if (isPlus)
	{
		if (stickType > 0)
		{
			return true;
		}
	}
	else
	{
		if (stickType < 0)
		{
			return true;
		}
	}

	return false;
}

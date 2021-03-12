#pragma once
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>

enum PadButton {

	A,B,X,Y,Start,Options,Up,Down,Left,Right,LeftShoulder,RightShoulder,LeftStick,RightStick

};

class ControlInput
{
public:
	ControlInput() {


		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(0, &state) == ERROR_SUCCESS)
		{
			printf("Controller is in port 1.\n");
			//while (true) {}
			// controller is connected on port 0
		}
		else {
			printf("No controller.\n");
			//while (true) {

			//}
		}

	}

	bool IsPressed(PadButton button)
	{
		WORD but;
		switch (button) {
		case PadButton::A:
			but = XINPUT_GAMEPAD_A;
			break;
		case PadButton::B:
			but = XINPUT_GAMEPAD_B;
			break;
		case PadButton::X:
			but = XINPUT_GAMEPAD_X;
			break;
		case PadButton::Y:
			but = XINPUT_GAMEPAD_Y;
			break;
		case PadButton::Start:
			but = XINPUT_GAMEPAD_START;
			break;
		case PadButton::Options:
			but = XINPUT_GAMEPAD_BACK;
			break;
		case PadButton::Up:
			but = XINPUT_GAMEPAD_DPAD_UP;
			break;
		case PadButton::Down:
			but = XINPUT_GAMEPAD_DPAD_DOWN;
			break;
		case PadButton::Left:
			but = XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		case PadButton::Right:
			but = XINPUT_GAMEPAD_DPAD_RIGHT;
		case PadButton::LeftShoulder:
			but = XINPUT_GAMEPAD_LEFT_SHOULDER;
			break;
		case PadButton::RightShoulder:
			but = XINPUT_GAMEPAD_RIGHT_SHOULDER;
			break;
		case PadButton::LeftStick:
			but = XINPUT_GAMEPAD_LEFT_THUMB;
			break;
		case PadButton::RightStick:
			but = XINPUT_GAMEPAD_RIGHT_THUMB;
			break;

			
		}

		return (state.Gamepad.wButtons & but) !=0;

	}

	void Update() {

		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(0, &state) != ERROR_SUCCESS)
		{
			//cId = -1;
			//return false;

		}

		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)state.Gamepad.bRightTrigger / 255;

	}
	XINPUT_STATE state;
	float leftStickX, leftStickY;
	float rightStickX, rightStickY;
	float leftTrigger, rightTrigger;
	float deadzoneX = 0.05f;
	float deadzoneY = 0.02f;
};



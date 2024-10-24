#include "user_input.hpp"
#include <raylib/raylib.h>


void User_Input::process(Input_Observer& observer, float)
{
	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsKeyPressed(KEY_UP))
		observer.handle_input_event(Input_Event::up_pressed);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsKeyPressed(KEY_DOWN))
		observer.handle_input_event(Input_Event::down_pressed);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || IsKeyPressed(KEY_LEFT))
		observer.handle_input_event(Input_Event::left_pressed);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || IsKeyPressed(KEY_RIGHT))
		observer.handle_input_event(Input_Event::right_pressed);

	if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsKeyReleased(KEY_UP))
		observer.handle_input_event(Input_Event::up_released);

	if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsKeyReleased(KEY_DOWN))
		observer.handle_input_event(Input_Event::down_released);

	if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || IsKeyReleased(KEY_LEFT))
		observer.handle_input_event(Input_Event::left_released);

	if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || IsKeyReleased(KEY_RIGHT))
		observer.handle_input_event(Input_Event::right_released);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyPressed(KEY_ENTER))
		observer.handle_input_event(Input_Event::accept);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) || IsKeyPressed(KEY_ESCAPE))
		observer.handle_input_event(Input_Event::escape);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) || IsKeyPressed(KEY_I))
		observer.handle_input_event(Input_Event::open_inventory);

	if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP) || IsKeyPressed(KEY_Q))
		observer.handle_input_event(Input_Event::open_quest_log);
}

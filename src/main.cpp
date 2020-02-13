#include <Windows.h>
#include <xinput.h>
#include <iostream>

#define XINPUT_GAMEPAD_THUMB_DEADZONE 9000


bool ControllerProcessInput() {
  for (DWORD ControllerIndex = 0;
       ControllerIndex < XUSER_MAX_COUNT;
       ControllerIndex++){
    
    XINPUT_STATE ControllerState;
    XINPUT_VIBRATION Vibration;
    
    if (XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS) {
      // controller is pluged in
      XINPUT_GAMEPAD *Pad = &ControllerState.Gamepad;

      if (Pad->bLeftTrigger)
	std::cout << "LeftTrigger is pressed\n";
      if (Pad->bRightTrigger)
	std::cout << "RightTrigger is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP)
	std::cout << "Up button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	std::cout << "Down button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	std::cout << "Left button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	std::cout << "Right button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_START) {
	std::cout << "Start button is pressed\n";
	return(false);
      }
      if (Pad->wButtons & XINPUT_GAMEPAD_BACK)
	std::cout << "Back button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
	std::cout << "LeftThumb button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
	std::cout << "RightThumb button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	std::cout << "LeftShoulder button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	std::cout << "RightShoulder button is pressed\n";
      if (Pad->wButtons & XINPUT_GAMEPAD_A) {
	std::cout << "A button is pressed\n";
	Vibration.wLeftMotorSpeed = 30000;
	Vibration.wRightMotorSpeed = 30000;
	XInputSetState(ControllerIndex, &Vibration);
	std::cout << "Vibration on\n";	
      }
      if (Pad->wButtons & XINPUT_GAMEPAD_B) {
	std::cout << "B button is pressed\n";
      }
      if (Pad->wButtons & XINPUT_GAMEPAD_X) {
	std::cout << "X button is pressed\n";
	Vibration.wLeftMotorSpeed = 0;
	Vibration.wRightMotorSpeed = 0;
	XInputSetState(ControllerIndex, &Vibration);
	std::cout << "Vibration off\n";
      }
      if (Pad->wButtons & XINPUT_GAMEPAD_Y)
	std::cout << "Y button is pressed\n";
      
      int16_t LeftStickX = Pad->sThumbLX;
      int16_t LeftStickY = Pad->sThumbLY;
      if (abs(LeftStickX) > XINPUT_GAMEPAD_THUMB_DEADZONE || \
	  abs(LeftStickY) > XINPUT_GAMEPAD_THUMB_DEADZONE) {
	std::cout << "Left stick coords X Y: " << LeftStickX << " : "<< LeftStickY << std::endl;
      }
      
      int16_t RightStickX = Pad->sThumbRX;
      int16_t RightStickY = Pad->sThumbRY;      
      if ( abs(RightStickX) > XINPUT_GAMEPAD_THUMB_DEADZONE || \
	   abs(RightStickY) > XINPUT_GAMEPAD_THUMB_DEADZONE ) {
	std::cout << "Right stick coords X Y: " << RightStickX << " : "<< RightStickY << std::endl;
      }
      return(true);     
    }
  }
}

int main() {
  std::cout << "\t\t\t#######################################\n";
  std::cout << "\t\t\t#Xbox gamepad buttons testing programm#\n";
  std::cout << "\t\t\t#      For exit press the start       #\n";
  std::cout << "\t\t\t#       vibration on - A button       #\n";
  std::cout << "\t\t\t#       vibration off - X button      #\n";
  std::cout << "\t\t\t#######################################\n";
  while(ControllerProcessInput()) {
    Sleep(100);
  }
  return(0);
}

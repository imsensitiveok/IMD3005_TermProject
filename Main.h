#pragma once

//analog
#define JOYSTICK_X 0
#define JOYSTICK_Y 1
#define PROXIMITY 2



//digital
#define BUTTON_INFO 10
#define BUTTON_ATTACK 11
#define LIGHT_ON_RIGHT 5
#define LIGHT_ON_LEFT 6
//#define LIGHT_PROXIMITY_RIGHT 3
//#define LIGHT_PROXIMITY_RIGHT 4

//arduino:
#define ARDUINO_NAME "COM6"

//window:
#define WINDOW_SIZE 800

//joystick:
#define JOYSTICK_DEFAULT_X 501
#define JOYSTICK_DEFAULT_Y 529


//light:
#define HIGH 255

//maze:
#define MAZE_BORDER_SIZE 30

//header files:
#include "ofMain.h"
#include "ofEvents.h"
#include "GameObject.h"
#include "ofApp.h"
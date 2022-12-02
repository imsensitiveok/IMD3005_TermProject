#pragma once

//analog
#define JOYSTICK_X 0
#define JOYSTICK_Y 1
#define BUTTON_INFO 2
#define BUTTON_ATTACK 3

//digital
#define LIGHT_ON_RIGHT 1
#define LIGHT_ON_LEFT 2
#define LIGHT_PROXIMITY_RIGHT 3
#define LIGHT_PROXIMITY_RIGHT 4

//arduino:
#define ARDUINO_NAME "COM5"

//window:
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

//joystick:
#define JOYSTICK_DEFAULT_X 501
#define JOYSTICK_DEFAULT_Y 529
#define JOYSTICK_MAX 1023
#define JOYSTICK_MIN 0

//maze:
#define MAZE_BORDER_SIZE 25

//header files:
#include "ofMain.h"
#include "ofEvents.h"
#include "GameObject.h"
#include "ofApp.h"
#pragma once

#include "Main.h"

//namespace config {
//	//static const std::string ARDUINO_DEVICE_NAME = "COM3";		//WIN
//	//static const std::string ARDUINO_DEVICE_NAME = "/dev/cu.usbmodem144101";	//MAC
//};

class ofApp : public ofBaseApp
{
public:
	//static const int PIN_ANALOG_INPUT = 5;
	//static const int PIN_PWM_OUTPUT = 9;

	void setup();
	void update();
	void draw();

	//Arduino stuff
	ofArduino				m_arduino;
	
	//ofTrueTypeFont          m_font;
	
	int m_input_val;	//sensor value
	bool m_bSetup;       //is Arduinio initialized yet
	
	void setupArduino(const int& _version);
	void updateArduino();
	void digitalPinChanged(const int& pinNum);
	void analogPinChanged(const int& pinNum);

	float getIRDistance(int& val);


	//game variables:

	GameObject player;

	GameObject obstacle1;
	GameObject obstacle2;

	GameObject goal;

	ofRectangle mazeWall[15];

	int speed;

};

#pragma once

#include "Main.h"


class ofApp : public ofBaseApp
{
public:

	ofArduino m_arduino;
	
	GameObject player;
	GameObject obstacle1;
	GameObject obstacle2;
	GameObject goal;

	ofImage instructions;		//image of instructions

	ofRectangle mazeWall[16];

	int mazeUnit;
	int speed;
	int proximity_val;			//proximity sensor value

	bool arduinoSetup;			//if Arduinio initialized yet
	bool showInstructions;
	bool won;

	//FUNCTIONS:
	void setup();
	void update();
	void draw();
	void setupArduino(const int& _version);
	void updateArduino();
	void digitalPinChanged(const int& pinNum);
	void analogPinChanged(const int& pinNum);
	void keyPressed(int key);
};

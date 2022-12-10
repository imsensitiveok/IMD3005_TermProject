#include "Main.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(WINDOW_SIZE, WINDOW_SIZE);
    ofSetWindowTitle("Maze Game");

    cout << "starting" << endl;

    //setup Arduino
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application (Tools Menu -> Port) 
    m_arduino.connect(ARDUINO_NAME, 57600);

    // Listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

    arduinoSetup = false;


    instructions.load("instructions.png");

    proximity_val = 0;


    //Set up GameObjects:

    player.x = 60;
    player.y = 60;
    player.r = 0;
    player.g = 255;
    player.b = 0;

    obstacle1.x = 550;
    obstacle1.y = 230;

    obstacle2.x = 320;
    obstacle2.y = 390;

    goal.x = 400;
    goal.y = 690;
    goal.r = 255;
    goal.g = 255;
    goal.b = 0;

    speed = 1;

    mazeUnit = WINDOW_SIZE / 5;

    showInstructions = false;
    won = false;
}

//--------------------------------------------------------------
void ofApp::update()
{
    //CHECKS IF GAME IS WON:
    if (goal.rect.inside(player.x + player.width/2, player.y + player.height/2)) {
        won = true;
    }

    //JOYSTICK MOVEMENT:
    if (m_arduino.getAnalog(JOYSTICK_Y) < 300) {
        player.y += speed;
    }
    else if (m_arduino.getAnalog(JOYSTICK_Y) > 800) {
        player.y -= speed;
    }

    if (m_arduino.getAnalog(JOYSTICK_X) < 300) {
        player.x += speed;
    }
    else if (m_arduino.getAnalog(JOYSTICK_X) > 800) {
        player.x -= speed;
    }

    updateArduino();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetBackgroundColor(0, 0, 0);

    //DRAW WIN SCREEN:
    if (won == true) {
        ofSetColor(0, 0, 0, 90);
        ofDrawRectangle(0, 0, WINDOW_SIZE, WINDOW_SIZE);
        ofSetColor(255, 255, 255);
        //ofScale(10);
        ofDrawBitmapString("You Won!", 300, 500);
    } 
    else {
        //DRAW GAME OBJECTS:
        
        player.Draw();
        
        if (obstacle1.isKilled == false) {
            obstacle1.Draw();
        }
        if (obstacle2.isKilled == false) {
            obstacle2.Draw();
        }
        goal.Draw();


        //DRAW MAZE:
        ofSetColor(255, 255, 255);
        //BORDER:
        ofDrawRectangle(0, 0, WINDOW_SIZE, MAZE_BORDER_SIZE);
        ofDrawRectangle(0, WINDOW_SIZE - MAZE_BORDER_SIZE, WINDOW_SIZE, MAZE_BORDER_SIZE);
        ofDrawRectangle(0, 0, MAZE_BORDER_SIZE, WINDOW_SIZE);
        ofDrawRectangle(WINDOW_SIZE - MAZE_BORDER_SIZE, 0, MAZE_BORDER_SIZE, WINDOW_SIZE);
        //ROW 1:
        ofDrawRectangle(0, mazeUnit * 1, mazeUnit * 2, MAZE_BORDER_SIZE);
        ofDrawRectangle(mazeUnit * 3, mazeUnit * 1, mazeUnit * 1, MAZE_BORDER_SIZE);
        //ROW 2:
        ofDrawRectangle(mazeUnit * 2, mazeUnit * 2, mazeUnit * 2, MAZE_BORDER_SIZE);
        //ROW 3:
        ofDrawRectangle(0, mazeUnit * 3, mazeUnit * 1, MAZE_BORDER_SIZE);
        ofDrawRectangle(mazeUnit * 2, mazeUnit * 3, mazeUnit * 1, MAZE_BORDER_SIZE);
        //ROW 4:
        ofDrawRectangle(mazeUnit * 1, mazeUnit * 4, mazeUnit * 3, MAZE_BORDER_SIZE);
        //COLUMN 1:
        ofDrawRectangle(mazeUnit * 1, mazeUnit * 2, MAZE_BORDER_SIZE, mazeUnit * 1 + MAZE_BORDER_SIZE);
        //COLUMN 2:
        ofDrawRectangle(mazeUnit * 2, mazeUnit * 1, MAZE_BORDER_SIZE, mazeUnit * 1 + MAZE_BORDER_SIZE);
        ofDrawRectangle(mazeUnit * 2, mazeUnit * 3, MAZE_BORDER_SIZE, mazeUnit * 1 + MAZE_BORDER_SIZE);
        //COLUMN 3:
        ofDrawRectangle(mazeUnit * 3, mazeUnit * 0, MAZE_BORDER_SIZE, mazeUnit * 1 + MAZE_BORDER_SIZE);
        ofDrawRectangle(mazeUnit * 3, mazeUnit * 4, MAZE_BORDER_SIZE, mazeUnit * 1 + MAZE_BORDER_SIZE);
        //COLUMN 4:
        ofDrawRectangle(mazeUnit * 4, mazeUnit * 3, MAZE_BORDER_SIZE, mazeUnit * 1 + MAZE_BORDER_SIZE);

        if (showInstructions == true) {
            instructions.draw(0, 0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& _version)
{

    arduinoSetup = true;

    // remove listener because we don't need it anymore
    ofRemoveListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

    // print firmware name and version to the console
    cout << m_arduino.getFirmwareName() << endl;
    cout << "firmata v" << m_arduino.getMajorFirmwareVersion() << "." << m_arduino.getMinorFirmwareVersion() << endl;


    //analog input
    m_arduino.sendAnalogPinReporting(JOYSTICK_X, ARD_ANALOG);
    m_arduino.sendAnalogPinReporting(JOYSTICK_Y, ARD_ANALOG);
    m_arduino.sendAnalogPinReporting(PROXIMITY, ARD_ANALOG);

    
    //PMW/digital output
    m_arduino.sendDigitalPinMode(LIGHT_ON_RIGHT, ARD_PWM);
    m_arduino.sendDigitalPinMode(LIGHT_ON_LEFT, ARD_PWM);
    m_arduino.sendDigitalPinMode(BUTTON_INFO, ARD_INPUT);
    m_arduino.sendDigitalPinMode(BUTTON_ATTACK, ARD_INPUT);


    ofAddListener(m_arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(m_arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);

    //turn lights on
    //m_arduino.sendPwm(LIGHT_ON_LEFT, 255);
    //m_arduino.sendPwm(LIGHT_ON_RIGHT, 255);
}

//--------------------------------------------------------------
void ofApp::updateArduino() {

    m_arduino.update();
}

void ofApp::digitalPinChanged(const int& pinNum) {
    
    if (pinNum == BUTTON_ATTACK) {

        if (obstacle1.rect.inside(player.x + player.width / 2, player.y + player.height / 2)) {
            obstacle1.isKilled = true;
        }
        else if (obstacle2.rect.inside(player.x + player.width / 2, player.y + player.height / 2)) {
            obstacle2.isKilled = true;
        }
    }

    if (pinNum == BUTTON_INFO) {
        if (showInstructions == true) {
            showInstructions = false;
        } else if (showInstructions == false) {
            showInstructions = true;
        }
    }

}

void ofApp::analogPinChanged(const int& pinNum) {

    //std::cout  << "analog pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getAnalog(pinNum)) << std::endl;

    //cout << "X: " << m_arduino.getAnalog(JOYSTICK_X) << "Y: " << m_arduino.getAnalog(JOYSTICK_Y) << endl;

    if (pinNum == PROXIMITY) {

        //get analog value
        proximity_val = m_arduino.getAnalog(pinNum);
        
        //set speed
        speed = (int)ofMap(proximity_val, 0, 700, 1, 5);
        
        //setup proximity light:
        proximity_light = (int)ofMap(proximity_val, 0, 700, 0, 255);
        m_arduino.sendPwm(LIGHT_ON_LEFT, proximity_light);
        m_arduino.sendPwm(LIGHT_ON_RIGHT, proximity_light);
        
    }

}


void ofApp::keyPressed(int key) {

    //SPACEBAR:
    if (key == 32 && showInstructions == false) {
        showInstructions = true;
    }
    else if (key == 32 && showInstructions == true) {
        showInstructions = false;
    }

    //A KEY
    if (key == 'a') {
        if (obstacle1.rect.inside(player.x, player.y)) {
            obstacle1.isKilled = true;
        }
        else if (obstacle2.rect.inside(player.x, player.y)) {
            obstacle2.isKilled = true;
        }
    }
}

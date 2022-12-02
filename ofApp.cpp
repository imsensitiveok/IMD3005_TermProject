#include "Main.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
    //ofSetFrameRate(10);

    //m_font.load("franklinGothic.otf", 16);

    cout << "starting" << endl;

    //setup Arduino
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application (Tools Menu -> Port) 
    m_arduino.connect(ARDUINO_NAME, 57600);

    m_input_val = 0.0f;

    // Listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

    m_bSetup = false;

    //Set up GameObjects

    player.x = 0;
    player.y = 0;
    player.r = 0;
    player.g = 255;
    player.b = 0;

    obstacle1.x = 100;
    obstacle1.y = 100;
    obstacle1.r = 255;
    obstacle1.g = 0;
    obstacle1.b = 0;

    obstacle2.x = 300;
    obstacle2.y = 300;
    obstacle2.r = 255;
    obstacle2.g = 0;
    obstacle2.b = 0;

    goal.x = 300;
    goal.y = 300;
    goal.r = 255;
    goal.g = 255;
    goal.b = 0;

    speed = 1;

}

//--------------------------------------------------------------
void ofApp::update()
{
    //JOYSTICK:
    if (m_arduino.getAnalog(JOYSTICK_Y) < 300) {
        player.y += 1 * speed;
    }
    else if (m_arduino.getAnalog(JOYSTICK_Y) > 800) {
        player.y -= 1 * speed;
    }

    if (m_arduino.getAnalog(JOYSTICK_X) < 300) {
        player.x += 1 * speed;
    }
    else if (m_arduino.getAnalog(JOYSTICK_X) > 800) {
        player.x -= 1 * speed;
    }

    updateArduino();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetBackgroundColor(0, 0, 0);

    //ofEnableAlphaBlending();
    //ofSetColor(0, 0, 0, 127);
    //ofDrawRectangle(510, 15, 275, 150);
    //ofDisableAlphaBlending();

    ofSetColor(255, 255, 255);
    
    // Draw sensor input values
    //m_font.drawString("Sensor Value: " + ofToString(m_input_val), 530, 105);

    // remap our flex values (can check on arduino sketch as values will always vary between sensors)
    //float radius = ofMap(m_input_val, 0, 255, 20, 150);
    //ofDrawCircle(640, 400, radius);

    //BORDER:
    ofDrawRectangle(0, 0, WINDOW_WIDTH, MAZE_BORDER_SIZE);
    ofDrawRectangle(0, WINDOW_HEIGHT - MAZE_BORDER_SIZE, WINDOW_WIDTH, MAZE_BORDER_SIZE);
    ofDrawRectangle(0, 0, MAZE_BORDER_SIZE, WINDOW_HEIGHT);
    ofDrawRectangle(WINDOW_WIDTH - MAZE_BORDER_SIZE, 0, MAZE_BORDER_SIZE, WINDOW_HEIGHT);

    ofDrawRectangle(0, 100, 200, MAZE_BORDER_SIZE);


    //Draw the GameObjects
    player.Draw();
    obstacle1.Draw();
    obstacle2.Draw();
    goal.Draw();
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& _version)
{

    m_bSetup = true;

    // remove listener because we don't need it anymore
    ofRemoveListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

    // print firmware name and version to the console
    cout << m_arduino.getFirmwareName() << endl;
    cout << "firmata v" << m_arduino.getMajorFirmwareVersion() << "." << m_arduino.getMinorFirmwareVersion() << endl;
    

    //analog input
    m_arduino.sendAnalogPinReporting(JOYSTICK_X, ARD_ANALOG);
    m_arduino.sendAnalogPinReporting(JOYSTICK_Y, ARD_ANALOG);
    m_arduino.sendAnalogPinReporting(BUTTON_INFO, ARD_ANALOG);
    m_arduino.sendAnalogPinReporting(BUTTON_ATTACK, ARD_ANALOG);

    //PMW/digital output
    m_arduino.sendDigitalPinMode(LIGHT_ON_RIGHT, ARD_PWM);
    m_arduino.sendDigitalPinMode(LIGHT_ON_LEFT, ARD_PWM);
    m_arduino.sendDigitalPinMode(LIGHT_PROXIMITY_RIGHT, ARD_PWM);
    m_arduino.sendDigitalPinMode(LIGHT_PROXIMITY_RIGHT, ARD_PWM);

    ofAddListener(m_arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(m_arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino() {

    // update the arduino, get any data or messages.
    // the call to m_arduino.update() is required
    m_arduino.update();
}

void ofApp::digitalPinChanged(const int& pinNum) {

    //std::cout  << "digital pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getDigital(pinNum)) << std::endl;
}

void ofApp::analogPinChanged(const int& pinNum) {
    //std::cout  << "analog pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getAnalog(pinNum)) << std::endl;

    //cout << "X: " << m_arduino.getAnalog(JOYSTICK_X) << "Y: " << m_arduino.getAnalog(JOYSTICK_Y) << endl;



}

//!!convert voltage signal into a readable result distance in cm (convenience function for for distance sensor - from IR sensor specs)
float ofApp::getIRDistance(int& val)
{
    if (val < 16)
    {
        val = 16;
    }

    return 2076.0f / (val - 11.0f);
}
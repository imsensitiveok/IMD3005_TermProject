#include "Main.h"

GameObject::GameObject() {
    x = 0;
    y = 0;

    r = 255;
    g = 255;
    b = 255;

    width = 40;
    height = 40;

    //possibly move to ofApp
    speed = 0;
}

GameObject::~GameObject() {
}

void GameObject::Draw() {
    ofSetColor(r, g, b, 255);

    rect.x = x;
    rect.y = y;

    rect.width = width;
    rect.height = height;

    ofDrawRectangle(rect);
    ofSetColor(0, 0, 0, 255);
}
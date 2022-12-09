#include "Main.h"

GameObject::GameObject() {
    x = 0;
    y = 0;

    r = 255;
    g = 0;
    b = 0;

    width = 60;
    height = 60;

    isKilled = false;
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
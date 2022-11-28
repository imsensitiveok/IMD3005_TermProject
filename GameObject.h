#pragma once

class GameObject {
public:
    ofRectangle rect;

    int x;
    int y;

    int r;
    int g;
    int b;

    int width;
    int height;

    void Draw();


    int speed;
    

    GameObject();
    ~GameObject();


};


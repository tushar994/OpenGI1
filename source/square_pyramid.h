#include "main.h"

#ifndef SQUARE_PYRAMID_H
#define SQUARE_PYRAMID_H

class Square_Pyramid
{
public:
    Square_Pyramid() {}
    Square_Pyramid(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object[16];
};

#endif // BALL_H

#include "main.h"

#ifndef DISPHENOID_H
#define DISPHENOID_H

class Disphenoid
{
public:
    Disphenoid() {}
    Disphenoid(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object[12];
};

#endif // BALL_H

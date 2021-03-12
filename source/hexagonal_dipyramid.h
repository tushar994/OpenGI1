#include "main.h"

#ifndef HEXAGONAL_DIPYRAMID_H
#define HEXAGONAL_DIPYRAMID_H

class Hexagonal_dipyramid
{
public:
    Hexagonal_dipyramid() {}
    Hexagonal_dipyramid(float x, float y, color_t color);
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

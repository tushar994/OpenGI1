#include "hexagonal_dipyramid.h"
#include "main.h"


Hexagonal_dipyramid::Hexagonal_dipyramid(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float a = 1.0;
    float b = sqrt(3)/2;
    float c = 1/2;
    float d = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[12][9] = {
        // the top part
        {0.0f,0.0f,1.0f,
        -0.86f,0.5f,0.0f,
        0.0f,1.0f,0.0f},
        {0.0f,0.0f,1.0f,
        0.86f,0.5f,0.0f,
        0.0f,1.0f,0.0f},

        {0.0f,0.0f,1.0f,
        0.86f,0.5f,0.0f,
        0.86f,-0.5f,0.0f},

        {0.0f,0.0f,1.0f,
        0.0f,-1.0f,0.0f,
        0.86f,-0.5f,0.0f},

        {0.0f,0.0f,1.0f,
        0.0f,-1.0f,0.0f,
        -0.86f,-0.5f,0.0f},

        {0.0f,0.0f,1.0f,
        -0.86f,0.5f,0.0f,
        -0.86f,-0.5f,0.0f},

        {0.0f,0.0f,-1.0f,
        -0.86f,0.5f,0.0f,
        0.0f,1.0f,0.0f},
        {0.0f,0.0f,-1.0f,
        0.86f,0.5f,0.0f,
        0.0f,1.0f,0.0f},

        {0.0f,0.0f,-1.0f,
        0.86f,0.5f,0.0f,
        0.86f,-0.5f,0.0f},

        {0.0f,0.0f,-1.0f,
        0.0f,-1.0f,0.0f,
        0.86f,-0.5f,0.0f},

        {0.0f,0.0f,-1.0f,
        0.0f,-1.0f,0.0f,
        -0.86f,-0.5f,0.0f},

        {0.0f,0.0f,-1.0f,
        -0.86f,0.5f,0.0f,
        -0.86f,-0.5f,0.0f},
        };
        color_t colors[8] = {COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_BRO, COLOR_1, COLOR_2, COLOR_3, COLOR_4};
    for(int i=0;i<12;i++){

        this->object[i] = create3DObject(GL_TRIANGLES, 1 * 3, vertex_buffer_data[i], colors[i%8], GL_FILL);
    }
}

void Hexagonal_dipyramid::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<12;i++){
        // printf("what");
        draw3DObject(this->object[i]);
    }
}

void Hexagonal_dipyramid::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Hexagonal_dipyramid::tick()
{
    if(rotate_object){
        this->rotation += 1;
    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}

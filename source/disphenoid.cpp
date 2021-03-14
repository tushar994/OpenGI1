#include "disphenoid.h"
#include "main.h"

float speed = 0.1;
Disphenoid::Disphenoid(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float a = 1.56;
    float b = 0.41;
    float c = 1.28;
    float d = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[12][9] = {
        {0.0f,-0.41f,1.28f,
        -1.28f,0.41f,0.0f,
        -1.0f,-1.56f,0.0f},
        
        {0.0f,-0.41f,1.28f,
        1.0f,-1.56f,0.0f,
        -1.0f,-1.56f,0.0f},
        
        {0.0f,-0.41f,1.28f,
        1.0f,-1.56f,0.0f,
        1.28f,0.41f,0.0f},

        {0.0f,-0.41f,1.28f,
        0.0f,1.56f,1.0f,
        1.28f,0.41f,0.0f},

        {0.0f,-0.41f,1.28f,
        0.0f,1.56f,1.0f,
        -1.28f,0.41f,0.0f},


        {0.0f,1.56f,-1.0f,
        0.0f,-0.41f,-1.28f,
        -1.28,0.41f,0.0f},

        {0.0f,1.56f,-1.0f,
        0.0f,1.56f,1.0f,
        -1.28,0.41f,0.0f},

        {0.0f,1.56f,-1.0f,
        0.0f,1.56f,1.0f,
        1.28,0.41f,0.0f},

        {0.0f,1.56f,-1.0f,
        0.0f,-0.41f,-1.28f,
        1.28,0.41f,0.0f},

        {0.0f,-0.41f,-1.28f,
        -1.28f,0.41f,0.0f,
        -1.0f,-1.56f,0.0f},

        {0.0f,-0.41f,-1.28f,
        1.0f,-1.56f,0.0f,
        -1.0f,-1.56f,0.0f},

        {0.0f,-0.41f,-1.28f,
        1.0f,-1.56f,0.0f,
        1.28f,0.41f,0.0f},
        };
        color_t colors[4] = {COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_BRO};
    for(int i=0;i<12;i++){

        this->object[i] = create3DObject(GL_TRIANGLES, 1 * 3, vertex_buffer_data[i], colors[i%4], GL_FILL);
    }
}

void Disphenoid::draw(glm::mat4 VP)
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

void Disphenoid::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Disphenoid::tick()
{
    if(rotate_object){
        this->rotation += 1;
    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}

#include "main.h"
#include "timer.h"
#include "ball.h"
#include "hexagonal_dipyramid.h"
#include "square_pyramid.h"
#include "disphenoid.h"
#include "objects.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Hexagonal_dipyramid ball1;
Disphenoid ball2;
Square_Pyramid ball3;
int var_object_det = 1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

int rotate_camera = 0;
int rotate_object = 0;
// for translation of camera
float cam_x = 0, cam_y = 0, cam_z = 0;
float cam_x1 = 0, cam_y1 = 0, cam_z1 = 0;
float cam_speed = 0.1;
// speed of object translation
float object_speed = 0.1;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( cam_x + 5*cos(camera_rotation_angle*M_PI/180.0f), cam_y+ 0, cam_z + 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    glm::vec3 target (cam_x1, cam_y1, cam_z1);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(var_object_det == 0){
        ball1.draw(VP);
    }
    else if(var_object_det ==1){
        ball2.draw(VP);
    }
    else if(var_object_det==2){
        ball3.draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    // for object moving
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int n = glfwGetKey(window, GLFW_KEY_N);
    // for camera translation
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w  = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int z  = glfwGetKey(window, GLFW_KEY_Z);
    int x = glfwGetKey(window, GLFW_KEY_X);
    if (a) {
        // Do something
        // printf("a12");
        cam_z += cam_speed;
        cam_z1 += cam_speed;
    }
    if(d){
        // printf("11");
        cam_z -= cam_speed;
        cam_z1 -= cam_speed;
    }
    if(w){
        // printf("a10");
        cam_y += cam_speed;
        cam_y1 += cam_speed;
    }
    if(s){
        // printf("a9");
        cam_y -= cam_speed;
        cam_y1 -= cam_speed;
    }
    if(x){
        // printf("a8");
        cam_x -= cam_speed;
        cam_x1 -= cam_speed;
    }
    if(z){
        // printf("a7");
        cam_x += cam_speed;
        cam_x1 += cam_speed;
    }
    if(left){
        // printf("a6");
        ball1.position.z +=object_speed;
        ball2.position.z +=object_speed;
        ball3.position.z +=object_speed;
    }
    if(right){
        // printf("a5");
        ball1.position.z -= object_speed;
        ball2.position.z -= object_speed;
        ball3.position.z -= object_speed;
    }
    if(up){
        // printf("a4");
        ball1.position.y += object_speed;
        ball2.position.y += object_speed;
        ball3.position.y += object_speed;
    }
    if(down){
        // printf("a3");
        ball1.position.y -= object_speed;
        ball2.position.y -= object_speed;
        ball3.position.y -= object_speed;
    }
    if(m){
        // printf("a2");
        ball1.position.x += object_speed;
        ball2.position.x += object_speed;
        ball3.position.x += object_speed;
    }
    if(n){
        // printf("a1");
        ball1.position.x -= object_speed;
        ball2.position.x -= object_speed;
        ball3.position.x -= object_speed;
    }

}

void tick_elements() {
    ball1.tick();
    ball2.tick();
    ball3.tick();
    if(rotate_camera){
        ball1.position.x = 0;
        ball1.position.y = 0;
        ball1.position.z = 0;
        ball2.position.x = 0;
        ball2.position.y = 0;
        ball2.position.z = 0;
        ball3.position.x = 0;
        ball3.position.y = 0;
        ball3.position.z = 0;
        cam_x1 = 0;
        cam_y1 = 0;
        cam_z1 = 0;
        cam_x = 0;
        cam_z = 0;
        cam_y = 0;
        rotate_camera = 0;
        camera_rotation_angle += 1;
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Hexagonal_dipyramid(0, 0, COLOR_RED);
    ball2 = Disphenoid(0, 0, COLOR_RED);
    ball3 = Square_Pyramid(0, 0, COLOR_RED);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

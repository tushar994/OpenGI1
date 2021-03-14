#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "objects.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    case 'p':
        rotate_camera = (rotate_camera + 1)% 2;
        break;
    case 'j':
        rotate_object = (rotate_object + 1)% 2;
        break;
    case '1':
        cam_x = 3;
        cam_z = 3;
        cam_y = 3;
        camera_rotation_angle = 90;
        cam_x1 = ball1.position.x;
        cam_z1 = ball1.position.z;
        cam_y1 = ball1.position.y;
        break;
    case '2':
        cam_x = 5;
        cam_z = -4;
        cam_y = 3;
        camera_rotation_angle = 45;
        cam_x1 = ball1.position.x;
        cam_z1 = ball1.position.z;
        cam_y1 = ball1.position.y;
        break;
    case '3':
        cam_x = -3;
        cam_z = 2;
        cam_y = 7;
        camera_rotation_angle = 0;
        cam_x1 = ball1.position.x;
        cam_z1 = ball1.position.z;
        cam_y1 = ball1.position.y;
        break;
    case 's':
        draw1 = (draw1 + 1 )% 3;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            // Do something
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
}

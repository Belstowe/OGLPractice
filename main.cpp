#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "pngtexture.h"
#include "camera.h"
#include "ogl_obj/objpyramid.h"
#include "ogl_obj/objcube.h"

#define WIDTH 1280
#define HEIGHT 720

using namespace std;

bool keys[1024];
Camera camera;
int screenWidth, screenHeight;
GLfloat edgeProximityX = 0.0f, edgeProximityY = 0.0f;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void cameraControl(GLfloat deltaTime);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL 3D Scene", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    Shader myShader("shaders/standardShader.vrs", "shaders/standardShader.frs");

    PNGTexture containerText("textures/container.png");
    PNGTexture awesomeText("textures/awesome.png");
    PNGTexture reimuText("textures/reimu.png");
    PNGTexture marisaText("textures/marisa.png");
    PNGTexture fabricText("textures/fabric.png");
    PNGTexture transText("textures/transparent.png");
    PNGTexture floorText("textures/woodfloor.png");
    PNGTexture wallText("textures/woodwall.png");
    PNGTexture boxsideText("textures/boxside.png");
    PNGTexture boxtopText("textures/boxtop.png");

    vector<OGLObj *> objlist;
    // Комната
    objlist.push_back(new ObjCube(myShader.Program, glm::vec3(0.0f, 4.5f, 0.0f), &wallText, &wallText, &floorText, &transText, &transText, &transText, 10.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
    // Пирамидки с Рейму
    objlist.push_back(new ObjPyramid(myShader.Program, glm::vec3(-0.6f, 2.3f + 0.0003f, 1.0f), &fabricText, &reimuText, &transText, &transText, 0.75f, glm::vec3(1.0f, 7.0f, 35.0f)));
    objlist.push_back(new ObjPyramid(myShader.Program, glm::vec3(0.2f, 2.25f + 0.0003f, 1.3f), &fabricText, &reimuText, &transText, &transText, 0.5f, glm::vec3(0.0f, 20.0f, 0.0f)));
    objlist.push_back(new ObjPyramid(myShader.Program, glm::vec3(1.2f, 0.9f + 0.0002f, 2.0f), &fabricText, &marisaText, &transText, &transText, 0.8f, glm::vec3(0.0f, 90.0f, 0.0f)));
    // Ящики
    objlist.push_back(new ObjCube(myShader.Program, glm::vec3(0.0f, 0.25f + 0.0001f, 1.0f), &boxtopText, &boxsideText, &boxtopText, &transText, &transText, &transText, 1.5f, glm::vec3(0.0f, 30.0f, 0.0f)));
    objlist.push_back(new ObjCube(myShader.Program, glm::vec3(1.2f, 0.0f + 0.0001f, 2.0f), &boxtopText, &boxsideText, &boxtopText, &transText, &transText, &transText, 1.0f, glm::vec3(0.0f, 0.0f, 90.0f)));
    objlist.push_back(new ObjCube(myShader.Program, glm::vec3(0.05f, 1.5f + 0.0002f, 1.1f), &boxtopText, &boxsideText, &boxtopText, &transText, &transText, &transText, 1.0f, glm::vec3(0.0f, 15.0f, 0.0f)));
    objlist.push_back(new ObjCube(myShader.Program, glm::vec3(-0.8f, 0.1f + 0.0001f, -0.8f), &boxtopText, &boxsideText, &boxtopText, &transText, &transText, &transText, 1.2f, glm::vec3(0.0f, 20.0f, 0.0f)));
    objlist.push_back(new ObjCube(myShader.Program, glm::vec3(4.0f, 0.1f + 0.0001f, -4.1f), &boxtopText, &boxsideText, &boxtopText, &transText, &transText, &transText, 1.2f, glm::vec3(0.0f, -10.0f, 0.0f)));


    GLfloat timeValue = 0;
    GLfloat pastFrameTimeValue = 0;
    GLfloat deltaTime = timeValue - pastFrameTimeValue;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        cameraControl(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glm::mat4 projection = glm::perspective(camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.view();
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        for (GLuint i = 0; i < objlist.size(); i++)
            objlist[i]->draw();

        glfwSwapBuffers(window);
        pastFrameTimeValue = timeValue;
        timeValue = glfwGetTime();
        deltaTime = timeValue - pastFrameTimeValue;
    }

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        glfwSetWindowShouldClose(window, GL_TRUE);
    if ((key == GLFW_KEY_RIGHT_CONTROL) && (action == GLFW_PRESS)) {
        cout << camera.pos.x << " " << camera.pos.y << " " << camera.pos.z << endl;
        cout << camera.front.x << " " << camera.front.y << " " << camera.front.z << endl;
        cout << camera.up.x << " " << camera.up.y << " " << camera.up.z << endl;
        cout << camera.yaw << " " << camera.pitch << endl;
    }

    if ((key >= 0) && (key < 1024)) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void cameraControl(GLfloat deltaTime) {
    if (keys[GLFW_KEY_W])
        camera.move(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.move(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.move(LEFTWARD, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.move(RIGHTWARD, deltaTime);
    if (keys[GLFW_KEY_Q])
        camera.move(LEFTTURN, deltaTime);
    if (keys[GLFW_KEY_E])
        camera.move(RIGHTTURN, deltaTime);
    if (keys[GLFW_KEY_R])
        camera.move(UPTURN, deltaTime);
    if (keys[GLFW_KEY_F])
        camera.move(DOWNTURN, deltaTime);
    if (keys[GLFW_KEY_I])
        camera.move(ZOOMIN, deltaTime);
    if (keys[GLFW_KEY_K])
        camera.move(ZOOMOUT, deltaTime);

    if ((abs(edgeProximityX) > 1e-6) || (abs(edgeProximityY) > 1e-6))
        camera.controlms(30.0f * edgeProximityX * deltaTime, 30.0f * edgeProximityY * deltaTime, true);
}

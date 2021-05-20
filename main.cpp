#include <iostream>
#include <cmath>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "pngtexture.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

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

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "More Containers in 3D!", NULL, NULL);
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

    GLfloat verticles[] = {
        // Позиции              // Текстурные координаты
        -0.5f,  -0.5f,  -0.5f,  1.0f,   0.0f, // Задняя сторона
        0.5f,   -0.5f,  -0.5f,  0.0f,   0.0f,
        0.5f,   0.5f,   -0.5f,  0.0f,   1.0f,
        0.5f,   0.5f,   -0.5f,  0.0f,   1.0f,
        -0.5f,  0.5f,   -0.5f,  1.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  1.0f,   0.0f,

        -0.5f,  -0.5f,  0.5f,   0.0f,   0.0f, // Передняя сторона
        0.5f,   -0.5f,  0.5f,   1.0f,   0.0f,
        0.5f,   0.5f,   0.5f,   1.0f,   1.0f,
        0.5f,   0.5f,   0.5f,   1.0f,   1.0f,
        -0.5f,  0.5f,   0.5f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   0.0f,

        -0.5f,  0.5f,   0.5f,   1.0f,   1.0f, // Левая сторона
        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,
        -0.5f,  -0.5f,  0.5f,   1.0f,   0.0f,
        -0.5f,  0.5f,   0.5f,   1.0f,   1.0f,

        0.5f,   0.5f,   0.5f,   0.0f,   1.0f, // Правая сторона
        0.5f,   0.5f,   -0.5f,  1.0f,   1.0f,
        0.5f,   -0.5f,  -0.5f,  1.0f,   0.0f,
        0.5f,   -0.5f,  -0.5f,  1.0f,   0.0f,
        0.5f,   -0.5f,  0.5f,   0.0f,   0.0f,
        0.5f,   0.5f,   0.5f,   0.0f,   1.0f,

        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f, // Нижняя сторона
        0.5f,   -0.5f,  -0.5f,  1.0f,   0.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   1.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   1.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,

        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f, // Верхняя сторона
        0.5f,   0.5f,   -0.5f,  1.0f,   1.0f,
        0.5f,   0.5f,    0.5f,  1.0f,   0.0f,
        0.5f,   0.5f,    0.5f,  1.0f,   0.0f,
        -0.5f,  0.5f,    0.5f,  0.0f,   0.0f,
        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f
    };
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,    0.0f,   0.0f),
        glm::vec3( 2.0f,    5.0f,   -15.0f),
        glm::vec3(-1.5f,    -2.2f,  -2.5f),
        glm::vec3(-3.8f,    -2.0f,  -12.3f),
        glm::vec3( 2.4f,    -0.4f,  -3.5f),
        glm::vec3(-1.7f,    3.0f,   -7.5f),
        glm::vec3( 1.3f,    -2.0f,  -2.5f),
        glm::vec3( 1.5f,    2.0f,   -2.5f),
        glm::vec3( 1.5f,    0.2f,   -1.5f),
        glm::vec3(-1.3f,    1.0f,   -1.5f)
    };
    Shader myShader("shaders/myShader.vrs", "shaders/myShader.frs");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    PNGTexture containerText("textures/container.png");
    PNGTexture awesomeText("textures/awesome.png");



    GLfloat timeValue = 0;
    GLfloat pastFrameTimeValue = 0;
    GLfloat deltaTime = timeValue - pastFrameTimeValue;
    const glm::mat4 unitmat(1.0f);
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

        glActiveTexture(GL_TEXTURE0);
        containerText.bind();
        glUniform1i(glGetUniformLocation(myShader.Program, "baseTexture"), 0);
        glActiveTexture(GL_TEXTURE1);
        awesomeText.bind();
        glUniform1i(glGetUniformLocation(myShader.Program, "overlayTexture"), 1);

        glBindVertexArray(VAO);
        glm::mat4 projection = glm::perspective(camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.view();
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        for (GLuint i = 0; i < (sizeof(cubePositions) / sizeof(glm::vec3)); i++) {
            glm::mat4 model = glm::translate(unitmat, cubePositions[i]);
            model = glm::rotate(model, glm::radians(25.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::rotate(model, glm::radians(timeValue * 20.0f * i), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        pastFrameTimeValue = timeValue;
        timeValue = glfwGetTime();
        deltaTime = timeValue - pastFrameTimeValue;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        glfwSetWindowShouldClose(window, GL_TRUE);
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

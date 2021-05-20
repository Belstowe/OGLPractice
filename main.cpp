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

#define WIDTH 800
#define HEIGHT 600

using namespace std;

GLfloat x_pos = 0.0f;
GLfloat z_pos = -3.0f;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if ((key == GLFW_KEY_W) && (action == GLFW_PRESS))
        z_pos += 1.0f;
    else if ((key == GLFW_KEY_S) && (action == GLFW_PRESS))
        z_pos -= 1.0f;
    else if ((key == GLFW_KEY_A) && (action == GLFW_PRESS))
        x_pos += 1.0f;
    else if ((key == GLFW_KEY_D) && (action == GLFW_PRESS))
        x_pos -= 1.0f;
}

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

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    GLfloat verticles[] = {
        // Позиции              // Текстурные координаты
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,
        0.5f,   -0.5f,  -0.5f,  1.0f,   0.0f,
        0.5f,   0.5f,   -0.5f,  1.0f,   1.0f,
        0.5f,   0.5f,   -0.5f,  1.0f,   1.0f,
        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,

        -0.5f,  -0.5f,  0.5f,   0.0f,   0.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   0.0f,
        0.5f,   0.5f,   0.5f,   1.0f,   1.0f,
        0.5f,   0.5f,   0.5f,   1.0f,   1.0f,
        -0.5f,  0.5f,   0.5f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   0.0f,

        -0.5f,  0.5f,   0.5f,   1.0f,   0.0f,
        -0.5f,  0.5f,   -0.5f,  1.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   1.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   0.0f,
        -0.5f,  0.5f,   0.5f,   1.0f,   0.0f,

        0.5f,   0.5f,   0.5f,   1.0f,   0.0f,
        0.5f,   0.5f,   -0.5f,  1.0f,   1.0f,
        0.5f,   -0.5f,  -0.5f,  0.0f,   1.0f,
        0.5f,   -0.5f,  -0.5f,  0.0f,   1.0f,
        0.5f,   -0.5f,  0.5f,   0.0f,   0.0f,
        0.5f,   0.5f,   0.5f,   1.0f,   0.0f,

        -0.5f,  -0.5f,  -0.5f,  0.0f,   1.0f,
        0.5f,   -0.5f,  -0.5f,  1.0f,   1.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   0.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   0.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   0.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   1.0f,

        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f,
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
    /*
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    */
    Shader myShader("shaders/myShader.vrs", "shaders/myShader.frs");

    GLuint VBO, VAO;
    //GLuint EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    PNGTexture containerText("textures/container.png");
    PNGTexture awesomeText("textures/awesome.png");



    GLfloat timeValue = 0;
    //GLfloat pastFrameTimeValue = 0;
    //GLfloat speedCoef = 60 * (timeValue - pastFrameTimeValue);
    const glm::mat4 unitmat(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glActiveTexture(GL_TEXTURE0);
        containerText.bind();
        glUniform1i(glGetUniformLocation(myShader.Program, "myTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        awesomeText.bind();
        glUniform1i(glGetUniformLocation(myShader.Program, "myTexture2"), 1);

        glBindVertexArray(VAO);
        glm::mat4 view = glm::translate(unitmat, glm::vec3(x_pos, 0.0f, z_pos));
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
        //pastFrameTimeValue = timeValue;
        timeValue = glfwGetTime();
        //speedCoef = 60 * (timeValue - pastFrameTimeValue);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

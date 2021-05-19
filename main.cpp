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

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "But More Containers!", NULL, NULL);
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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLfloat verticles[] = {
        // Позиции              // Цвета                // Координаты текстуры
        0.5f,   0.5f,   0.0f,   1.0f,   0.0f,   0.0f,   1.0f,   1.0f,   // Правый верхний
        0.5f,   -0.5f,  0.0f,   0.0f,   1.0f,   0.0f,   1.0f,   0.0f,   // Правый нижний
        -0.5f,  -0.5f,  0.0f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f,   // Левый нижний
        -0.5f,  0.5f,   0.0f,   1.0f,   1.0f,   0.0f,   0.0f,   1.0f    // Левый верхний
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    Shader myShader("shaders/myShader.vrs", "shaders/myShader.frs");

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    PNGTexture containerText("textures/container.png");
    PNGTexture awesomeText("textures/awesome.png");

    /*
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    */

    GLfloat timeValue = 0;
    /*
    GLfloat pastFrameTimeValue = 0;
    GLfloat speedCoef = 60 * (timeValue - pastFrameTimeValue);
    */
    glm::mat4 trans;
    GLfloat satValue, scaleFactor;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();

        glActiveTexture(GL_TEXTURE0);
        containerText.bind();
        glUniform1i(glGetUniformLocation(myShader.Program, "myTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        awesomeText.bind();
        glUniform1i(glGetUniformLocation(myShader.Program, "myTexture2"), 1);

        glBindVertexArray(VAO);

        satValue = (sin(timeValue) / 2) + 0.5;
        scaleFactor = 0.5f;
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, glm::radians(timeValue) * 100.0f, glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
        //trans = glm::rotate(trans, glm::radians(speedCoef), glm::vec3(0.0, 0.0, 1.0));
        glUniform1f(glGetUniformLocation(myShader.Program, "mySaturation"), satValue);
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        satValue = 0.0;
        scaleFactor = (sin(2 * timeValue) / 4) + 0.5;
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::scale(trans, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
        glUniform1f(glGetUniformLocation(myShader.Program, "mySaturation"), satValue);
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        //pastFrameTimeValue = timeValue;
        timeValue = glfwGetTime();
        //speedCoef = 60 * (timeValue - pastFrameTimeValue);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

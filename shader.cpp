#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
    // Получаем исходный код шейдера по переданным путям
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    // Удостоверимся, что ifstream объекты могут выкидывать исключения
    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);

    try {
        // Открываем файлы
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        // Считываем данные в потоки
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();
        // Преобразовываем потоки в строки
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    // Преобразовываем строки в GLchar
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    // Сборка шейдеров
    GLuint vertex, fragment;
    GLint success;
    GLchar infolog[512];

    // Вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl << infolog << endl;
    }

    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infolog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << endl << infolog << endl;
    }

    // Шейдерная программа
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, infolog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl << infolog << endl;
    }

    // Удаляем шейдеры, поскольку мы встроили их в программу
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(this->Program);
}

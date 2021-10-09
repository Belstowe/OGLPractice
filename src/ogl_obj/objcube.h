#ifndef OBJCUBE_H
#define OBJCUBE_H

#include "oglobj.h"

class ObjCube : public OGLObj {
public:
    PNGTexture *baseTextureTop;
    PNGTexture *baseTextureSide;
    PNGTexture *baseTextureBtm;
    PNGTexture *overlayTextureTop;
    PNGTexture *overlayTextureSide;
    PNGTexture *overlayTextureBtm;
    ObjCube(GLuint program, glm::vec3 pos,
            PNGTexture *baseTextureTop, PNGTexture *baseTextureSide, PNGTexture *baseTextureBtm,
            PNGTexture *overlayTextureTop, PNGTexture *overlayTextureSide, PNGTexture *overlayTextureBtm,
            GLfloat sizefactor, glm::vec3 rotation);
    ~ObjCube();
    virtual void draw();

private:
    GLuint topVBO, topVAO, sideVBO, sideVAO, bottomVBO, bottomVAO;
    GLfloat topVerticles[30] = {
        // Позиции              // Текстурные координаты
        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f, // Верхняя сторона
        0.5f,   0.5f,   -0.5f,  1.0f,   1.0f,
        0.5f,   0.5f,    0.5f,  1.0f,   0.0f,
        0.5f,   0.5f,    0.5f,  1.0f,   0.0f,
        -0.5f,  0.5f,    0.5f,  0.0f,   0.0f,
        -0.5f,  0.5f,   -0.5f,  0.0f,   1.0f
    };
    GLfloat bottomVerticles[30] = {
        // Позиции              // Текстурные координаты
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f, // Нижняя сторона
        0.5f,   -0.5f,  -0.5f,  1.0f,   0.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   1.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   1.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f
    };
    GLfloat sideVerticles[120] = {
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
        0.5f,   0.5f,   0.5f,   0.0f,   1.0f
    };
};

#endif // OBJCUBE_H

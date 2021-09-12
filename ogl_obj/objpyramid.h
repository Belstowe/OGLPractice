#ifndef OBJPYRAMID_H
#define OBJPYRAMID_H

#include "oglobj.h"

class ObjPyramid: public OGLObj {
public:
    PNGTexture *baseTexture;
    PNGTexture *overlayTextureFront;
    PNGTexture *overlayTextureBack;
    PNGTexture *overlayTextureBtm;
    ObjPyramid(GLuint program, glm::vec3 pos, PNGTexture *baseTexture, PNGTexture *overlayTextureFront, PNGTexture *overlayTextureBack, PNGTexture *overlayTextureBtm, GLfloat sizefactor, glm::vec3 rotation);
    ~ObjPyramid();
    virtual void draw();

private:
    GLuint frontVBO, frontVAO, backVBO, backVAO, bottomVBO, bottomVAO;
    GLfloat frontVerticles[30] = {
        // Позиции              // Текстурные координаты
        -0.5f,  -0.5f,  -0.5f,  1.0f,   0.0f,
        -0.5f,  -0.5f,  0.5f,   0.5f,   0.0f,
        0.0f,   0.5f,   0.0f,   0.5f,   1.0f,

        -0.5f,  -0.5f,  0.5f,   0.5f,   0.0f,
        0.5f,   -0.5f,  0.5f,   0.0f,   0.0f,
        0.0f,   0.5f,   0.0f,   0.5f,   1.0f
    };
    GLfloat backVerticles[30] = {
        // Позиции              // Текстурные координаты
        0.5f,   -0.5f,  0.5f,   0.0f,   0.0f,
        0.5f,   -0.5f,  -0.5f,  0.5f,   0.0f,
        0.0f,   0.5f,   0.0f,   0.5f,   1.0f,

        0.5f,   -0.5f,  -0.5f,  0.5f,   0.0f,
        -0.5f,   -0.5f,  -0.5f, 1.0f,   0.0f,
        0.0f,   0.5f,   0.0f,   0.5f,   1.0f
    };
    GLfloat bottomVerticles[30] = {
        // Позиции              // Текстурные координаты
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f,
        0.5f,   -0.5f,  -0.5f,  1.0f,   0.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   1.0f,
        0.5f,   -0.5f,  0.5f,   1.0f,   1.0f,
        -0.5f,  -0.5f,  0.5f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  -0.5f,  0.0f,   0.0f
    };
};

#endif // OBJPYRAMID_H

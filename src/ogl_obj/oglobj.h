#ifndef OGLOBJ_H
#define OGLOBJ_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../pngtexture.h"

class OGLObj
{
public:
    OGLObj(GLuint program, glm::vec3 pos, GLfloat sizefactor, glm::vec3 rotation);
    GLuint program;
    glm::vec3 pos;
    GLfloat sizefactor;
    glm::vec3 rotation;
    virtual void draw() = 0;

protected:
    void initVertexArrays(GLuint *VAO, GLuint *VBO, GLfloat *verticles, GLuint verticlesNum);
    void drawVertexArrays(GLuint VAO, PNGTexture *baseTexture, PNGTexture *overlayTexture, GLuint verticlesNum);
    void freeVertexArrays(GLuint *VAO, GLuint *VBO);
};

#endif // OGLOBJ_H

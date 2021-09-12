#include "objpyramid.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ObjPyramid::ObjPyramid(GLuint program, glm::vec3 pos, PNGTexture *baseTexture, PNGTexture *overlayTextureFront, PNGTexture *overlayTextureBack, PNGTexture *overlayTextureBtm, GLfloat sizefactor = 1.0f, glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f))
    : OGLObj(program, pos, sizefactor, rotation) {
    this->baseTexture = baseTexture;
    this->overlayTextureFront = overlayTextureFront;
    this->overlayTextureBack = overlayTextureBack;
    this->overlayTextureBtm = overlayTextureBtm;

    initVertexArrays(&frontVAO, &frontVBO, frontVerticles, 2);
    initVertexArrays(&backVAO, &backVBO, backVerticles, 2);
    initVertexArrays(&bottomVAO, &bottomVBO, bottomVerticles, 2);
}

ObjPyramid::~ObjPyramid() {
    freeVertexArrays(&backVAO, &backVBO);
    freeVertexArrays(&frontVAO, &frontVBO);
    freeVertexArrays(&bottomVAO, &bottomVBO);
}

void ObjPyramid::draw() {
    drawVertexArrays(frontVAO, baseTexture, overlayTextureFront, 2);
    drawVertexArrays(backVAO, baseTexture, overlayTextureBack, 2);
    drawVertexArrays(bottomVAO, baseTexture, overlayTextureBtm, 2);
}

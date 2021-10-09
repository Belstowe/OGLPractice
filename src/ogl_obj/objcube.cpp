#include "objcube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ObjCube::ObjCube(GLuint program, glm::vec3 pos, PNGTexture *baseTextureTop,
                 PNGTexture *baseTextureSide, PNGTexture *baseTextureBtm,
                 PNGTexture *overlayTextureTop, PNGTexture *overlayTextureSide,
                 PNGTexture *overlayTextureBtm, GLfloat sizefactor = 1.0f,
                 glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f))
    : OGLObj(program, pos, sizefactor, rotation) {
  this->baseTextureTop = baseTextureTop;
  this->baseTextureSide = baseTextureSide;
  this->baseTextureBtm = baseTextureBtm;
  this->overlayTextureTop = overlayTextureTop;
  this->overlayTextureSide = overlayTextureSide;
  this->overlayTextureBtm = overlayTextureBtm;

  initVertexArrays(&topVAO, &topVBO, topVerticles, 2);
  initVertexArrays(&sideVAO, &sideVBO, sideVerticles, 8);
  initVertexArrays(&bottomVAO, &bottomVBO, bottomVerticles, 2);
}

ObjCube::~ObjCube() {
  freeVertexArrays(&topVAO, &topVBO);
  freeVertexArrays(&sideVAO, &sideVBO);
  freeVertexArrays(&bottomVAO, &bottomVBO);
}

void ObjCube::draw() {
  drawVertexArrays(topVAO, baseTextureTop, overlayTextureTop, 2);
  drawVertexArrays(sideVAO, baseTextureSide, overlayTextureSide, 8);
  drawVertexArrays(bottomVAO, baseTextureBtm, overlayTextureBtm, 2);
}

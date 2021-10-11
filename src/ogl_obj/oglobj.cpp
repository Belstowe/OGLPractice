#include "oglobj.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OGLObj::OGLObj(GLuint program, glm::vec3 pos, GLfloat sizefactor,
               glm::vec3 rotation)
    : program(program), pos(pos), sizefactor(sizefactor), rotation(rotation) {}

void OGLObj::initVertexArrays(GLuint *VAO, GLuint *VBO, GLfloat *verticles,
                              GLuint verticlesNum) {
  glGenVertexArrays(1, VAO);
  glGenBuffers(1, VBO);
  glBindVertexArray(*VAO);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, 15 * verticlesNum * sizeof(GLfloat), verticles,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void OGLObj::freeVertexArrays(GLuint *VAO, GLuint *VBO) {
  glDeleteVertexArrays(1, VAO);
  glDeleteBuffers(1, VBO);
}

void OGLObj::drawVertexArrays(GLuint VAO, PNGTexture *baseTexture,
                              PNGTexture *overlayTexture, GLuint verticlesNum) {
  glm::mat4 model(1.0f);

  glActiveTexture(GL_TEXTURE0);
  baseTexture->bind();
  glUniform1i(glGetUniformLocation(program, "baseTexture"), 0);
  glActiveTexture(GL_TEXTURE1);
  overlayTexture->bind();
  glUniform1i(glGetUniformLocation(program, "overlayTexture"), 1);

  glBindVertexArray(VAO);
  model = glm::translate(model, pos);
  model =
      glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  model =
      glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  model =
      glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(sizefactor, sizefactor, sizefactor));
  glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE,
                     glm::value_ptr(model));
  glDrawArrays(GL_TRIANGLES, 0, 3 * verticlesNum);
  glBindVertexArray(0);
}

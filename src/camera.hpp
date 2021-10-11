#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>

enum __camera_movement {
  FORWARD,
  BACKWARD,
  LEFTWARD,
  RIGHTWARD,
  LEFTTURN,
  RIGHTTURN,
  UPTURN,
  DOWNTURN,
  ZOOMIN,
  ZOOMOUT
};

class Camera {
public:
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
  GLfloat yaw;
  GLfloat pitch;
  GLfloat speed;
  GLfloat mouseSensitivity;
  GLfloat zoom;

  Camera();
  glm::mat4 view();
  void move(__camera_movement direction, GLfloat deltatime);
  void controlms(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);
  void controlscr(GLfloat yoffset);

private:
  void updateVectors();
};

#endif // CAMERA_H

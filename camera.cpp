#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : pos(glm::vec3(0.0f, 0.0f, 3.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      yaw(-90.0f), pitch(0.0f), speed(3.0f), mouseSensitivity(0.25f), zoom(45.0f)
{
    this->updateVectors();
}

glm::mat4 Camera::view() {
    return glm::lookAt(this->pos, this->pos + this->front, this->up);
}

void Camera::move(__camera_movement direction, GLfloat deltatime) {
    switch (direction) {
        case FORWARD: this->pos += this->front * this->speed * deltatime; break;
        case BACKWARD: this->pos -= this->front * this->speed * deltatime; break;
        case LEFTWARD: this->pos -= this->right * this->speed * deltatime; break;
        case RIGHTWARD: this->pos += this->right * this->speed * deltatime; break;

        case UPTURN:
            this->pitch += 30.0f * this->speed * deltatime;
            this->pitch = (this->pitch > 89.0f)     ? 89.0f     : this->pitch;
            this->updateVectors();
            break;
        case DOWNTURN:
            this->pitch -= 30.0f * this->speed * deltatime;
            this->pitch = (this->pitch < -89.0f)    ? -89.0f    : this->pitch;
            this->updateVectors();
            break;
        case LEFTTURN: this->yaw -= 30.0f * this->speed * deltatime; this->updateVectors(); break;
        case RIGHTTURN: this->yaw += 30.0f * this->speed * deltatime; this->updateVectors(); break;

        case ZOOMIN:
            this->zoom -= deltatime;
            this->zoom = (this->zoom < 44.2f) ? 44.2f : this->zoom;
            break;
        case ZOOMOUT:
            this->zoom += deltatime;
            this->zoom = (this->zoom > 45.0f) ? 45.0f : this->zoom;
            break;
    }
}

void Camera::controlms(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
    xoffset *= this->mouseSensitivity;
    yoffset *= this->mouseSensitivity;

    this->yaw += xoffset;
    this->pitch += yoffset;

    if (constrainPitch) {
        this->pitch = (this->pitch < -89.0f)    ? -89.0f    : this->pitch;
        this->pitch = (this->pitch > 89.0f)     ? 89.0f     : this->pitch;
    }

    this->updateVectors();
}

void Camera::controlscr(GLfloat yoffset) {
    this->zoom -= yoffset;
    this->zoom = (this->zoom < 44.2f)   ? 44.2f  : this->zoom;
    this->zoom = (this->zoom > 45.0f)   ? 45.0f : this->zoom;
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}



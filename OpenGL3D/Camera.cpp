#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec3 clearColor) {
	this->pos = position;
	this->up = up;
	this->lookAt = lookAt;
	this->clearColor = clearColor;
	rot = glm::vec3(0);
	
	prepare();
}

Camera::~Camera() {

}

void Camera::move(float timeStep) {
	if (State::keybEvent[GLFW_KEY_W])
		pos += forward * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_S])
		pos -= forward * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_A])
		pos -= glm::normalize(glm::cross(forward, up)) * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_D])
		pos += glm::normalize(glm::cross(forward, up)) * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_E])
		pos += up * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_Q]) 
		pos -= up * timeStep * speed;
	
	glm::vec3 direction(0);

	direction.x = cos(glm::radians(State::xRoll)) * cos(glm::radians(State::yRoll)) * timeStep;
	direction.y = -sin(glm::radians(State::yRoll)) * timeStep;
	direction.z = sin(glm::radians(State::xRoll)) * cos(glm::radians(State::yRoll)) * timeStep;
	forward = glm::normalize(direction);
}

void Camera::prepare() {
	modelMtx = glm::lookAt(pos, lookAt, up);

	State::viewMatrix = modelMtx;
	State::projectionMatrix = projection;
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

void Camera::step(float timeStep) {
	move(timeStep);
	modelMtx = glm::lookAt(pos, pos + forward, up);
	State::viewMatrix = modelMtx;
	State::projectionMatrix = projection;
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

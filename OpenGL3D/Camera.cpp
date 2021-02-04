#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec3 clearColor) {
	this->pos = position;
	this->up = up;
	this->lookAt = lookAt;
	this->clearColor = clearColor;
	rot = glm::vec3(0);
}

Camera::~Camera() {

}

void Camera::move(float timeStep) {
	glm::vec3 right = glm::normalize(glm::cross(lookAt, up));
	glm::vec3 newUp = glm::normalize(glm::cross(lookAt, right));

	if (State::keybEvent[GLFW_KEY_W])
		pos += lookAt * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_S])
		pos -= lookAt * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_A])
		pos -= right * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_D])
		pos += right * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_E])
		pos -= newUp * timeStep * speed;
	if (State::keybEvent[GLFW_KEY_Q]) 
		pos += newUp * timeStep * speed;
	
	glm::vec3 direction(0);

	direction.x = cos(glm::radians(State::xRoll)) * cos(glm::radians(State::yRoll)) * timeStep;
	direction.y = -sin(glm::radians(State::yRoll)) * timeStep;
	direction.z = sin(glm::radians(State::xRoll)) * cos(glm::radians(State::yRoll)) * timeStep;
	lookAt = glm::normalize(direction);
}

void Camera::prepare() {
	modelMtx = glm::lookAt(pos, pos + lookAt, up);

	State::viewMatrix = modelMtx;
	State::projectionMatrix = projection;
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

void Camera::step(float timeStep) {
	move(timeStep);
	prepare();
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

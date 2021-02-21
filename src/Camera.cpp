#include "Camera.hpp"

Camera::Camera(glm::vec4 position, glm::vec3 up, glm::vec3 lookAt, glm::vec3 clearColor, glm::mat4 projection) {
	this->pos = position;
	this->up = up;
	this->lookAt = lookAt;
	this->clearColor = clearColor;
	this->projection = projection;
	rot = glm::vec4(0);
}

Camera::~Camera() {

}

void Camera::move(float timeStep) {
	glm::vec3 right = glm::normalize(glm::cross(lookAt, up));
	glm::vec3 newUp = glm::normalize(glm::cross(lookAt, right));

	rot.x += (Input::rightAxisX + Input::mouseX) * speed;
	rot.y += (Input::rightAxisY + Input::mouseY) * speed;


	if (rot.x >= 360.0f)
		rot.x = 0;

	if (rot.y > 89.f)
		rot.y = 89.f;
	if (rot.y < -89.f)
		rot.y = -89.f;
	
	
	glm::vec3 targetPos = (lookAt * Input::leftAxisY + right * Input::leftAxisX) * timeStep * speed;

	pos.x += targetPos.x;
	pos.y += targetPos.y;
	pos.z += targetPos.z;

	/*if (Input::keybEvent[GLFW_KEY_E])
		pos -= newUp * timeStep * speed;
	if (Input::keybEvent[GLFW_KEY_Q]) 
		pos += newUp * timeStep * speed;*/
	
	glm::vec3 direction(0);

	direction.x = cos(glm::radians(rot.x)) * cos(glm::radians(rot.y));
	direction.y = -sin(glm::radians(rot.y));
	direction.z = sin(glm::radians(rot.x)) * cos(glm::radians(rot.y));
	lookAt = glm::normalize(direction);
}

void Camera::prepare() {
	glm::vec3 position = glm::vec3(pos.x, pos.y, pos.z);
	modelMtx = glm::lookAt(position, position + lookAt, up);

	State::viewMatrix = modelMtx;
	State::projectionMatrix = projection;
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

void Camera::step(float timeStep) {
	move(timeStep);
	prepare();
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

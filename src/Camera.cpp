#include "Camera.hpp"

Camera::Camera() : Entity() {
	this->clearColor = glm::vec3();
	this->upView = this->up;
	this->projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

Camera::Camera(glm::vec4 position, glm::vec3 up, glm::vec3 forward, glm::vec3 clearColor, glm::mat4 projection, glm::vec3 upView) {
	this->pos = position;
	this->up = up;
	this->upView = upView;
	this->forward = forward;
	this->clearColor = clearColor;
	this->projection = projection;
	rot = glm::vec4(0);
}

Camera::~Camera() {

}

void Camera::move(float timeStep) {
	//glm::vec3 newUp = glm::normalize(glm::cross(forward, right));

	rot.x += (Input::rightAxisX + Input::mouseX) * speed;
	rot.y += (Input::rightAxisY + Input::mouseY) * speed;

	if (rot.x >= 360.0f)
		rot.x = 0;

	if (rot.y > 89.f)
		rot.y = 89.f;
	if (rot.y < -89.f)
		rot.y = -89.f;
	
	
	glm::vec3 targetPos = (forward * Input::leftAxisY + right * Input::leftAxisX) * timeStep * speed;

	pos.x += targetPos.x;
	pos.y += targetPos.y;
	pos.z += targetPos.z;

	/*if (Input::keybEvent[GLFW_KEY_E])
		pos -= newUp * timeStep * speed;
	if (Input::keybEvent[GLFW_KEY_Q]) 
		pos += newUp * timeStep * speed;*/
}

void Camera::prepare() {
	glm::vec3 position = glm::vec3(pos.x, pos.y, pos.z);
	modelMtx = glm::lookAt(position, position + forward, upView);

	State::viewMatrix = modelMtx;
	State::projectionMatrix = projection;
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

void Camera::setUpView(const glm::vec3 upView) { this->upView = upView; }
const glm::vec3& Camera::getUpView() const { return upView; }

void Camera::step(float timeStep) {
	right = glm::normalize(glm::cross(forward, upView));
	up = glm::normalize(glm::cross(forward, right));

	forward = normalize(Math::eulerToDirection(rot));

	move(timeStep);
	prepare();
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
}

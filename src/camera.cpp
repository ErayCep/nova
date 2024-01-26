#include "camera.h"

glm::mat4 Camera::get_view_matrix() {
	return glm::lookAt(position, position + front, up);
}


void Camera::handle_keyboard(camera_movement direction, float delta_time) {
	float velocity = MovementSpeed * delta_time;
	if (direction == FORWARD) {
		position += front * velocity;
	}	
	if (direction == BACKWARD) {
		position -= front * velocity;
	}	
	if (direction == LEFT) {
		position -= right * velocity;
	}
	if (direction == RIGHT) {
		position += right * velocity;
	}
}


void Camera::handle_mouse(float x_offset, float y_offset, GLboolean constrain_pitch) {
	x_offset *= MouseSensitivity;
	y_offset *= MouseSensitivity;

	Yaw += x_offset;
	Pitch += y_offset;

	if (constrain_pitch) {
		if (Pitch > 89.0f) {
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f) {
			Pitch = -89.0f;
		}
	}

	update_camera_vectors();
}


void Camera::update_camera_vectors() {
	glm::vec3 _front;
	_front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	_front.y = sin(glm::radians(Pitch));
	_front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(_front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

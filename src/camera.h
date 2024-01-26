#ifndef CAMERA_H
#define CAMERA_H

#include "gfx.h"
#include "utils.h"

enum camera_movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class Camera {
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	float Yaw;
	float Pitch;
	float Fov;

	float MovementSpeed;
	float MouseSensitivity;

	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : front(0.0f, 0.0f, -1.0f), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV) {
		position = _position;
		world_up = _up;
		Yaw = yaw;
		Pitch = pitch;
		update_camera_vectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV) {
		position = glm::vec3(posX, posY, posZ);
		world_up = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		update_camera_vectors();
	}

	glm::mat4 get_view_matrix();

	void handle_keyboard(camera_movement direction, float delta_time);
	void handle_mouse(float x_offset, float y_offset, GLboolean constrain_pitch = true);

private:
	void update_camera_vectors();
};


#endif

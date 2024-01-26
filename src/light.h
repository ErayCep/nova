#ifndef LIGHT_H
#define LIGHT_H

#include "utils.h"
#include "gfx.h"

#include "shader.h"
#include "camera.h"

class Light {
public:
	Light();

	void draw(Shader &shader, Camera &camera);

	glm::vec3 lightPos;
	glm::vec3 getLightPos();
private:
	unsigned int VAO, VBO;
	glm::mat4 model, view, projection;	
};

#endif

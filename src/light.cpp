#include "light.h"

#include "types.h"

Light::Light() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	lightPos = glm::vec3(1.2f, 0.0f, 2.0f);
}

void Light::draw(Shader &shader, Camera &camera) {
	lightPos.x = sin(glfwGetTime()) * 15.0f;
	lightPos.y = cos(glfwGetTime()) * 15.0f;
				
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


glm::vec3 Light::getLightPos() {
	return lightPos;
}

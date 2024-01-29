#ifndef INSTANCE_H
#define INSTANCE_H

#include "gfx.h"
#include "model.h"
#include "shader.h"

class Instance {
public:
	Instance(Model &model, Model &planet, Shader &shader, Shader &instanceShader);

	void Draw();

	glm::mat4 *modelMatrices;
	unsigned int amount = 10000;
	unsigned int VBO;
private:
	Model &pModel;
	Model &pPlanet;
	Shader &pShader;
	Shader &pInstanceShader;
};

#endif

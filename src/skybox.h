#ifndef SKYBOX_H
#define SKYBOX_H

#pragma once

#include "utils.h"
#include "gfx.h"

class Skybox {
public:
	Skybox();

	void loadCubeMap(std::vector<std::string> faces);
	void Draw();

	unsigned int textureID;
	unsigned int VAO, VBO;
private:
};

#endif

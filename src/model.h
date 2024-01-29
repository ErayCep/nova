#ifndef MODEL_H
#define MODEL_H

#include "shader.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	Model(std::string const &path, bool gamma);
	void Draw(Shader &shader);

	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;


private:
	bool gammaCorrection;
	std::string directory;

	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif

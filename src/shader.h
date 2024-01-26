#ifndef SHADER_H
#define SHADER_H

#include "gfx.h"
#include "utils.h"


class Shader {
public:
	unsigned int ID;

	Shader(const char* vs_path, const char* fs_path);

	void use();
	
	void set_bool(const std::string &name, bool value);
	void set_float(const std::string &name, float value);
	void set_int(const std::string &name, int value);
	void set_mat4(const std::string &name, glm::mat4 value);
	void set_vec3(const std::string &name, glm::vec3 value);
	void set_vec3(const std::string &name, float x, float y, float z);
private:
	void check_compile_errors(GLuint shader, std::string type);
	unsigned int get_location(const std::string name);
};

#endif

#include "shader.h"

Shader::Shader(const char* vs_path, const char* fs_path) {
	std::string vertex_code, fragment_code;
	std::ifstream vertex_file, fragment_file;

	vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertex_file.open(vs_path);
		fragment_file.open(fs_path);

		std::stringstream vertex_stream, fragment_stream;
		vertex_stream << vertex_file.rdbuf();
		fragment_stream << fragment_file.rdbuf();

		vertex_file.close();
		fragment_file.close();

		vertex_code = vertex_stream.str();
		fragment_code = fragment_stream.str();
	} catch (std::ifstream::failure &f) {
		std::cerr << "Unable to open" << std::endl;
	}

	const char* vertex_shader_code = vertex_code.c_str();
	const char* fragment_shader_code = fragment_code.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex);
	check_compile_errors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment);
	check_compile_errors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	check_compile_errors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::use() {
	glUseProgram(ID);
}


void Shader::set_int(const std::string &name, int value) {
	unsigned int location = get_location(name);
	glUniform1i(location, value);
}


void Shader::set_float(const std::string &name, float value) {
	unsigned int location = get_location(name);
	glUniform1f(location, value);
}


void Shader::set_mat4(const std::string &name, glm::mat4 value) {
	unsigned int location = get_location(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);	
}


void Shader::set_vec3(const std::string &name, glm::vec3 value) {
	unsigned int location = get_location(name);
	glUniform3fv(location, 1, &value[0]);
}


void Shader::set_vec3(const std::string &name, float x, float y, float z) {
	unsigned int location = get_location(name);
	glUniform3f(location, x, y, z);
}


unsigned int Shader::get_location(const std::string name) {
	return glGetUniformLocation(ID, name.c_str());
}


void Shader::check_compile_errors(GLuint shader, std::string type) {
	int success;
	char info_log[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, info_log);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type " << type << "\n" << info_log;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, info_log);
			std::cerr << "ERROR::PROGRAM_LINK_ERROR of type " << type << "\n" << info_log << std::endl;
		}
	}
}

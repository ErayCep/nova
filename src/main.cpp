#include "shader.h"
#include "camera.h"
#include "model.h"
#include "light.h"
#include "skybox.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handle_keys(GLFWwindow* window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float last_x = WINDOW_WIDTH/ 2.0f;
float last_y = WINDOW_HEIGHT / 2.0f;
bool first_mouse = true;

float delta_time;
float last_frame;

int main() {
	glfwInit();
  
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "voxel-gl", 0, 0);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwMakeContextCurrent(window);
  
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  	std::cout << "[ERROR] Failed to initialize GLAD" << std::endl;
    return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("shader/shader.vert", "shader/shader.frag");
	Shader skyboxShader("shader/skybox.vert", "shader/skybox.frag");

	Model ourModel("resources/backpack/backpack.obj", false);

	Skybox skybox;

	skyboxShader.use();
	skyboxShader.set_int("skybox", 0);

	while (!glfwWindowShouldClose(window)) {
		float current_frame = static_cast<float>(glfwGetTime());
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		handle_keys(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = camera.get_view_matrix();
		projection = glm::perspective(glm::radians(camera.Fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

		shader.set_mat4("view", view);		
		shader.set_mat4("projection", projection);

		glm::mat4 model = glm::mat4(0.0002f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		shader.set_mat4("model", model);
		
		shader.set_vec3("cameraPos", camera.position);

		ourModel.Draw(shader);

		glDepthFunc(GL_LEQUAL);

		skyboxShader.use();

		view = glm::mat4(glm::mat3(camera.get_view_matrix()));
		skyboxShader.set_mat4("view", view);
		skyboxShader.set_mat4("projection", projection);

		skybox.Draw();

		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in) {
	float x_pos = static_cast<float>(x_pos_in);
	float y_pos = static_cast<float>(y_pos_in);

	if (first_mouse) {
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	float x_offset = x_pos - last_x;
	float y_offset = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;

	camera.handle_mouse(x_offset, y_offset, true);
}

void handle_keys(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.handle_keyboard(FORWARD, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.handle_keyboard(BACKWARD, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.handle_keyboard(LEFT, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.handle_keyboard(RIGHT, delta_time);
	}
}

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Resource Manager.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

const GLuint SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

Game SpaceInvaders(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc,char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invadersish", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SpaceInvaders.init();

	GLfloat deltaTime = 0.0f, lastFrame = 0.0f;
	
	SpaceInvaders.gs = INIT;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		SpaceInvaders.processInput(deltaTime);

		SpaceInvaders.update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SpaceInvaders.render();

		glfwSwapBuffers(window);
	}

	ResourceManager::clear();
	
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, GL_TRUE);
			SpaceInvaders.keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE)
		{
			SpaceInvaders.keys[key] = GL_FALSE;
		}
	}
}
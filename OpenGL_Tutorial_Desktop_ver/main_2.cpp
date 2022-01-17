#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

using namespace std;

void errorCallback(int errorcode, const char* errorDescription)
{
	fprintf(stderr, "error: %s\n", errorDescription);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main()
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		cerr << "Error: fail to init GLFW" << endl;;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window)
	{
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);
	glewExperimental = GL_TRUE;
	GLenum errorCode = glewInit();
	if (GLEW_OK != errorCode)
	{
		cerr << "Error: fail to init glew" << glewGetErrorString(errorCode) << endl;

		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	glfwSwapInterval(1);

	double lastTime = glfwGetTime();
	int numOfFrames = 0;
	int count = 0;

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		++numOfFrames;
		if (currentTime - lastTime >= 1.0)
		{
			printf("%f ms/frame %d fps \n", 1000.0 / double(numOfFrames), numOfFrames);
			numOfFrames = 0;
			lastTime = currentTime;
		}

		if (count % 2 == 0)
		{
			glClearColor(0, 1, 0, 0);

		}
		else
		{
			glClearColor(0, 0, 1, 0);
		}
		glClear(GL_COLOR_BUFFER_BIT);

		++count;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	exit(EXIT_SUCCESS);
}

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

using namespace std;

void window_resized(GLFWwindow* window, int width, int height);
void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void show_glfw_error(int error, const char* description);

int main()
{
	glfwSetErrorCallback(show_glfw_error);

	if (!glfwInit())
	{
		cerr << "Init Failed" << endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Example", NULL, NULL);
	if (!window)
	{
		cerr << "window init failed" << endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, window_resized);
	glfwSetKeyCallback(window, key_pressed);

	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		cerr << "GLEW Init Failed" << glewGetErrorString(err) << endl;
		glfwTerminate();
		exit(-1);
	}

	cout << glGetString(GL_VERSION) << endl;

	int nr_extensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nr_extensions);

	for (int i = 0; i < nr_extensions; ++i)
	{
		cout << glGetStringi(GL_EXTENSIONS, i) << endl;
	}

	glClearColor(0, 0, 1, 1);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}

void show_glfw_error(int error, const char* description)
{
	cerr << "Error: " << description << endl;

}

void window_resized(GLFWwindow* window, int width, int height)
{
	cout << "Window resized, new window size: " << width << " x " << height << endl;

	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == 'Q' && action == GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}
}
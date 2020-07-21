#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{

public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return glfwWindowShouldClose(mainWindow);
	}
	bool* getkeys() { return keys; }

	GLfloat getXchange();
	GLfloat getYchange();

	void swapBuffers() {
		glfwSwapBuffers(mainWindow);
	}
	~Window();


private:
	GLFWwindow *mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX; //son alýnan x
	GLfloat lastY; //son alýnan y cordinatý
	GLfloat xChange; //deðiþen x
	GLfloat yChange; //deðiþen y
	bool mouseFirstMoved; //ilk mouse hareketi mi diye kontrol eder

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};
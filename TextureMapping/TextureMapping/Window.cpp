#include "Window.h"


Window::Window() {
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight) {

	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

int Window::Initialise() {
	//Initialise GLFW

	if (!glfwInit()) {

		printf("GLFW Initiliazetion failed!");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW Window properties
	//OpenGL version

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //3.2 VERSÝYONU
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profie = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "TEST WINDOW", NULL, NULL);

	if (!mainWindow) {

		printf("GLFW window creatiýn failed!");
		glfwTerminate();
		return 1;
	}


	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set the context for GlEW to use
	glfwMakeContextCurrent(mainWindow);

	//Handle key + mouse
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {

		printf("GLEW Initiliezation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;

	}

	glEnable(GL_DEPTH_TEST);
	//Setup Viewport Size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXchange() {
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}
GLfloat Window::getYchange() {
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			/*printf("Pressed: %d\n", key);*/
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			/*printf("Released: %d\n", key);*/
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos; //y ekseni tersine dönmesin diye böyle yapýldý.

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	/*printf("X: %.6f , Y: %.6f\n", theWindow->xChange, theWindow->yChange);*/
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
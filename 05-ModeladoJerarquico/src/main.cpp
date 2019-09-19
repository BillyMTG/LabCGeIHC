//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int screenWidth;
int screenHeight;

GLFWwindow * window;

Shader shader;
std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Box box1;
Cylinder cylinder2(20, 20, 0.5, 0.5);
Box box2;
Box box3;
///////////R2D2
Sphere sphereR2D(20, 20);
Box boxR2D; 
Cylinder cylinderR2D(20, 20, 0.5, 0.5);
Box boxR2D2;
Sphere sphereR2D2(20, 20);


bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

float rot0 = 0.0, dz = 0.0; 

//R2D2
float rot0r2 = 0.0, dzr2 = 0.0;

//se declaran las rotaciones
float rot1 = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0, rot5 = 0.0, rot6 = 0.0, rot7 = 0.0, rot8 = 0.0;
//rotaciones de r2d2
float rot1r2 = 0.0, rot2r2 = 0.0, rot3r2 = 0.0, rot4r2 = 0.0;

bool sentido = true;

double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {
	
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");

	// Inicializar los buffers VAO, VBO, EBO
	sphere1.init();
	// Método setter que colocar el apuntador al shader
	sphere1.setShader(&shader);
	//Setter para poner el color de la geometria
	sphere1.setColor(glm::vec4(1.0, 0.843, 0.0, 1.0));

	// Inicializar los buffers VAO, VBO, EBO
	sphere2.init();
	// Método setter que colocar el apuntador al shader
	sphere2.setShader(&shader);
	//Setter para poner el color de la geometria
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	cylinder1.init();
	cylinder1.setShader(&shader);
	cylinder1.setColor(glm::vec4(1.0, 0.843, 0.0, 1.0));

	cylinder2.init();
	cylinder2.setShader(&shader);
	cylinder2.setColor(glm::vec4(0.803, 0.521, 0.247, 1.0));

	box1.init();
	box1.setShader(&shader);
	box1.setColor(glm::vec4(1.0, 0.843, 0.0, 1.0));

	box2.init();
	box2.setShader(&shader);
	box2.setColor(glm::vec4(0.803, 0.521, 0.247, 1.0));

	box3.init();
	box3.setShader(&shader);
	box3.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	//////////////////////////R2D2
	cylinderR2D.init();
	cylinderR2D.setShader(&shader);
	cylinderR2D.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	boxR2D.init();
	boxR2D.setShader(&shader);
	boxR2D.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereR2D.init();
	sphereR2D.setShader(&shader);
	sphereR2D.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	boxR2D2.init();
	boxR2D2.setShader(&shader);
	boxR2D2.setColor(glm::vec4(0.0, 0.0, 0.803,1.0));

	sphereR2D2.init();
	sphereR2D2.setShader(&shader);
	sphereR2D2.setColor(glm::vec4(0.0, 0.0, 0.0, 1.0));



	camera->setPosition(glm::vec3(0.0, 0.0, 4.0));
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Destrucción de los VAO, EBO, VBO
	sphere1.destroy();
	sphere2.destroy();
	cylinder1.destroy();
	cylinder2.destroy();
	box1.destroy();
	box2.destroy();
    box3.destroy();
    
	cylinderR2D.destroy();
	boxR2D.destroy();
	sphereR2D.destroy();
	boxR2D2.destroy();
	sphereR2D2.destroy();

	shader.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication){
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	TimeManager::Instance().CalculateFrameRate(false);
	deltaTime = TimeManager::Instance().DeltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, 0.01);
	offsetX = 0;
	offsetY = 0;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot0 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot0 += 0.001;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		dz += 0.001;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		dz -= 0.001;

	//Rotacion De r2d2
	
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS )
		rot0r2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS )
		rot0r2 += 0.001;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS )
		dzr2 += 0.001;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS )
		dzr2 -= 0.001;
	
	
	//Para agrgar mas moviemiento
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		sentido = false;

	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && sentido)
		rot1 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !sentido)
		rot1 -= 0.001;
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && sentido)
		rot2 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !sentido)
		rot2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && sentido)
		rot3 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !sentido)
		rot3 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && sentido)
		rot4 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !sentido)
		rot4 -= 0.001;
	//lado izquierdo
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && sentido)
		rot5 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && !sentido)
		rot5 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && sentido)
		rot6 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && !sentido)
		rot6 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && sentido)
		rot7 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && !sentido)
		rot7 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && sentido)
		rot8 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && !sentido)
		rot8 -= 0.001;

	//moviemiento R2D2
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		sentido = false;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && sentido)
		rot1r2 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !sentido)
		rot1r2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && sentido)
		rot2r2 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !sentido)
		rot2r2 -= 0.001;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && sentido)
		rot3r2 += 0.001;
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !sentido)
		rot3r2 -= 0.001;
	

	sentido = true;

	glfwPollEvents();
	return continueApplication;
}


void applicationLoop() {
	bool psi = true;

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 modelR2D = glm::mat4(1.0f);
	
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		
		/*//box1.enableWireMode();
		box1.render(glm::scale(model, glm::vec3(1.0, 1.0, 0.1)));

		// Articulacion 1
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));
		j1 = glm::rotate(j1, rot1, glm::vec3(0, 0, 1.0));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0.0));

		// Hueso 1
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25f, 0.0, 0.0));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));

		// Articulacion 2
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5, 0.0f, 0.0f));
		j2 = glm::rotate(j2, rot3, glm::vec3(0, 0, 1.0));
		j2 = glm::rotate(j2, rot4, glm::vec3(1, 0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));

		// Hueso 2
		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.25, 0.0, 0.0));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l2, glm::vec3(0.1, 0.5, 0.1)));

		// Ojo
		glm::mat4 ojo = glm::translate(model, glm::vec3(0.25, 0.25, 0.05));
		//sphere1.enableWireMode();
		sphere1.render(glm::scale(ojo, glm::vec3(0.2, 0.2, 0.1)));

		glm::mat4 ojo2 = glm::translate(model, glm::vec3(-0.25, 0.25, 0.05));
		//sphere2.enableWireMode();
		sphere2.render(glm::scale(ojo2, glm::vec3(0.2, 0.2, 0.1)));*/

		model = glm::translate(model,glm::vec3(0.0, dz, 0));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0.0));
		box1.enableWireMode();
		box1.render(glm::scale(model, glm::vec3(1.0, 1.0, 0.1)));

		//articulacion
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));
		j1 = glm::rotate(j1, rot1, glm::vec3(0, 0, 1.0));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0.0));

		//hueso
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25f, 0.0f, 0.0f));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));

		//articulacion2
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5f, 0.0f, 0.0f));
		j2 = glm::rotate(j2, rot3, glm::vec3(0, 0, 1.0));
		j2 = glm::rotate(j2, rot4, glm::vec3(1, 0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));

		//hueso2
		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.25f, 0.0f, 0.0f));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l2, glm::vec3(0.1, 0.5, 0.1)));

		//ojo
		glm::mat4 ojo = glm::translate(model, glm::vec3(0.25f, 0.25f, 0.05f));
		sphere2.enableWireMode();
		sphere2.render(glm::scale(ojo, glm::vec3(0.2, 0.2, 0.1)));

		glm::mat4 ojo2 = glm::translate(model, glm::vec3(-0.25f, 0.25f, 0.05f));
		sphere2.enableWireMode();
		sphere2.render(glm::scale(ojo2, glm::vec3(0.2, 0.2, 0.1)));

		//Lado Izquierdo
		//
		//articulacionIZq
		glm::mat4 a1 = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(a1, glm::vec3(0.1, 0.1, 0.1)));
		a1 = glm::rotate(a1, rot5, glm::vec3(0, 0, 1.0));
		a1 = glm::rotate(a1, rot6, glm::vec3(0, 1, 0.0));

		//huesoIzq
		glm::mat4 h1 = glm::translate(a1, glm::vec3(-0.25f, 0.0f, 0.0f));
		h1 = glm::rotate(h1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(h1, glm::vec3(0.1, 0.5, 0.1)));

		//articulacion2Izq
		glm::mat4 a2 = glm::translate(a1, glm::vec3(-0.5f, 0.0f, 0.0f));
		a2 = glm::rotate(a2, rot7, glm::vec3(0, 0, 1.0));
		a2 = glm::rotate(a2, rot8, glm::vec3(1, 0, 0.0));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(a2, glm::vec3(0.1, 0.1, 0.1)));


		//hueso2Izq
		glm::mat4 h2 = glm::translate(a2, glm::vec3(-0.25f, 0.0f, 0.0f));
		h2 = glm::rotate(h2, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(h2, glm::vec3(0.1, 0.5, 0.1)));

		//pantalon
		glm::mat4 p = glm::translate(model, glm::vec3(0.0f, -0.625f, 0.0f));
		//box2.enableWireMode();
		box2.render(glm::scale(p, glm::vec3(1.0, 0.25, 0.1)));

		glm::mat4 p2 = glm::translate(p, glm::vec3(-0.25f, -0.25f, 0.0f));
		cylinder2.enableWireMode();
		cylinder2.render(glm::scale(p2, glm::vec3(0.25, 0.25, 0.1)));

		glm::mat4 p3 = glm::translate(p, glm::vec3(0.25f, -0.25f, 0.0f));
		cylinder2.enableWireMode();
		cylinder2.render(glm::scale(p3, glm::vec3(0.25, 0.25, 0.1)));

		//pies

		glm::mat4 pie = glm::translate(p2, glm::vec3(0.0f, -0.375f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(pie, glm::vec3(0.1, 0.5, 0.1)));

		glm::mat4 pie2 = glm::translate(p3, glm::vec3(0.0f, -0.375f, 0.0f));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(pie2, glm::vec3(0.1, 0.5, 0.1)));

		//boca
		glm::mat4 b = glm::translate(model, glm::vec3(0.0f, -0.30f, 0.05f));
		//box3.enableWireMode();
		box3.render(glm::scale(b, glm::vec3(0.50, 0.15, 0.1)));

		//nariz 
		glm::mat4 n = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		n = glm::rotate(n, glm::radians(90.0f), glm::vec3(1.0, 0, 0.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(n, glm::vec3(0.1, 0.5, 0.1)));

		/////////////////R2D2::::

		modelR2D = glm::translate(modelR2D, glm::vec3(0.0, dzr2, 0));
		modelR2D = glm::rotate(modelR2D, rot0r2, glm::vec3(0, 1, 0.0));
		
		
		glm::mat4 cuerpo = glm::translate(modelR2D, glm::vec3(4.0f, 0.0f, 0.0f));
		//cuerpo = glm::rotate(cuerpo, rot0r2, glm::vec3(0, 1, 0.0));
		//cylinderR2D.enableWireMode();
		cylinderR2D.render(glm::scale(cuerpo, glm::vec3(1.0, 1.0, 1.0)));

		//articulaciion
		glm::mat4 art1 = glm::translate(cuerpo, glm::vec3(0.5f, 0.0f, 0.0f));
		//sphereR2D.enableWireMode();
		sphereR2D.render(glm::scale(art1, glm::vec3(0.1, 0.1, 0.1)));
		art1 = glm::rotate(art1, rot1r2, glm::vec3(1.0, 0.0, 0));
		

		//articulaciionizq
		glm::mat4 art1izq = glm::translate(cuerpo, glm::vec3(-0.5f, 0.0f, 0.0f));
		//sphereR2D.enableWireMode();
		sphereR2D.render(glm::scale(art1izq, glm::vec3(0.1, 0.1, 0.1)));
		art1izq = glm::rotate(art1izq, rot2r2, glm::vec3(1.0, 0.0, 0));

		//brazo
		glm::mat4 brazo = glm::translate(art1, glm::vec3(0.1f, -0.2f, 0.0f));
		//boxR2D.enableWireMode();
		boxR2D.render(glm::scale(brazo, glm::vec3(0.2, 0.7, 0.1)));

		//brazoizq
		glm::mat4 brazo2 = glm::translate(art1izq, glm::vec3(-0.1f, -0.2f, 0.0f));
		//boxR2D.enableWireMode();
		boxR2D.render(glm::scale(brazo2, glm::vec3(0.2, 0.7, 0.1)));

		//articulacion cabeza
		glm::mat4 artcabeza = glm::translate(cuerpo, glm::vec3(0.0f, 0.0f, 0.0f));
		sphereR2D.enableWireMode();
		sphereR2D.render(glm::scale(artcabeza, glm::vec3(0.1, 0.1, 0.1)));
		artcabeza = glm::rotate(artcabeza, rot3r2, glm::vec3(0.0, 1.0, 0));

		//cabeza
		glm::mat4 cabeza = glm::translate(artcabeza, glm::vec3(0.0f, 0.55f, 0.0f));
		//sphereR2D.enableWireMode();
		sphereR2D.render(glm::scale(cabeza, glm::vec3(1.0, 1.0, 1.0)));

		//articulacion pies
		glm::mat4 artpie = glm::translate(cuerpo, glm::vec3(0.0f, -0.5f, 0.0f));
		sphereR2D.enableWireMode();
		sphereR2D.render(glm::scale(artpie, glm::vec3(0.1, 0.1, 0.1)));
		

		//pìes
		glm::mat4 pies = glm::translate(artpie, glm::vec3(0.0f, -0.05f, 0.0f));
		//boxR2D.enableWireMode();
		boxR2D.render(glm::scale(pies, glm::vec3(0.4, 0.1, 1.0)));

		//extras
		glm::mat4 eye = glm::translate(cabeza, glm::vec3(0.0f, 0.0f, 0.5f));
		sphereR2D2.enableWireMode();
		sphereR2D2.render(glm::scale(eye, glm::vec3(0.1, 0.1, 0.05)));
		
		glm::mat4 o = glm::translate(cabeza, glm::vec3(0.0f, 0.0f, 0.5f));
		//boxR2D.enableWireMode();
		boxR2D2.render(glm::scale(o, glm::vec3(0.2, 0.2, 0.01)));

		glm::mat4 estomago = glm::translate(cuerpo, glm::vec3(0.0f, -0.1f, 0.5f));
		//boxR2D.enableWireMode();
		boxR2D2.render(glm::scale(estomago, glm::vec3(0.2, 0.5, 0.0)));

		glm::mat4 om = glm::translate(cuerpo, glm::vec3(0.0f, -0.1f, 0.5f));
		//sphereR2D2.enableWireMode();
		sphereR2D2.render(glm::scale(om, glm::vec3(0.1, 0.5, 0.1)));

		




		shader.turnOff();

		dz = 0;
		rot0 = 0;

		dzr2 = 0;
		rot0r2 = 0;

		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}

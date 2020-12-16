// 学学学
#include <iostream>
#include <vector>

// GLEW нужно подключать до GLFW.
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>

#include "Render/ShaderProgram.h"
#include "Render/Texture.h"
#include "Core/Camera.h"
#include "Visual/SceneObject.h"
// прототипи функцій
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Вікно
const GLuint WIDTH = 1024, HEIGHT = 720;

// Масив клавіш
bool keys[1024];

// Deltatimes
GLfloat deltaTime = 0.0f;	// Час, пройдений між останнім і поточним кадром
GLfloat lastFrame = 0.0f;  	// Час виводу останнього кадру

// Налаштування мишкі
GLfloat lastX = WIDTH / 2, lastY = HEIGHT / 2;
GLfloat yaw = -90.0f; // рискання навколо oY
GLfloat pitch = 0.0f; // тангаж навколо oX

// field of view
GLfloat fov = 45.0f; // тангаж навколо oX


int main()
{
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Колбекі
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// Захват курсора
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_DEPTH_TEST);

	ShaderProgram shader = ShaderProgram("../base/shaders/texturesMatrix2.vs", "../base/shaders/textures2.fs");

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint VBO, VAO; // IBO = EBO  index buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Атрибут с координатами
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	// Атрибут с текстурой
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Отвязка VAO

	// всі текстури будуть правильно зчитуватись відносно Y-осі 
	stbi_set_flip_vertically_on_load(true);
	Render::Texture texture1("../base/textures/container.jpg");
	Render::Texture texture2("../base/textures/awesomeface.png");

	std::vector<Visual::SceneObject> objects = { 
		Visual::SceneObject(Visual::Transform(glm::vec3(0.0f,  0.0f,  0.0f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(2.0f,  5.0f, -15.0f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(-1.5f, -2.2f, -2.5f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(-3.8f, -2.0f, -12.3f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(2.4f, -0.4f, -3.5f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(-1.7f,  3.0f, -7.5f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(1.3f, -2.0f, -2.5f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(1.5f,  2.0f, -2.5f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(1.5f,  0.2f, -1.5f))),
		Visual::SceneObject(Visual::Transform(glm::vec3(-1.3f,  1.0f, -1.5f))),
	};

	auto&& camera = Camera::Instance();
	camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);
	camera.Up = glm::vec3(0.0f, 1.0f, 0.0f);

	//System::

	// Игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		// Розрахунок дельти поточного кадру
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Проверяем события и вызываем функции обратного вызова.
		glfwPollEvents();
		do_movement(window);

		// Очистка буферу екрану
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1.GetData());
		shader.SetUniform1i("ourTexture1", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.GetData());
		shader.SetUniform1i("ourTexture2", 1);

		// Використання шейдерів і отрісовка
		shader.Use();

		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(fov), static_cast<float>(WIDTH / HEIGHT), 0.1f, 100.0f);

		shader.SetUniformMatrix4fv("view", camera.GetViewMatrix());
		shader.SetUniformMatrix4fv("projection", projection);


		glBindVertexArray(VAO);
		for (GLuint i = 0; i < objects.size(); i++)
		{
			GLfloat angle = 20.0f * i;
			objects[i].GetTransform().SetRotation(glm::vec3(1.0f, 0.3f, 0.5f) * angle);
			shader.SetUniformMatrix4fv("model", objects[i].GetTransform().GetModelMatrix());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Меняем буферы местами
		glfwSwapBuffers(window);
	}
	// Видалення масиву вершин
	glDeleteVertexArrays(1, &VAO);
	// Видалення вершинного буфера
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= static_cast<GLfloat>(yoffset);
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

bool _mouseFocus = false;
void do_movement(GLFWwindow* window)
{
	auto&& camera = Camera::Instance();
	// Управління камерою
	GLfloat cameraSpeed = 1.5f * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		if (keys[GLFW_KEY_LEFT_SHIFT])
			cameraSpeed *= 3.0f;
		camera.Position += cameraSpeed * camera.Front;
	}
	if (keys[GLFW_KEY_S])
		camera.Position -= cameraSpeed * camera.Front;
	if (keys[GLFW_KEY_A])
		camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;

	if (keys[GLFW_KEY_E])
	{
		_mouseFocus = !_mouseFocus;
		if (_mouseFocus)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	/*if (keys[GLFW_MOUSE_BUTTON_RIGHT])
		fov = 10.0f;
	else if (!keys[GLFW_MOUSE_BUTTON_RIGHT])
		fov = 45.0f;*/
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;
	if (firstMouse) // эта переменная была проинициализирована значением true
	{
		lastX = static_cast<GLfloat>(xpos);
		lastY = static_cast<GLfloat>(ypos);
		firstMouse = false;
	}

	GLfloat xoffset = static_cast<GLfloat>(xpos) - lastX;
	GLfloat yoffset = lastY - static_cast<GLfloat>(ypos); // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз 
	lastX = static_cast<GLfloat>(xpos);
	lastY = static_cast<GLfloat>(ypos);

	GLfloat sensitivity = 0.08f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	Camera::Instance().Front = glm::normalize(front);
}


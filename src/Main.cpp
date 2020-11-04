#include <iostream>

// GLEW ����� ���������� �� GLFW.
// GLEW
#define GLEW_STATIC
#include "GL/glew.h"
// GLFW
#include "GLFW/glfw3.h"
#include "Render/ShaderProgram.h"
#include "Render/Texture.h"
#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	//������������� GLFW
	glfwInit();
	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	ShaderProgram sh = ShaderProgram("../base/shaders/textures2.vs", "../base/shaders/textures2.fs");

	GLfloat vertices[] = {
		// �������          // �����             // ���������� ����������
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ������� ������
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ������ ������
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ������ �����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ������� �����
	};
	GLuint indices[] = {  // �������, ��� �� �������� � 0!
		0, 1, 3,   // ������ �����������
		1, 2, 3    // ������ �����������
	};

	GLuint VBO, VAO, IBO; // IBO = EBO  index buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO); // IBO = EBO
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ������� � ������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	// ������� � ������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// ������� � ������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // ������� VAO

	// �� �������� ������ ��������� ����������� ������� Y-�� 
	stbi_set_flip_vertically_on_load(true);
	Render::Texture texture1("../base/textures/container.jpg");
	Render::Texture texture2("../base/textures/awesomeface.png");

	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		// ��������� ������� � �������� ������� ��������� ������.
		glfwPollEvents();

		// ������� ������ ������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1.GetData());
		sh.SetUniform1i("ourTexture1", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.GetData());
		sh.SetUniform1i("ourTexture2", 1);

		// ������������ ������� � ��������
		sh.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// ������ ������ �������
		glfwSwapBuffers(window);
	}
	// ��������� ������ ������
	glDeleteVertexArrays(1, &VAO);
	// ��������� ���������� ������
	glDeleteBuffers(1, &VBO);
	// ��������� ���������� ������
	glDeleteBuffers(1, &IBO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
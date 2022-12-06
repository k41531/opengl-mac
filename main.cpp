#include<iostream>
#include<cmath>
#include<glad/gl.h>
#include<GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertices coordinates
GLfloat vertices[] =
{
	1.0f ,1.0f, 1.0f,
	-1.0f,1.0f, 1.0f,
	-1.0f,1.0f, -1.0f,
	1.0f ,1.0f, -1.0f,
	1.0f ,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, -1.0f,
	1.0f ,-1.0f, -1.0f,
};

// Indices for vertices order
GLuint indices[] =
{
	// Ceiling
	0, 1, 2,
	2, 3, 0,

	// Floor
	4, 5, 6,
	6, 7, 4,
	
	0, 1, 5,
	5, 4, 0,

	1, 2, 6,
	6, 5, 1,

	2, 3, 7,
	7, 6, 2,

	3, 0, 4,
	4, 7, 3,
};

int main()
{
	// GLFWの初期化
	glfwInit();

	// GLFWのバージョンを指定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// GLFWのプロファイルを指定
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Windowを作成 
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL on MAC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// コンテキストの作成
	glfwMakeContextCurrent(window);
	// GLADをロードしてOpenGLの設定を行う
	gladLoadGL(glfwGetProcAddress);
    


	glViewport(0, 0, 800, 800);
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();;

	// 射影行列：45&deg;の視界、アスペクト比4:3、表示範囲：0.1単位  100単位
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	// カメラ行列
	glm::mat4 View       = glm::lookAt(
		glm::vec3(4,3,3), // ワールド空間でカメラは(4,3,3)にあります。
		glm::vec3(0,0,0), // 原点を見ています。
		glm::vec3(0,1,0)  // 頭が上方向(0,-1,0にセットすると上下逆転します。)
	);
	// モデル行列：単位行列(モデルは原点にあります。)
	glm::mat4 Model      = glm::mat4(1.0f);  // 各モデルを変える！
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // 行列の掛け算は逆になることを思い出してください。
	GLuint MatrixID = glGetUniformLocation(shaderProgram.ID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
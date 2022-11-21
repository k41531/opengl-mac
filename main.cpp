#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

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
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
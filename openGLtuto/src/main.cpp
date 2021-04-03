#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "Texture.h"

int main1()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window;

	window = glfwCreateWindow(1080, 768, "test", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR" << std::endl;
		return -1;
	}
	glfwSwapInterval(10);

	{
		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f, 0.5f,
			-0.5f, 0.5f
		};

		// indices of triangles
		unsigned int indices[] = {
				0,1,2
		};

		unsigned int indices2[] = {
			2,3,0
		};
		while (true) 
		{
			VertexBuffer vb(positions, 4 * 2 * sizeof(float));
			IndexBuffer ib(indices, 3);
			IndexBuffer ib2(indices2, 3);
			VertexArray va;
			VertexBufferLayout layout;
			layout.Push<float>(2);
			va.AddBuffer(vb, layout);
			Shader shader("res/shaders/Basic.shader");
			shader.Bind();
			shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
			Renderer renderer;
			renderer.Clear();
			renderer.Draw(va, ib, shader);
			shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.2f, 1.0f);
			renderer.Draw(va, ib2, shader);
			GLCall(glfwSwapBuffers(window));
		}
		
	}
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <matrix.hpp>


#include <string>
#include <iostream>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include <random>
#include "Texture.h"
#include <trigonometric.hpp>
#include <gtc/matrix_transform.hpp>


int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window;

	window = glfwCreateWindow(800, 800, "test", NULL, NULL);

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
		float front_face[4 * 5] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};
		float back_face[4 * 5] = {
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		float right_face[4 * 5] = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		float left_face[4* 5] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		float top_face[4 * 5] = {
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		float bottom_face[4 * 5] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};

		// indices of triangles
		unsigned int indices[] = {
				0,1,2,
				1,2,3
		};

		VertexBuffer front_vb(front_face, 4 * 5 * sizeof(float));
		VertexBuffer back_vb(back_face, 4 * 5 * sizeof(float));
		VertexBuffer left_vb(left_face, 4 * 5 * sizeof(float));
		VertexBuffer right_vb(right_face, 4 * 5 * sizeof(float));
		VertexBuffer top_vb(top_face, 4 * 5 * sizeof(float));
		VertexBuffer bottom_vb(bottom_face, 4 * 5 * sizeof(float));
		IndexBuffer ib(indices, 6);


		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		VertexArray front_va;
		front_va.AddBuffer(front_vb,layout);

		VertexArray back_va;
		back_va.AddBuffer(back_vb, layout);

		VertexArray top_va;
		top_va.AddBuffer(top_vb, layout);

		VertexArray bottom_va;
		bottom_va.AddBuffer(bottom_vb, layout);

		VertexArray left_va;
		left_va.AddBuffer(left_vb, layout);

		VertexArray right_va;
		right_va.AddBuffer(right_vb, layout);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		// �������� ��Ʈ���� : 45�� �þ߰�, 4:3 ����, �þ� ���� : 0.1 ���� <--> 100 ����
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

		//Ȥ�� ortho(����) ī�޶󿡼� :
		//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // ���� ��ǥ�� ǥ��

		// ī�޶� ��Ʈ����
		glm::mat4 View = glm::lookAt(
			glm::vec3(2, 4, 3), // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
			glm::vec3(0, 0, 0), // �׸��� ī�޶� ������ ����
			glm::vec3(0, 1, 0)  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
		);

		// �� ��Ʈ���� : ���� ��Ʈ���� (���� ������ ��ġ�ȴ�)
		glm::mat4 Model = glm::mat4(1.0f);
		// �츮�� �𵨺��������� : 3�� ��Ʈ�������� ���Ѵ�
		glm::mat4 mvp = Projection * View * Model; // ����ϼ���, ��İ��� ����� �ݴ������ �̷�����ϴ�
		shader.SetUniformMat4by4("u_proj", mvp);
		
		Texture texture("res/img.png");
		texture.Bind();
		Renderer renderer;
		while (true)
		{
			renderer.Clear();
			renderer.Draw(left_va, ib, shader);
			renderer.Draw(bottom_va, ib, shader);
			renderer.Draw(back_va, ib, shader);
			renderer.Draw(front_va, ib, shader);
			renderer.Draw(top_va, ib, shader);
			renderer.Draw(right_va, ib, shader);
			
			
			GLCall(glfwSwapBuffers(window));
		}

	}
}
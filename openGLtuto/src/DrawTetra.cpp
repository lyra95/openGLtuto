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


int main1()
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
		/*
		float faceZ[9] = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f
		};
		

		float faceX[9] = {
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f
		};

		float faceY[9] = {
			 -0.5f,  -0.5f, -0.5f,
			  0.5f,  -0.5f, -0.5f,
			 -0.5f,  -0.5f,  0.5f
		};

		float face[] = {
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f
		};
		*/
		float points[] = {
			-0.5f, -0.5f, -0.5f, //1.0f,
			 0.5f, -0.5f, -0.5f, //1.0f,
			-0.5f,  0.5f, -0.5f, //1.0f,
			-0.5f, -0.5f,  0.5f//, 1.0f
		};

		// indices of triangles
		unsigned int indices[] = {
				0,1,2,
				0,1,3,
				0,2,3,
				1,2,3
		};

		VertexBuffer vb(points, 4 * 3 * sizeof(float));
		IndexBuffer ib0(indices, 3);
		IndexBuffer ib1(indices+3, 3);
		IndexBuffer ib2(indices+6, 3);
		IndexBuffer ib3(indices+9, 3);

		VertexArray va;
		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		Shader shader("res/shaders/CubeShader.shader");
		shader.Bind();

		// 프로젝션 매트릭스 : 45도 시야각, 4:3 비율, 시야 범위 : 0.1 유닛 <--> 100 유닛
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

		//혹은 ortho(직교) 카메라에선 :
		//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // 월드 좌표로 표현

		// 카메라 매트릭스
		glm::mat4 View = glm::lookAt(
			glm::vec3(2, 1, 3), // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
			glm::vec3(0, 0, 0), // 그리고 카메라가 원점을 본다
			glm::vec3(0, 1, 0)  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)
		);

		// 모델 매트릭스 : 단위 매트릭스 (모델은 원점에 배치된다)
		glm::mat4 Model = glm::mat4(1.0f);
		// 우리의 모델뷰프로젝션 : 3개 매트릭스들을 곱한다
		glm::mat4 mvp = Projection * View * Model; // 기억하세요, 행렬곱은 계산은 반대순서로 이루어집니다

		
		shader.SetUniformMat4by4("u_proj", mvp);
		Renderer renderer;
		while (true) 
		{	
			renderer.Clear();

			shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
			renderer.Draw(va, ib0, shader);

			shader.SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
			renderer.Draw(va, ib1, shader);
			
			shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
			renderer.Draw(va, ib2, shader);
			
			//shader.SetUniform4f("u_Color", 0.7f, 0.2f, 0.4f, 1.0f);
			//renderer.Draw(va, ib3, shader);
			
			GLCall(glfwSwapBuffers(window));
		}
		
	}
}